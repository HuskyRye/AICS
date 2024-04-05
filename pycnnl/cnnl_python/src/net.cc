#include "net.h"
#include<sys/time.h>


#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;




//保存txt
int savetxt(float * cpudata,string fname,int datalenth)
{
	ofstream dataFile;
	
	dataFile.open(fname, ofstream::app);
        

	for(int i=0;i < datalenth; i++)
	{
           dataFile << cpudata[i] << std::endl; 

	}
	dataFile.close();

	return 0;

}


CnnlNet::CnnlNet()
{
    
    initDevice(_dev, _queue, _handle);
   

    _isFirstLayer = true;
   
    std::cout << "Init success: "  << std::endl;
    
}


CnnlNet::~CnnlNet() {
   
    for (uint i = 0; i < _layerList.size(); i++) {
         //std::cout << "delete1: " <<i << std::endl;


    	    
	if( _layerList[i]!=NULL)
	{
//	  delete _layerList[i];
	}
    
    }
    
    if(_input_mlu_ptr!=NULL)
    {
       CNRT_CHECK(cnrtFree(_input_mlu_ptr));
       _input_mlu_ptr=NULL;
       
    }
    

    if(_inputData.size()>0)
    {
       _inputData.clear();
      
    }
   

    if(_outputData.size()>0)
    {
       _outputData.clear();
       
    }

    CNNL_CHECK(cnnlDestroy(_handle));
    CNRT_CHECK(cnrtQueueDestroy(_queue));

}



void CnnlNet::setInputShape(int dim_1, int dim_2, int dim_3, int dim_4) {
    _inputShape.resize(4);
    _inputShape[0] = dim_1;
    _inputShape[1] = dim_2;
    _inputShape[2] = dim_3;
    _inputShape[3] = dim_4;

    _outputShape.resize(4);
    _outputShape = _inputShape;

    _inputData.resize(dim_1 * dim_2 * dim_3 * dim_4);

    

}

void CnnlNet::setInputShape(int dim_1, int dim_2) {
    _inputShape.resize(2);
    _inputShape[0] = dim_1;
    _inputShape[1] = dim_2;
   
    _outputShape.resize(2);
    _outputShape = _inputShape;
    _inputData.resize(dim_1 * dim_2);

}





void CnnlNet::setOutputShape(int dim_1, int dim_2, int dim_3) {
   
    _outputShape.resize(3);
    _outputShape[0] = dim_1;
    _outputShape[1] = dim_2;
    _outputShape[2] = dim_3;
   

    _outputData.resize(dim_1 * dim_2 * dim_3);

}




void CnnlNet::setOutputShape(int dim_1, int dim_2) {
   
    _outputShape.resize(2);
    _outputShape[0] = dim_1;
    _outputShape[1] = dim_2;
   
    _outputData.resize(dim_1 * dim_2);


}



void CnnlNet::setOutputShape(int dim_1, int dim_2, int dim_3,int dim_4) {
  
    _outputShape.resize(4);
    _outputShape[0] = dim_1;
    _outputShape[1] = dim_2;
    _outputShape[2] = dim_3;
    _outputShape[4] = dim_4;
   

    _outputData.resize(dim_1 * dim_2 * dim_3*dim_4);


}






//1.创建conv层

void CnnlNet::createConvLayer(string layer_name,std::vector<int>input_shape,int out_channel,int kernel_size,int stride,int dilation,int pad)	
{
    
   
    std::vector<int> kernel_vector= {kernel_size, kernel_size};
    std::vector<int> stride_vector = {stride, stride};
    std::vector<int> dilation_vector = {dilation, dilation};
    std::vector<int> pad_vector = {pad, pad, pad, pad};
    
    int input_position = 1;
    float input_scale = 1;

  

   
    int out_height=((input_shape)[2] + 2 * pad - kernel_size)/stride + 1;
    int out_width=((input_shape)[3] + 2 * pad - kernel_size)/stride + 1;

    std::vector<int> output_shape={input_shape[0],out_channel,out_height, out_width};

    _outputShape[0] = input_shape[0];
    _outputShape[1] = out_channel;
    _outputShape[2] = out_height;
    _outputShape[3] = out_width;


    bool has_bias=true;
    CnnlConvLayer * convlayer = new CnnlConvLayer(_handle,_queue,input_shape,output_shape,kernel_vector,stride_vector,dilation_vector,pad_vector,input_position,input_scale,has_bias);
    _layerList.push_back(new Layer(convlayer, layer_name, CONVOLUTION, false));
}

