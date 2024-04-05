/*************************************************************************
 * Copyright (C) [2019-2022] by Cambricon, Inc.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *************************************************************************/
#include <chrono>
#include <random>
#include <iomanip>
#include <limits>
#include <cfloat>
#include <string>
#include "string.h"
#include "tool.h"

using std::map;
using std::string;
using std::pair;





#define INT16_BITWIDTH 16
#define INT31_BITWIDTH 31
#define ARGC_NUM 21

const double EPSILON = 1e-9;


void initDevice(int &dev, cnrtQueue_t &queue, cnnlHandle_t &handle) {
  CNRT_CHECK(cnrtGetDevice(&dev));
  CNRT_CHECK(cnrtSetDevice(dev));

  CNRT_CHECK(cnrtQueueCreate(&queue));

  CNNL_CHECK(cnnlCreate(&handle));
  CNNL_CHECK(cnnlSetQueue(handle, queue));
}

// found inf or nan, return true.
#ifdef __AVX__
bool hasNanOrInf(float *data, size_t count) {
  const __m256 exp_bit = _mm256_set1_ps(std::numeric_limits<float>::infinity());
  size_t stride = 256 / (sizeof(float) * 8);  // 1 __m256 saved 8 * (sizeof(float) * 8 bit)
  size_t repeat = count / stride * stride;
  __m256 m_data;
  for (size_t i = 0; i < repeat; i += stride) {
    m_data = _mm256_load_ps(data + i);
    m_data = _mm256_and_ps(exp_bit, m_data);
    m_data = _mm256_cmp_ps(m_data, exp_bit, _CMP_EQ_OQ);
    if (_mm256_movemask_ps(m_data) != 0) {
      return true;
    }
  }
  for (size_t i = repeat; i < count - repeat; ++i) {
    if (std::isnan(data[i]) || std::isinf(data[i])) {
      return true;
    }
  }
  return false;
}
#else
bool hasNanOrInf(float *data, size_t count) {
  for (size_t i = 0; i < count; ++i) {
    if (std::isinf(data[i]) || std::isnan(data[i])) {
      return true;
    }
  }
  return false;
}
#endif

double computeDiff1(float *cpu_result, float *mlu_result, size_t count) {
  if (hasNanOrInf(cpu_result, count) || hasNanOrInf(mlu_result, count)) {
    ERROR("Found NaN or Inf when compute diff, return DBL_MAX instead.");
    return DBL_MAX;
  }
  double numerator_sum = 0.0;
  double denominator_sum = 0.0;
  for (size_t i = 0; i < count; i++) {
    numerator_sum += fabs(cpu_result[i] - mlu_result[i]);
    denominator_sum += fabs(cpu_result[i]);
  }
  return numerator_sum / (denominator_sum + EPSILON);
}

double computeDiff2(float *cpu_result, float *mlu_result, size_t count) {
  if (hasNanOrInf(cpu_result, count) || hasNanOrInf(mlu_result, count)) {
    ERROR("Found NaN or Inf when compute diff, return DBL_MAX instead.");
    return DBL_MAX;
  }
  double numerator_sum = 0.0;
  double denominator_sum = 0.0;
  for (size_t i = 0; i < count; i++) {
    float delta = fabs(cpu_result[i] - mlu_result[i]);
    numerator_sum += pow(delta, 2);
    denominator_sum += pow(fabs(cpu_result[i]), 2);
  }
  return sqrt(numerator_sum / (denominator_sum + EPSILON));
}

size_t dataSize(cnnlDataType_t dtype) {
  switch (dtype) {
    case CNNL_DTYPE_HALF:
      return 2;
    case CNNL_DTYPE_FLOAT:
      return 4;
    case CNNL_DTYPE_INT8:
      return 1;
    case CNNL_DTYPE_INT16:
      return 2;
    case CNNL_DTYPE_INT31:
      return 4;
    case CNNL_DTYPE_INT32:
      return 4;
    default:
      ERROR("unsupport data  dtype");
  }
}

cnrtDataType_t convertCnnlDtypeToCnrt(cnnlDataType_t dtype) {
  switch (dtype) {
    case CNNL_DTYPE_HALF:
      return CNRT_FLOAT16;
    case CNNL_DTYPE_FLOAT:
      return CNRT_FLOAT32;
    case CNNL_DTYPE_INT8:
      return CNRT_INT8;
    case CNNL_DTYPE_INT16:
      return CNRT_INT16;
    case CNNL_DTYPE_INT32:
      return CNRT_INT32;
    case CNNL_DTYPE_BOOL:
      return CNRT_BOOL;
    case CNNL_DTYPE_UINT8:
      return CNRT_UINT8;
    default:
      ERROR("unsupport data type!");
  }
}

