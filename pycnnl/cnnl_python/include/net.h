#ifndef PYTHON_CNNL_NET_H_
#define PYTHON_CNNL_NET_H_

#include <string.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <memory>
#include <math.h>
#include <utility>
#include "layers.h"
#include "tool.h"


using std::vector;
using std::pair;
using std::make_pair;
using std::string;


struct Layer {
    CnnlLayer *layer;
    string name;
    LayerType type;
    bool isParamLoaded;
    Layer() = delete;
    Layer(CnnlLayer *layer,string name,LayerType type,bool is_param_loaded): layer(layer), name(name), type(type), isParamLoaded(is_param_loaded) 
    {

    }
    ~Layer() 
    {
        if (layer != NULL) 
	{
            delete layer;
        }
    }
};



class CnnlNet {
    public:
    
    CnnlNet();
    ~CnnlNet();
    void setInputShape(int dim_1, int dim_2, int dim_3, int dim_4);
    void setInputShape(int dim_1, int dim_2);
    void setOutputShape(int dim_1, int dim_2, int dim_3,int dim_4);
    void setOutputShape(int dim_1, int dim_2, int dim_3);
    void setOutputShape(int dim_1, int dim_2);
    
    void createConvLayer(string layer_name,std::vector<int>input_shape,int out_channel,int kernel_size,int stride,int dilation,int pad);
    
    void createMlpLayer(string layer_name,std::vector<int> input_shape, std::vector<int> weight_shape, std::vector<int> output_shape);
    void createReLuLayer(string layer_name);
    void createSoftmaxLayer(string layer_name,std::vector<int> input_shape,int axis);
    void createPoolingLayer(string layer_name,std::vector<int> input_shape,int kernel_size,int stride);
    
    void setInputData(std::vector<float> data);
    void forward();
    std::vector<float> getOutputData();
    
    void loadParams(int layer_id,std::vector<float> filter_data,std::vector<float> bias_data);

    int size();
    string getLayerName(int layer_id);
    bool needToBeQuantized(int layer_id);//是否需要量化
    private:
    void insertCastLayer(cnnlCastDataType_t cast_type);
    bool _isFirstLayer;
   
    std::vector<Layer*> _layerList;
    std::vector<int> _inputShape;
    std::vector<int> _outputShape;
    void* _input_mlu_ptr=NULL;
    std::vector<float> _inputData;//输入数据
    std::vector<float> _outputData;//输出数据
    cnrtQueue_t _queue = nullptr;
    cnnlHandle_t _handle = nullptr;
    
    int  _dev;


};

#endif  // PYTHON_CNNL_TEST_MLP_H_