//2.创建relu层

void CnnlNet::createReLuLayer(string layer_name) {
    
     std::vector<int>* input_shape;
     _isFirstLayer=false; 

    if (_isFirstLayer) {
        if (_inputShape.empty()) {
            std::clog << "ERROR : The input shape is empty ! You should set input shape first .\n";
            exit(1);
        }
        input_shape = &_inputShape;
        std::cout << "input_shape: [" << _inputShape[0] << " "
                                   << _inputShape[1] << " "
                                   << _inputShape[2] << " "
                                   << _inputShape[3] << "]\n";
        _isFirstLayer = false;
    } else {
        input_shape = &_outputShape;
    }

    std::cout << "creating relu layer ..." << std::endl;

  
    CnnlReLuLayer * relulayer = new CnnlReLuLayer(_handle,_queue,*input_shape);
    
    _layerList.push_back(new Layer(relulayer, layer_name, RELU, false));
}

//3.创建softmax层

void CnnlNet::createSoftmaxLayer(string layer_name, std::vector<int> input_shape,int axis) {
   
 

    _outputShape.resize(3);
    _outputShape[0] = input_shape[0];
    _outputShape[1] = input_shape[1];
    _outputShape[2] = input_shape[2];
   


    std::cout << "softmax output_shape: [" << _outputShape[0] << " "
                                   << _outputShape[1] << " "
                                   << _outputShape[2] << " "<< std::endl;

    
    CnnlSoftmaxLayer * softmaxlayer = new CnnlSoftmaxLayer(_handle,_queue,input_shape, axis);

    _layerList.push_back(new Layer(softmaxlayer, layer_name, SOFTMAX, false));
}

//4.创建pooling层

void CnnlNet::createPoolingLayer(string layer_name,std::vector<int> input_shape,int kernel_size,int stride) 
{
    
	std::cout << "creating pooling layer ..." << std::endl;
   

    std::vector<int> kernel_vector = {kernel_size, kernel_size};
    std::vector<int> stride_vector = {stride, stride};

    const int pooled_height = static_cast<int>(floor(static_cast<float>((input_shape)[2] - kernel_size) /stride)) + 1;
    const int pooled_width = static_cast<int>(floor(static_cast<float>((input_shape)[3] - kernel_size) /stride)) + 1;


    std::cout << "poolinglayer output_shape: [" << input_shape[0] << " "
                                   << input_shape[1] << " "
                                   << pooled_height << " "
                                   << pooled_width << "]"<<std::endl;

    

    std::vector<int> output_shape={input_shape[0],input_shape[1],pooled_height, pooled_width};
    

    _outputShape[0] = input_shape[0];
    _outputShape[1] = input_shape[1];
    _outputShape[2] = pooled_height;
    _outputShape[3] = pooled_width;

    CnnlPoolingLayer * poolinglayer = new  CnnlPoolingLayer(_handle, _queue,input_shape,output_shape,kernel_vector,stride_vector);
    


    _layerList.push_back(new Layer(poolinglayer, layer_name, POOL, false));
}