void getPosition(float *input, size_t num, cnnlDataType_t datatype, int &position) {
  if (nullptr == input || 0 == num) {
    ERROR("[getPosition]:input param is illegal");
    return;
  }

  int bitwidth = 8;
  if (datatype == CNNL_DTYPE_INT8) {
    bitwidth = 8;
  } else if (datatype == CNNL_DTYPE_INT16) {
    bitwidth = 16;
  } else if (datatype == CNNL_DTYPE_INT31) {
    bitwidth = 31;
  } else {
    ERROR("[getPosition]:Input data type is not supported.");
  }
  // Formula: position = floor(log2(absmax) - (bitwidth - 2)))
  float absmax = std::fabs(input[0]);
  for (size_t index = 0; index < num; ++index) {
    if (std::fabs(input[index]) > absmax)
      absmax = std::fabs(input[index]);
  }

  if (absmax == 0) {
    position = 0;
  } else {
    position = static_cast<int>(std::floor(std::log2(absmax)) - (bitwidth - 2));
  }
}

void getPositionAndScale(float *input,
                         size_t num,
                         cnnlDataType_t datatype,
                         int &position,
                         float &scale) {
  if (nullptr == input || 0 == num) {
    ERROR("[getPositionAndScale]:input param is illegal");
  }

  int bitwidth = 8;
  if (datatype == CNNL_DTYPE_INT8) {
    bitwidth = 8;
  } else if (datatype == CNNL_DTYPE_INT16) {
    bitwidth = 16;
  } else if (datatype == CNNL_DTYPE_INT31) {
    bitwidth = 31;
  } else {
    ERROR("[getPositionAndScale]:Input data type is not supported.");
  }

  int scale_var = std::pow(2, bitwidth - 1) - 1;
  float max_data = std::fabs(input[0]);
  for (size_t index = 0; index < num; ++index) {
    if (std::fabs(input[index]) > max_data)
      max_data = std::fabs(input[index]);
  }
  if (max_data == 0) {
    position = 0;
    scale = 1.0;
  } else if (bitwidth != 31) {
    position = static_cast<int>(std::floor(std::log2(max_data)) - (bitwidth - 2));
    scale = static_cast<float>(std::pow(2, position) * scale_var / max_data);
  } else {
    position = static_cast<int>(std::floor(std::log2(max_data)) - (bitwidth - 2));
    scale = 1.0;
  }
}

void castFloat32ToInt31(float *src, size_t num, void *dst) {
  if (nullptr == src || nullptr == dst || num == 0) {
    ERROR("[castFloat32ToInt31]:input param is illegal.");
  }

  int position = 0;
  int var = std::pow(2, INT31_BITWIDTH - 1) - 1;
  float temp = 0.0f;
  float temp_high = 0.0f;
  float temp_low = 0.0f;

  // get absmax of the float data
  float absmax = std::fabs(src[0]);
  for (size_t i = 0; i < num; ++i) {
    if (std::fabs(src[i]) > absmax)
      absmax = std::fabs(src[i]);
  }

  // Formula: int31 , position = floor(log2(absmax) - 29))
  if (absmax == 0) {
    position = 0;
  } else {
    position = static_cast<int>(std::floor(std::log2(absmax)) - 29);
  }

  if (absmax == 0) {
    for (size_t i = 0; i < num; ++i) {
      // low int16 data
      ((int16_t *)dst)[i] = 0;
      // high int16 data
      ((int16_t *)dst)[i + num] = 0;
    }
  } else {
    // Formula: f = (high * 2^15 + low) * 2^position.
    var = std::pow(2, INT16_BITWIDTH - 1);
    for (size_t i = 0; i < num; ++i) {
      temp = src[i] / (std::pow(2, position));
      temp = (temp >= 0) ? (temp + 0.5f) : (temp - 0.5f);

      // high int16 data
      temp_high = temp / var;
      ((int16_t *)dst)[i + num] = static_cast<int16_t>(temp_high);
      // low int16 data
      temp_low = temp - ((int16_t *)dst)[i + num] * var;
      ((int16_t *)dst)[i] = static_cast<int16_t>(temp_low);
    }
  }
}

