#ifndef PYTHON_CNNL_LAYERS_H_
#define PYTHON_CNNL_LAYERS_H_
#include <time.h>
#include <string>
#include "string.h"
#include "tool.h"

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "cnnl.h"
#include "cnrt.h"


using std::vector;


#define CONV_2D 4

typedef struct Convolution_ {
  cnnlTensorDescriptor_t input_desc = nullptr;
  cnnlTensorDescriptor_t weight_desc = nullptr;
  cnnlTensorDescriptor_t output_desc = nullptr;
  cnnlTensorDescriptor_t bias_desc = nullptr;
  cnnlConvolutionDescriptor_t conv_desc = nullptr;
  cnnlConvolutionForwardAlgo_t algo;
  DataAddress input_data;
  DataAddress weight_data;
  DataAddress output_data;
  DataAddress bias_data;
  void *workspace = nullptr;
  size_t workspace_size = 0;
  double diff1 = 0.0;
  double diff2 = 0.0;
  float hardware_time = 0.0;    // mlu compute time
  float interface_time = 0.0;   // cnnlConvolutionForward host time
  float end2end_time = 0.0;     // copy data in + mlu compute + copy data out
  float memcpyH2D_time = 0.0;   // copy data in(include input, weight, bias)
  float memcpyD2H_time = 0.0;   // copy data out(output)
  float cpu_compute_time = .0;  // cpu compute
} Convolution;


class CnnlLayer{};

class CnnlConvLayer: public CnnlLayer {
    public:
    CnnlConvLayer() = delete;
    CnnlConvLayer(cnnlHandle_t handle,cnrtQueue_t queue,std::vector<int> input_shape,
                  std::vector<int> output_shape,
                  std::vector<int> kernel_shape,
                  std::vector<int> stride,
                  std::vector<int> dilation,
                  std::vector<int> pad,
                  int input_position,
                  float input_scale,
		  bool has_bias);
    ~CnnlConvLayer();
    
    void *forward(void *input_mlu_ptr);
    float* getoutputCpuData();
    int getoutputCpulenth();

    //加载数据权重
    void loadParam(std::vector<float> filter_data,std::vector<float> bias_data,int filter_position,float filter_scale);
    private:
    Convolution _conv;
    ShapeParam _conv_param;
   
    cnrtQueue_t _queue = nullptr;
    cnnlHandle_t _handle = nullptr;

    int _output_count;
    int _batchsize=1;
    

    cnnlTensorDescriptor_t _input_desc = nullptr;
    cnnlTensorDescriptor_t _weight_desc = nullptr;
    cnnlTensorDescriptor_t _output_desc = nullptr;
    cnnlTensorDescriptor_t _bias_desc = nullptr;
    cnnlConvolutionDescriptor_t _conv_desc = nullptr;
    cnnlConvolutionForwardAlgo_t _algo;
    size_t _workspace_size = 0;
    void *_workspace = nullptr;



    void *_output_mlu_ptr;
    int _dimNum;
    int _kernel_h;
    int _kernel_w;
    int _stride_h;
    int _stride_w;
    int _dilation_h;
    int _dilation_w;
    int _pad_htop;
    int _pad_wleft;
    int _pad_hbottom;
    int _pad_wright;
};


class CnnlMlpLayer: public CnnlLayer {
    public:
    CnnlMlpLayer() = delete;
    CnnlMlpLayer(cnnlHandle_t handle, cnrtQueue_t  queue,std::vector<int> input_shape, std::vector<int> weight_shape,std::vector<int> output_shape,int input_position,float input_scale);
    ~CnnlMlpLayer();
    
    void *forward(void *input_mlu_ptr);
    float* getoutputCpuData();
    int getoutputCpulenth();
    //加载数权重
    void loadParam(std::vector<float> filter_data,std::vector<float> bias_data,int filter_position,float filter_scale);
    private:
    int _output_count;
    cnrtQueue_t _queue = nullptr;
    cnnlHandle_t _handle = nullptr;

    
    cnnlDataType_t _DataType;
    cnnlTensorDescriptor_t  _input_desc;
    cnnlTensorDescriptor_t  _weight_desc;
    cnnlTensorDescriptor_t  _output_desc;
    cnnlTensorDescriptor_t _bias_desc;

    //
   
    bool _is_havebias=true;
    size_t _input_length = 1;
    size_t _weight_length = 1;
    size_t _output_length = 1;
    size_t _bias_length = 1;

    size_t _batchsize=1;

    float *_input_cpu_ptr;
    float *_weight_cpu_ptr;
    float *_bias_cpu_ptr;
    float *_output_cpu_ptr;
    float *_alpha_cpu_ptr;
    float *_beta_cpu_ptr; 

    size_t _workspace_size = 0;
    void *_workspace = nullptr;


    void *_input_mlu_ptr;
    void *_weight_mlu_ptr;
    void *_bias_mlu_ptr;
    void *_output_mlu_ptr;
    bool _is_transa=false;
    bool _is_transb=false;