//6 mlp  output
void CnnlNet::createMlpLayer(string layer_name,std::vector<int> input_shape, std::vector<int> weight_shape, std::vector<int> output_shape)
{
 
 
    std::cout << "creating mlp layer ..." << std::endl;

    

    if(weight_shape.size()==3)
    {
	_outputShape.resize(3);
        _outputShape[0] = output_shape[0];
        _outputShape[1] = output_shape[1];
        _outputShape[2] = output_shape[2];


    }else if(weight_shape.size()==4)
    {
       _outputShape.resize(4);
        _outputShape[0] = output_shape[0];
        _outputShape[1] = output_shape[1];
        _outputShape[2] = output_shape[2];
	   _outputShape[3] = output_shape[3];

	

    }
    else if(weight_shape.size()==2)
    {
      
	    _outputShape.resize(2);
        _outputShape[0] = output_shape[0];
        _outputShape[1] = output_shape[1];


    }

   
   int input_position = 1;
   float input_scale = 1;
  
   CnnlMlpLayer * mlplayer = new CnnlMlpLayer(_handle, _queue,input_shape,weight_shape,output_shape,input_position,input_scale);

    _layerList.push_back(new Layer(mlplayer, layer_name, MLP, false));



}




//

void CnnlNet::setInputData(std::vector<float> data) {
    _inputData = data;
    // malloc cnml tensor
    cnrtMalloc(&_input_mlu_ptr, _inputData.size() * sizeof(float));
    // copy input to cnnl buffer
    cnrtMemcpy(_input_mlu_ptr, _inputData.data(), _inputData.size() * sizeof(float), CNRT_MEM_TRANS_DIR_HOST2DEV);
}


void CnnlNet::forward() {
    void *output_mlu_ptr = _input_mlu_ptr;
    float* outresult;
    int outlenth=1;
    
    for (unsigned int i = 0; i < _layerList.size(); i++) {
        //std::cout <<"zkgforward:"<<_layerList[i]->type<<" 层数："<<i << std::endl;
        switch (_layerList[i]->type) {
	   
            case CONVOLUTION:
            {
                
		
		if (_layerList[i]->isParamLoaded == false) {
                    std::clog << "ERROR: param of layer " << _layerList[i]->name << " is not loaded !\n";
                    exit(1);
                }
                CnnlConvLayer* convlayer = static_cast<CnnlConvLayer*>(_layerList[i]->layer);
                
	        output_mlu_ptr = convlayer->forward(output_mlu_ptr);
		       
		
                //CNRT_CHECK(cnrtQueueSync(_queue));
		
                break;
            }
            case MLP:
            {
	     
                if (_layerList[i]->isParamLoaded == false) {
                    std::clog << "ERROR: param of layer " << _layerList[i]->layer << " is not loaded !\n";
                    exit(1);
                }
                CnnlMlpLayer* mlplayer = static_cast<CnnlMlpLayer*>(_layerList[i]->layer);
		
		output_mlu_ptr = mlplayer->forward(output_mlu_ptr);
		
		//CNRT_CHECK(cnrtQueueSync(_queue));
                break;
            }
            case RELU:
            {
                CnnlReLuLayer* relulayer = static_cast<CnnlReLuLayer*>(_layerList[i]->layer);
		
		output_mlu_ptr = relulayer->forward(output_mlu_ptr);
		        
		                  
	
		       //CNRT_CHECK(cnrtQueueSync(_queue));
                break;
            }
            case SOFTMAX:
            {
                CnnlSoftmaxLayer* softmaxlayer = static_cast<CnnlSoftmaxLayer*>(_layerList[i]->layer);
		
                output_mlu_ptr = softmaxlayer->forward(output_mlu_ptr);
		 
                //outresult=softmaxlayer->getoutputCpuData();
		
                std::cout << "****网络推理完成 ...******" << std::endl;
                break;
            }
            case POOL:
            {
                CnnlPoolingLayer* poolinglayer = static_cast<CnnlPoolingLayer*>(_layerList[i]->layer);
		
                output_mlu_ptr = poolinglayer->forward(output_mlu_ptr);
		 
                //CNRT_CHECK(cnrtQueueSync(_queue));
                break;
            }
            case FLATTEN:
            {
                //CnmlFlattenLayer* flattenlayer = static_cast<CnmlFlattenLayer*>(_layerList[i]->layer);
                //output_mlu_ptr = flattenlayer->forward(output_mlu_ptr, _queue);
                break;
            }
            case CAST:
            {
                //CnnlCastLayer* castlayer = static_cast<CnmlCastLayer*>(_layerList[i]->layer);
                //output_mlu_ptr = castlayer->forward(output_mlu_ptr, _queue);
                break;
            }
            default:
            {
                std::clog << "Error: Not support this layer type: " << _layerList[i]->type << std::endl;
                exit(1);
            }
        }
    }
    
    int output_size =1;
    for(int i=0;i<_outputShape.size();i++)
    {
       if(_outputShape[i]>0)
       {
	        output_size= output_size *_outputShape[i];
       }
    }
   
    _outputData.resize(output_size);
   
    CNRT_CHECK(cnrtQueueSync(_queue));
   //数据拷贝20230614
    //CNRT_CHECK(cnrtMemcpy(_output_cpu_ptr, _output_mlu_ptr, _output_length * sizeof(float), CNRT_MEM_TRANS_DIR_DEV2HOST));
   cnrtMemcpy(_outputData.data(), output_mlu_ptr, output_size * sizeof(float),CNRT_MEM_TRANS_DIR_DEV2HOST);
    
   //for(int i=0;i< output_size;i++)
  // {
  //	  _outputData[i]=outresult[i];
	 
  // }
   
}