// get quant param
void getQuantizedParam(float *src_data,
                       size_t count,
                       cnnlDataType_t dst_dtype,
                       int quant_mode,
                       int &position,
                       float &scale) {
  position = 0;
  scale = 1.0f;
  if (CNNL_DTYPE_INT8 == dst_dtype || CNNL_DTYPE_INT16 == dst_dtype ||
      CNNL_DTYPE_INT31 == dst_dtype) {
    if (0 == quant_mode) {
      getPosition(src_data, count, dst_dtype, position);
    } else if (1 == quant_mode) {
      getPositionAndScale(src_data, count, dst_dtype, position, scale);
    } else {
      ERROR("unsupported quant mode")
    }
  } else {
    LOG("don't need fix quantify")
  }
}

void castData(float *src_data,
              cnnlDataType_t src_dtype,
              char *dst_data,
              cnnlDataType_t dst_dtype,
              float *dequantify_data,
              int quant_mode,
              size_t size,
              int &position,
              float &scale,
              int &offset) {
  if (src_dtype == CNNL_DTYPE_FLOAT && dst_dtype == CNNL_DTYPE_FLOAT) {
    memcpy(dst_data, src_data, size * sizeof(float));
    memcpy(dequantify_data, src_data, size * sizeof(float));
  } else if ((src_dtype == CNNL_DTYPE_FLOAT && dst_dtype == CNNL_DTYPE_INT8) ||
             (src_dtype == CNNL_DTYPE_FLOAT && dst_dtype == CNNL_DTYPE_INT16)) {
    getQuantizedParam(src_data, size, dst_dtype, quant_mode, position, scale);
    cnrtQuantizedParam_t quant_param = nullptr;
    CNRT_CHECK(cnrtCreateQuantizedParam(&quant_param, position, scale, offset));

    auto in_dtype = convertCnnlDtypeToCnrt(src_dtype);
    auto out_dtype = convertCnnlDtypeToCnrt(dst_dtype);
    CNRT_CHECK(cnrtCastDataType(src_data, in_dtype, dst_data, out_dtype, size, quant_param));
    // dequantify data for cpu compute
    CNRT_CHECK(cnrtCastDataType(dst_data, out_dtype, dequantify_data, in_dtype, size, quant_param));
    CNRT_CHECK(cnrtDestroyQuantizedParam(quant_param));
  } else if (src_dtype == CNNL_DTYPE_FLOAT && dst_dtype == CNNL_DTYPE_INT31) {
    getQuantizedParam(src_data, size, dst_dtype, quant_mode, position, scale);
    castFloat32ToInt31(src_data, size, dst_data);
    // int31 don't need dequantify cpu data
    memcpy(dequantify_data, src_data, size * sizeof(float));
  } else if ((src_dtype == CNNL_DTYPE_FLOAT && dst_dtype == CNNL_DTYPE_HALF) ||
             (src_dtype == CNNL_DTYPE_FLOAT && dst_dtype == CNNL_DTYPE_INT32) ||
             (src_dtype == CNNL_DTYPE_FLOAT && dst_dtype == CNNL_DTYPE_BOOL)) {
    // don't need dequantify cpu data
    auto in_dtype = convertCnnlDtypeToCnrt(src_dtype);
    auto out_dtype = convertCnnlDtypeToCnrt(dst_dtype);
    CNRT_CHECK(cnrtCastDataType(src_data, in_dtype, dst_data, out_dtype, size, nullptr));
    memcpy(dequantify_data, src_data, size * sizeof(float));
  } else {
    ERROR("This dtype is not supported, while cast data type.");
  }
}

