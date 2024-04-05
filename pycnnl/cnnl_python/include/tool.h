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
#ifndef SAMPLES_CONV_SAMPLE_TOOL_H_
#define SAMPLES_CONV_SAMPLE_TOOL_H_

#include "public.h"
#include <vector>
#include <map>
#include <string>


using std::vector;
using std::map;
using std::string;



//#define SWITCH_CHAR ('-') //需要修改注释
#define OPT_LEN (2)


typedef enum {
    CAST = 0,
    CONVOLUTION = 1,
    LRN = 2,
    MLP = 3,
    NORMALIZE = 4,
    RELU = 5,
    SOFTMAX =6,
    POOL = 7,
    FLATTEN = 8
} LayerType;



struct QuantParam {
    int position = 0;
    float scale = 0;
    QuantParam(): position(1), scale(1) {};
    QuantParam(int p, float s): position(p), scale(s) {};
};


class QuantTool {
    public:
    QuantParam getQuantParam(const vector<float> input_data,
                             string layer_name);
    private:
    std::map<string, float> _max_value;
};




struct Kernel {
  int kh = 0;
  int kw = 0;
  int sh = 1;
  int sw = 1;
  int dh = 1;
  int dw = 1;
};

struct Shape2D {
  int n = 0;
  int c = 0;
  int h = 0;
  int w = 0;
  inline int size() { return n * c * h * w; }
};

struct Pad {
  int pt = 0;
  int pb = 0;
  int pl = 0;
  int pr = 0;
};

struct DataType {
  cnnlDataType_t input_dtype;
  cnnlDataType_t weight_dtype;
  cnnlDataType_t output_dtype;
  cnnlTensorLayout_t layout = CNNL_LAYOUT_NHWC;
};

struct ShapeParam {
  Shape2D input;
  Shape2D weight;
  Shape2D output;
  Shape2D bias;
  Kernel kernel;
  Pad pad;
  DataType datainfo;
  bool has_bias = false;
  int group_count = 1;
};

struct DataAddress {
  float *cpu_data = nullptr;  // repack quantized data used for cpu compute
  float *fp_data  = nullptr;  // store init random data
  void *host      = nullptr;  // store casted data
  void *device    = nullptr;  // mlu device address
  size_t mlu_size = 0;        // mlu malloc size
  size_t fp_size  = 0;        // cpu random data size
};

struct HostTimer {
  struct timespec t0 = {0, 0};
  struct timespec t1 = {0, 0};
  double tv_nsec     = 0.0;
  double tv_sec      = 0.0;
  double tv_usec     = 0.0;
  void start() { clock_gettime(CLOCK_MONOTONIC, &t0); }
  void stop() {
    clock_gettime(CLOCK_MONOTONIC, &t1);
    tv_nsec = (double)t1.tv_nsec - (double)t0.tv_nsec;
    tv_sec  = (double)t1.tv_sec - (double)t0.tv_sec;
    tv_usec = tv_nsec / 1000 + tv_sec * 1000 * 1000;
  }
};

void initDevice(int &dev, cnrtQueue_t &queue, cnnlHandle_t &handle);

size_t dataSize(cnnlDataType_t dtype);

cnrtDataType_t convertCnnlDtypeToCnrt(cnnlDataType_t dtype);

void getPosition(float *input, size_t num, cnnlDataType_t datatype, int *position);

void getPositionAndScale(float *input, size_t size, cnnlDataType_t dtype, int *pos, float *scale);

void castData(float *src_data,
              cnnlDataType_t src_dtype,
              char *dst_data,
              cnnlDataType_t dst_dtype,
              float *dequantify_data,
              int quant_mode,
              size_t size,
              int &pos,
              float &scale,
              int &offset);

void parserParam(int argc, char *argv[], ShapeParam &param);

void setTensorDesc(cnnlTensorDescriptor_t &desc,
                     Shape2D shape,
                     cnnlDataType_t dtype,
                     cnnlTensorLayout_t layout);

float *mallocDataRandf(int size, int low, int hight);

void saveDataToFile(char const *file, float *data, size_t count);

void saveHexDataToFile(char const *file, void *data, cnnlDataType_t dtype, size_t count);

double computeDiff1(float *cpu_result, float *mlu_result, size_t count);

double computeDiff2(float *cpu_result, float *mlu_result, size_t count);

#endif  // SAMPLES_CONV_SAMPLE_TOOL_H_