std::vector<float> CnnlNet::getOutputData() 
{
    return _outputData;
}




void CnnlNet::loadParams(int layer_id,std::vector<float> filter_data,std::vector<float> bias_data) {
    
    if (_layerList.back()->type != CAST) {
       
    }
    

    std::cout << "loading params for layer " << _layerList[layer_id]->name << " ..." << std::endl;
   

     int filter_position = 1;
    float filter_scale = 1;

    
    if (_layerList[layer_id]->type == CONVOLUTION) {
        CnnlConvLayer* convlayer = static_cast<CnnlConvLayer*>(_layerList[layer_id]->layer);
        convlayer->loadParam(filter_data, bias_data, filter_position, filter_scale);
    } else if (_layerList[layer_id]->type == MLP) {

        CnnlMlpLayer* mlplayer = static_cast<CnnlMlpLayer*>(_layerList[layer_id]->layer);
        mlplayer->loadParam(filter_data, bias_data, filter_position, filter_scale);
    } else {
        std::clog << "ERROR : This layer is not conv or mlp !\n";
        std::clog << "\tlayer name is : " << _layerList[layer_id]->name << std::endl;
        exit(1);
    }
    _layerList[layer_id]->isParamLoaded = true;
}


void  CnnlNet::insertCastLayer(cnnlCastDataType_t cast_type)
{

   // insert the cast out layer
   /*
    CnnlCastLayer *castlayer = new CnnlCastLayer(_outputShape, cast_type);
    string layer_name;
    if (cast_type == CNNL_CAST_FLOAT32_TO_FLOAT16) {
        layer_name = "cast_in";
    } else if (cast_type == CNNL_CAST_FLOAT16_TO_FLOAT32) {
        layer_name = "cast_out";
    } else {
        std::clog << "Error: Not support this cast type yet: "
                  << cast_type << std::endl;
        exit(1);
    }
    _layerList.push_back(new Layer(castlayer, layer_name, CAST, false));
  */
	
}



string CnnlNet::getLayerName(int layer_id) {
    
    return _layerList[layer_id]->name;
}


int CnnlNet::size() {
    
    return _layerList.size();
}


bool CnnlNet::needToBeQuantized(int layer_id) {
    return _layerList[layer_id]->type == CONVOLUTION || _layerList[layer_id]->type == MLP;
}