void parserParam(int argc, char *argv[], ShapeParam &param) {
  if (argc != ARGC_NUM) {
    std::string message = "command format error, please reference run_conv_sample.sh.";
    ERROR(message);
  }
  argc -= 1;
  argv++;
  char opt[2];
  while (argc) {
    //if (*argv[0] == SWITCH_CHAR) 
    if (*argv[0] == '-')
    {
      strncpy(opt, argv[0] + 1, OPT_LEN);
      if (strncmp(opt, "ni", OPT_LEN) == 0) {
        param.input.n = atol(argv[0] + 3);
        param.output.n = atol(argv[0] + 3);
      } else if (strncmp(opt, "hi", OPT_LEN) == 0) {
        param.input.h = atol(argv[0] + 3);
      } else if (strncmp(opt, "wi", OPT_LEN) == 0) {
        param.input.w = atol(argv[0] + 3);
      } else if (strncmp(opt, "ci", OPT_LEN) == 0) {
        param.input.c = atol(argv[0] + 3);
        param.weight.c = param.input.c;
      } else if (strncmp(opt, "co", OPT_LEN) == 0) {
        param.output.c = atol(argv[0] + 3);
        param.weight.n = param.output.c;
      } else if (strncmp(opt, "kh", OPT_LEN) == 0) {
        param.kernel.kh = atol(argv[0] + 3);
        param.weight.h = param.kernel.kh;
      } else if (strncmp(opt, "kw", OPT_LEN) == 0) {
        param.kernel.kw = atol(argv[0] + 3);
        param.weight.w = param.kernel.kw;
      } else if (strncmp(opt, "sh", OPT_LEN) == 0) {
        param.kernel.sh = atol(argv[0] + 3);
      } else if (strncmp(opt, "sw", OPT_LEN) == 0) {
        param.kernel.sw = atol(argv[0] + 3);
      } else if (strncmp(opt, "dh", OPT_LEN) == 0) {
        param.kernel.dh = atol(argv[0] + 3);
      } else if (strncmp(opt, "dw", OPT_LEN) == 0) {
        param.kernel.dw = atol(argv[0] + 3);
      } else if (strncmp(opt, "pt", OPT_LEN) == 0) {
        param.pad.pt = atol(argv[0] + 3);
      } else if (strncmp(opt, "pb", OPT_LEN) == 0) {
        param.pad.pb = atol(argv[0] + 3);
      } else if (strncmp(opt, "pl", OPT_LEN) == 0) {
        param.pad.pl = atol(argv[0] + 3);
      } else if (strncmp(opt, "pr", OPT_LEN) == 0) {
        param.pad.pr = atol(argv[0] + 3);
      } else if (strncmp(opt, "id", OPT_LEN) == 0) {
        param.datainfo.input_dtype = (cnnlDataType_t)atol(argv[0] + 3);
      } else if (strncmp(opt, "wd", OPT_LEN) == 0) {
        param.datainfo.weight_dtype = (cnnlDataType_t)atol(argv[0] + 3);
      } else if (strncmp(opt, "od", OPT_LEN) == 0) {
        param.datainfo.output_dtype = (cnnlDataType_t)atol(argv[0] + 3);
      } else if (strncmp(opt, "hb", OPT_LEN) == 0) {
        param.has_bias = atol(argv[0] + 3) == 0 ? false : true;
      } else if (strncmp(opt, "gc", OPT_LEN) == 0) {
        param.group_count = atol(argv[0] + 3);
      } else {
        std::string opt_str = opt;
        std::string message = "unsupport param:" + opt_str;
        ERROR(message);
      }
    }
    argc -= 1;
    argv++;
  }

  if (param.has_bias) {
    param.bias.c = param.output.c;
    param.bias.n = 1;
    param.bias.h = 1;
    param.bias.w = 1;
  }
  // compute output shape
  int expand_kh = (param.kernel.kh - 1) * param.kernel.dh + 1;
  int expand_kw = (param.kernel.kw - 1) * param.kernel.dw + 1;
  param.output.h = (param.input.h + param.pad.pt + param.pad.pb - expand_kh) / param.kernel.sh + 1;
  param.output.w = (param.input.w + param.pad.pl + param.pad.pr - expand_kw) / param.kernel.sw + 1;
}

void setTensorDesc(cnnlTensorDescriptor_t &desc,
                   Shape2D shape,
                   cnnlDataType_t dtype,
                   cnnlTensorLayout_t layout) {
  int dim[4];
  if (layout == CNNL_LAYOUT_NHWC) {
    dim[0] = shape.n;
    dim[1] = shape.h;
    dim[2] = shape.w;
    dim[3] = shape.c;
  } else if (layout == CNNL_LAYOUT_NCHW) {
    dim[0] = shape.n;
    dim[1] = shape.c;
    dim[2] = shape.h;
    dim[3] = shape.w;
  } else if (layout == CNNL_LAYOUT_HWCN) {
    dim[0] = shape.h;
    dim[1] = shape.w;
    dim[2] = shape.c;
    dim[3] = shape.n;
  } else if (layout == CNNL_LAYOUT_ARRAY) {
    dim[0] = shape.n;
    dim[1] = shape.c;
    dim[2] = shape.h;
    dim[3] = shape.w;
  } else {
    ERROR("unsupport data layout!");
  }
//  printf("1111zkg\n");
  CNNL_CHECK(cnnlCreateTensorDescriptor(&desc));
  CNNL_CHECK(cnnlSetTensorDescriptor(desc, layout, dtype, 4, dim));
//  printf("22222zkg\n");
}