    //添加bias处理功能

};


class CnnlReLuLayer: public CnnlLayer {
    public:
    CnnlReLuLayer() = delete;
    CnnlReLuLayer(cnnlHandle_t handle,cnrtQueue_t queue,std::vector<int> input_shape);
    ~CnnlReLuLayer();
    
    void *forward(void *input_mlu_ptr);
    float* getoutputCpuData();
    int getoutputCpulenth();

    private:
    int _output_count;
    
    cnrtQueue_t _queue = nullptr;
    cnnlHandle_t _handle = nullptr;

   
    cnnlActivationMode_t _active_mode=CNNL_ACTIVATION_RELU;
    cnnlDataType_t _DataType;
    cnnlTensorDescriptor_t _input_desc;
    cnnlTensorDescriptor_t _output_desc;
    cnnlActivationDescriptor_t _active_desc;

    void *_input_mlu_ptr;
    void *_output_mlu_ptr;
    size_t _input_length = 1;
    size_t _output_length = 1;


    float *_input_cpu_ptr;
    float *_output_cpu_ptr;

    
};

class CnnlSoftmaxLayer: public CnnlLayer {
    public:
    CnnlSoftmaxLayer() = delete;
    CnnlSoftmaxLayer(cnnlHandle_t handle,cnrtQueue_t queue,std::vector<int> input_shape, int axis);
    ~CnnlSoftmaxLayer();
    
    void *forward(void *input_mlu_ptr);
    float* getoutputCpuData();
    int getoutputCpulenth();
    private:
    int _output_count;
    

    cnrtQueue_t _queue = nullptr;
    cnnlHandle_t _handle = nullptr;


     cnnlComputationPreference_t _prefer= CNNL_COMPUTATION_HIGH_PRECISION;

     cnnlDataType_t _DataType;
     cnnlSoftmaxMode_t _soft_mode=CNNL_SOFTMAX_MODE_HIGH_DIMENSION;
     cnnlTensorDescriptor_t _input_desc;
     cnnlTensorDescriptor_t _output_desc;
     cnnlSoftmaxAlgorithm_t _algorithm=CNNL_SOFTMAX_ACCURATE;
     void *_input_mlu_ptr;
     void *_output_mlu_ptr;
     size_t _input_length = 1;
     size_t _output_length = 1;
     float *_input_cpu_ptr;
     float *_output_cpu_ptr;


   
};



class CnnlPoolingLayer: public CnnlLayer {
    public:
    CnnlPoolingLayer() = delete;
    CnnlPoolingLayer(cnnlHandle_t handle,cnrtQueue_t queue,std::vector<int> input_shape,std::vector<int> output_shape,
                     std::vector<int> kernel_shape,
                     std::vector<int> stride);
    ~CnnlPoolingLayer();
    
    void *forward(void *input_mlu_ptr);
    float* getoutputCpuData();
    int getoutputCpulenth();
    private:
    int _output_count;
    cnrtQueue_t _queue = nullptr;
    cnnlHandle_t _handle = nullptr;

    
    cnnlDataType_t _DataType=CNNL_DTYPE_FLOAT;
    cnnlPoolingMode_t  _pool_mode=CNNL_POOLING_MAX;
    cnnlTensorDescriptor_t _input_desc;
    cnnlTensorDescriptor_t _output_desc;
    cnnlNanPropagation_t  _maxpooling_nan_opt=CNNL_NOT_PROPAGATE_NAN;
    cnnlPoolingDescriptor_t _pooling_desc;
    size_t _workspace_size = 0;
    void *_workspace = nullptr;
    size_t _input_length = 1;
    size_t _output_length = 1;
    float *_input_cpu_ptr;
    float *_output_cpu_ptr;

    void *_input_mlu_ptr;
    void *_output_mlu_ptr;
};


class CnnlCastLayer: public CnnlLayer {
    public:
    CnnlCastLayer() = delete;
    CnnlCastLayer(cnnlHandle_t handle,cnrtQueue_t queue,std::vector<int> input_shape,  cnnlCastDataType_t cast_type);
    ~CnnlCastLayer();
    
    void *forward(void *input_mlu_ptr);
    private:
    int _output_count;
    

    cnnlDataType_t _DataType;
    cnnlCastDataType_t _cast_type;
    cnnlTensorDescriptor_t _input_desc;
    cnnlTensorDescriptor_t _output_desc;
    void *_input_mlu_ptr;
    void *_output_mlu_ptr;

    size_t _input_length = 1;
    size_t _output_length = 1;
    float *_input_cpu_ptr;
    float *_output_cpu_ptr;

    bool _is_transa=false;
    bool _is_transb=false;
    cnrtQueue_t _queue = nullptr;
    cnnlHandle_t _handle = nullptr;


    
};
#endif  // PYTHON_CNNL_LAYERS_H