float *mallocDataRandf(int size, int low, int hight) {
  float *data = (float *)malloc(size * sizeof(float));
  std::uniform_real_distribution<float> dist(low, hight);
  std::default_random_engine random(time(NULL));
  for (int i = 0; i < size; i++) {
    data[i] = dist(random);
  }
  return data;
}

void saveDataToFile(char const *file, float *data, size_t count) {
  std::ofstream fout(file, std::ios::out);
  for (size_t i = 0; i < count; ++i) {
    fout << data[i] << std::endl;
  }
  fout.close();
}

float cvtHalfToFloat(int16_t src) {
  if (sizeof(int16_t) == 2) {
    int re = src;
    float f = 0.;
    int sign = (re >> 15) ? (-1) : 1;
    int exp = (re >> 10) & 0x1f;
    int eff = re & 0x3ff;
    float half_max = 65504.;
    float half_min = -65504.;  // or to be defined as infinity
    if (exp == 0x1f && sign == 1) {
      // add upper bound of half. 0x7bff： 0 11110 1111111111 =  65504
      return half_max;
    } else if (exp == 0x1f && sign == -1) {
      // add lower bound of half. 0xfbff： 1 11110 1111111111 = -65504
      return half_min;
    }
    if (exp > 0) {
      exp -= 15;
      eff = eff | 0x400;
    } else {
      exp = -14;
    }
    int sft;
    sft = exp - 10;
    if (sft < 0) {
      f = (float)sign * eff / (1 << (-sft));
    } else {
      f = ((float)sign) * (1 << sft) * eff;
    }
    return f;
  } else if (sizeof(int16_t) == 4) {
    // using float
    return src;
  }
}

void saveHexDataToFile(char const *file, void *data, cnnlDataType_t dtype, size_t count) {
  std::ofstream fout(file, std::ios::out);
  switch (dtype) {
    case CNNL_DTYPE_HALF: {
      for (size_t i = 0; i < count; ++i) {
        fout << "hex: " << std::setw(10) << std::hex << ((int16_t *)data)[i] << std::setw(20)
             << "dec: " << std::setw(10) << std::dec << cvtHalfToFloat(((int16_t *)data)[i])
             << std::endl;
      }
    } break;
    case CNNL_DTYPE_FLOAT: {
      for (size_t i = 0; i < count; ++i) {
        fout << "hex: " << std::setw(10) << std::hex << ((int32_t *)data)[i] << std::setw(20)
             << "dec: " << std::setw(10) << std::dec << ((float *)data)[i] << std::endl;
      }
    } break;
    case CNNL_DTYPE_INT8: {
      for (size_t i = 0; i < count; ++i) {
        fout << "hex: " << std::setw(10) << std::hex << (int32_t)((int8_t *)data)[i]
             << std::setw(20) << "dec: " << std::setw(10) << std::dec
             << (int32_t)((int8_t *)data)[i]  // don't show char
             << std::endl;
      }
    } break;
    case CNNL_DTYPE_UINT8: {
      for (size_t i = 0; i < count; ++i) {
        fout << "hex: " << std::setw(10) << std::hex << (uint32_t)((uint8_t *)data)[i]
             << std::setw(20) << "dec: " << std::setw(10) << std::dec
             << (uint32_t)((uint8_t *)data)[i]  // not char
             << std::endl;
      }
    } break;
    case CNNL_DTYPE_INT16: {
      for (size_t i = 0; i < count; ++i) {
        fout << "hex: " << std::setw(10) << std::hex << ((int16_t *)data)[i] << std::setw(20)
             << "dec: " << std::setw(10) << std::dec << ((int16_t *)data)[i] << std::endl;
      }
    } break;
    case CNNL_DTYPE_INT32: {
      for (size_t i = 0; i < count; ++i) {
        fout << "hex: " << std::setw(10) << std::hex << ((int32_t *)data)[i] << std::setw(20)
             << "dec: " << std::setw(10) << std::dec << ((int32_t *)data)[i] << std::endl;
      }
    } break;
    case CNNL_DTYPE_BOOL: {
      for (size_t i = 0; i < count; ++i) {
        fout << "hex: " << std::setw(10) << std::hex << (int32_t)((bool *)data)[i] << std::setw(20)
             << "dec: " << std::setw(10) << std::dec << (int32_t)((bool *)data)[i] << std::endl;
      }
    } break;
    case CNNL_DTYPE_INT31: {
      // int31 save as int16 * 2
      for (size_t i = 0; i < count * 2; ++i) {
        fout << "hex: " << std::setw(10) << std::hex << ((int16_t *)data)[i] << std::setw(20)
             << "dec: " << std::setw(10) << std::dec << ((int16_t *)data)[i] << std::endl;
      }
    } break;
    default: { ERROR("unsupport data type!"); }
  }
  fout.close();
}


//添加新函数20230512(后续删除量化内容)
QuantParam getInt8Info(const vector<float> input_data,
                       string layer_name,
                       LayerType layer_type,
                       const string& mode,
                       // only weights should get channel quantimizaed
                       bool channel_quantimize = false,
                       // this is for multi-batch images in generate_int8_pt
                       // for bottoms only
                       map<string, float>* const max_value = nullptr,
                       // absmax should be squared for normalize bottom 0
                       // not normalize bottom 1
                       bool is_first_normalize = false) {
    vector<float> max(1, 0), min(1, 0), abs_max(1, 0),
    position(1, 0), scale(1, 0);
    int length = input_data.size();
    bool lrn = layer_type == LRN;
    string key = layer_name;

    const float* data = input_data.data();
    min[0] = max[0] = data[0];
    for (int j = 0; j < length; ++j) {
        max[0] = std::max(data[j], max[0]);  // max input data
        min[0] = std::min(data[j], min[0]);  // min input data
    }
    abs_max[0] = std::max(std::abs(min[0]), std::abs(max[0]));

    if (max_value != nullptr) {
        for (unsigned int i = 0; i < abs_max.size(); i++) {
        auto iter = max_value->find(key);
        if (iter != max_value->end()) {
            if (abs_max[i] > iter->second) {
            (*max_value)[key] = abs_max[i];
            } else {
            abs_max[i] = (*max_value)[key];
            }
        } else {
            max_value->insert(pair<string, float>(key, abs_max[i]));
        }
        }
    }
    if (lrn) {
        // abs_max[0] = abs_max[0] * abs_max[0] * layer_param.lrn_param().alpha();
        std::cout << "ERROR: NOT SUPPORT LRN YET!\n";
        exit(1);
    } else if (is_first_normalize) {
        // abs_max[0] *= abs_max[0];
        std::cout << "ERROR: NOT SUPPORT NORMALIZE YET!\n";
        exit(1);
    }

    int critical_value = std::pow(2, 7) - 1;
    // if (data_type == DT_INT8) {
    //     critical_value = std::pow(2, 7) - 1;
    // } else if (data_type == DT_INT16) {
    //     critical_value = std::pow(2, 15) - 1;
    // }

    QuantParam quant_param;
    for (unsigned int i = 0; i < abs_max.size(); i++) {
        if (abs_max[i] == 0) {
            position[i] = 0;
            scale[i] = 1;
        } else {
            position[i] = log2(abs_max[i] / critical_value);
            position[i] += position[i] > 0 ? 1 : 0;
            scale[i] = critical_value * pow(2, static_cast<int>(position[i])) / abs_max[i];
        }
        if (position[i] > 32) position[i] = 32;
        if (position[i] < -32) position[i] = -32;
        if (mode == "common" || mode == "int8_channel" || lrn) {
            // blob_dtype.set_type(data_type);
            // blob_dtype.add_position(position[i]);
            quant_param.position = position[i];
            // blob_dtype.add_scale(scale[i]);
            quant_param.scale = scale[i];
        } else if (mode == "scale") {
            float new_scale =  pow(2, static_cast<int>(-position[i])) * scale[i];
            // blob_dtype.set_type(data_type);
            // blob_dtype.add_scale(new_scale);
            quant_param.position = -999999;
            quant_param.scale = new_scale;
        }
    }
    return quant_param;
}


QuantParam QuantTool::getQuantParam(const vector<float> input_data,
                                    string layer_name) {
    LayerType layer_type = CONVOLUTION;
    int iteration = input_data.size();
    return getInt8Info(input_data, layer_name, layer_type, "common", false, &_max_value, false);
}



