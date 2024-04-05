#include "layers.h"


//conv实现


//初始化
int initparam(ShapeParam &conv_param,
	      std::vector<int> input_shape,
              std::vector<int> output_shape,
              std::vector<int> kernel_shape,
	      std::vector<int> stride,
	      std::vector<int> dilation,
              std::vector<int> pad,
              int input_position,
              float input_scale,bool has_bias)
{



  conv_param.datainfo.input_dtype= CNNL_DTYPE_FLOAT;
  conv_param.datainfo.weight_dtype= CNNL_DTYPE_FLOAT;
  conv_param.datainfo.output_dtype= CNNL_DTYPE_FLOAT;

  conv_param.datainfo.layout=CNNL_LAYOUT_NHWC;
   
  //input input shape
  conv_param.input.n=input_shape[0];
  conv_param.input.c=input_shape[1];
  conv_param.input.h=input_shape[2];
  conv_param.input.w=input_shape[3];



  //output  output shape
  
  conv_param.output.n=conv_param.input.n;
  conv_param.output.c=output_shape[1];
  

  conv_param.kernel.sh=stride[0]; //stride
  conv_param.kernel.sw=stride[1];
  conv_param.kernel.dh=dilation[0]; //dilation数值调试
  conv_param.kernel.dw=dilation[1]; //
  conv_param.kernel.kh=kernel_shape[0]; //
  conv_param.kernel.kw=kernel_shape[1];



  conv_param.weight.n=conv_param.output.c;
  conv_param.weight.c=conv_param.input.c;
  conv_param.weight.h=conv_param.kernel.kh;
  conv_param.weight.w=conv_param.kernel.kw;


  //bias  bias shape
  conv_param.has_bias=has_bias;

  if(has_bias)
  {
   conv_param.bias.c=conv_param.output.c;
   conv_param.bias.n=1;
   conv_param.bias.h=1;
   conv_param.bias.w=1;

  }


  

  conv_param.pad.pt=pad[0];
  conv_param.pad.pb=pad[1];
  conv_param.pad.pl=pad[2];
  conv_param.pad.pr=pad[3];



  // compute output shape
  int expand_kh = (conv_param.kernel.kh - 1) * conv_param.kernel.dh + 1;
  int expand_kw = (conv_param.kernel.kw - 1) * conv_param.kernel.dw + 1;
  int ho = (conv_param.input.h + conv_param.pad.pt + conv_param.pad.pb - expand_kh) / conv_param.kernel.sh + 1;
  int wo = (conv_param.input.w + conv_param.pad.pl + conv_param.pad.pr - expand_kw) / conv_param.kernel.sw + 1;
  
  conv_param.output.h=ho;
  conv_param.output.w=wo;

  conv_param.group_count=1;



   return 0;
}




int initconv(cnnlHandle_t handle,Convolution& conv,ShapeParam param)
{
  //device 创建desc
  
  setTensorDesc(conv.input_desc, param.input, param.datainfo.input_dtype, param.datainfo.layout);
  setTensorDesc(conv.weight_desc, param.weight, param.datainfo.weight_dtype, param.datainfo.layout);
  setTensorDesc(conv.output_desc, param.output, param.datainfo.output_dtype, param.datainfo.layout);
  

  if (param.has_bias) {
    setTensorDesc(conv.bias_desc, param.bias, param.datainfo.output_dtype, param.datainfo.layout);
    conv.bias_data.fp_size = param.bias.size() * sizeof(float);
    conv.bias_data.mlu_size = param.bias.size() * dataSize(param.datainfo.output_dtype);
    
  }
  //
  int pad[4] = {param.pad.pt, param.pad.pb, param.pad.pl, param.pad.pr};
  int stride[2] = {param.kernel.sh, param.kernel.sw};
  int dilation[2] = {param.kernel.dh, param.kernel.dw};
  //创建卷积desc
  CNNL_CHECK(cnnlCreateConvolutionDescriptor(&conv.conv_desc));
  conv.algo = CNNL_CONVOLUTION_FWD_ALGO_DIRECT;
 
  CNNL_CHECK(cnnlSetConvolutionDescriptor(conv.conv_desc, CONV_2D, pad, stride, dilation,param.group_count, CNNL_DTYPE_FLOAT));
  
  
  CNNL_CHECK(cnnlGetConvolutionForwardWorkspaceSize(
      handle, conv.input_desc, conv.weight_desc, conv.output_desc, conv.bias_desc, conv.conv_desc,
      conv.algo, &(conv.workspace_size)));

  conv.input_data.fp_size = param.input.size() * sizeof(float);
  conv.input_data.mlu_size = param.input.size() * dataSize(param.datainfo.input_dtype);

  conv.weight_data.fp_size = param.weight.size() * sizeof(float);
  conv.weight_data.mlu_size = param.weight.size() * dataSize(param.datainfo.weight_dtype);

  conv.output_data.fp_size = param.output.size() * sizeof(float);
  conv.output_data.mlu_size = param.output.size() * dataSize(param.datainfo.output_dtype);
  //************device端初始化*************
  

  CNRT_CHECK(cnrtMalloc(&(conv.weight_data.device), conv.weight_data.mlu_size));
  CNRT_CHECK(cnrtMemset(conv.weight_data.device, 0, conv.weight_data.mlu_size));

  CNRT_CHECK(cnrtMalloc(&(conv.output_data.device), conv.output_data.mlu_size));
  CNRT_CHECK(cnrtMemset(conv.output_data.device, 0, conv.output_data.mlu_size));

  
  if (param.has_bias)
  {
    CNRT_CHECK(cnrtMalloc(&(conv.bias_data.device), conv.bias_data.mlu_size));
    CNRT_CHECK(cnrtMemset(conv.bias_data.device, 0, conv.bias_data.mlu_size));
  }

  if (conv.workspace_size != 0) {
    CNRT_CHECK(cnrtMalloc(&(conv.workspace), conv.workspace_size));
    CNRT_CHECK(cnrtMemset(conv.workspace, 0, conv.workspace_size));
  }

   //************host端初始化*************

    // generate random data
  int low = -1, hight = 1;
  conv.input_data.fp_data = mallocDataRandf(param.input.size(), low, hight);
  conv.input_data.cpu_data = (float *)malloc(param.input.size() * sizeof(float));
  conv.input_data.host = (char *)malloc(conv.input_data.mlu_size);

  conv.weight_data.fp_data = mallocDataRandf(param.weight.size(), low, hight);
  conv.weight_data.cpu_data = (float *)malloc(param.weight.size() * sizeof(float));
  conv.weight_data.host = (char *)malloc(conv.weight_data.mlu_size);
  

  /***********************************************/
   unsigned int seed = 2;

  for (size_t idx = 0; idx < param.weight.size(); idx++) {
        conv.weight_data.cpu_data[idx] = rand_r(&seed) % 10;


    }
   
 CNRT_CHECK(cnrtMemcpy(conv.weight_data.device,conv.weight_data.fp_data, conv.weight_data.mlu_size,CNRT_MEM_TRANS_DIR_HOST2DEV)); 
/*****************************************************/


  conv.output_data.fp_data = (float *)malloc(conv.output_data.fp_size);
  conv.output_data.cpu_data = (float *)malloc(param.output.size() * sizeof(float));
  conv.output_data.host = (char *)malloc(conv.output_data.mlu_size);

  if (param.has_bias) {
    conv.bias_data.fp_data = mallocDataRandf(param.bias.size(), low, hight);
    conv.bias_data.cpu_data = (float *)malloc(param.bias.size() * sizeof(float));
    conv.bias_data.host = (char *)malloc(conv.bias_data.mlu_size);
  }

  
  int pos = 0, offset = 0;
  float scale = 1.0;
 


  return 0;


}






int destroydeviceconv(cnrtQueue_t &queue, cnnlHandle_t &handle,Convolution& conv)
{
    


      //2.destory op and tensor desc
  CNNL_CHECK(cnnlDestroyConvolutionDescriptor(conv.conv_desc));
  CNNL_CHECK(cnnlDestroyTensorDescriptor(conv.input_desc));
  CNNL_CHECK(cnnlDestroyTensorDescriptor(conv.weight_desc));
  CNNL_CHECK(cnnlDestroyTensorDescriptor(conv.output_desc));

  if (conv.bias_desc) {
    CNNL_CHECK(cnnlDestroyTensorDescriptor(conv.bias_desc));
  }

  //3.free device memory
  //CNRT_CHECK(cnrtFree(conv.input_data.device));  //zkg
  CNRT_CHECK(cnrtFree(conv.weight_data.device));
  CNRT_CHECK(cnrtFree(conv.output_data.device));
  if (conv.bias_data.device != nullptr) {
    CNRT_CHECK(cnrtFree(conv.bias_data.device));
  }
  if (conv.workspace != nullptr) {
    CNRT_CHECK(cnrtFree(conv.workspace));
  }
	


	return 0;
}


int destroyconv(cnrtQueue_t &queue, cnnlHandle_t &handle,Convolution conv)
{



   //1.free host space
  free(conv.input_data.host);
  free(conv.input_data.fp_data);
  free(conv.input_data.cpu_data);

  free(conv.weight_data.host);
  free(conv.weight_data.fp_data);
  free(conv.weight_data.cpu_data);

  free(conv.output_data.host);
  free(conv.output_data.fp_data);
  free(conv.output_data.cpu_data);

  if (conv.bias_data.host) {
    free(conv.bias_data.host);
    free(conv.bias_data.fp_data);
  }

 


   return 0;

}



CnnlConvLayer::CnnlConvLayer(cnnlHandle_t handle, cnrtQueue_t  queue,std::vector<int> input_shape,std::vector<int> output_shape,std::vector<int> kernel_shape,std::vector<int> stride,std::vector<int> dilation,std::vector<int> pad,int input_position,float input_scale,bool has_bias)
{


    //初始化
   //_queue = queue;
   _handle = handle;
   cnnlGetQueue(_handle, &_queue);


    cnnlDataType_t DataType;
    DataType = CNNL_DTYPE_FLOAT;
 
  

  //cnnlTensorLayout_t conv_input_layout = CNNL_LAYOUT_NHWC;


    //初始化参数
    //_conv;

    _conv.algo=CNNL_CONVOLUTION_FWD_ALGO_DIRECT;
    
    //_conv_param;  
    initparam(_conv_param,input_shape,output_shape,kernel_shape,stride,dilation,pad,input_position,input_scale,has_bias);
 
    

    initconv(_handle,_conv,_conv_param);


   
    _kernel_h=_conv_param.kernel.kh;
    _kernel_w=_conv_param.kernel.kw;
    _stride_h=_conv_param.kernel.sh;
    _stride_w=_conv_param.kernel.sw;
    _dilation_h=_conv_param.kernel.dh;
    _dilation_w=_conv_param.kernel.dw;
    _pad_htop=_conv_param.pad.pt;
    _pad_wleft=_conv_param.pad.pl;
    _pad_hbottom=_conv_param.pad.pb;
    _pad_wright=_conv_param.pad.pr;


    

}


//前向推理

void *CnnlConvLayer::forward(void *input_mlu_ptr)
{

   
   //std::cout <<"convforward:"<<"start!"<< std::endl;
   //std::cout <<" conv.algo:"<< _conv.algo<< std::endl;

   //CNRT_CHECK(cnrtMemcpy(_conv.input_data.fp_data, input_mlu_ptr,_conv.input_data.fp_size, CNRT_MEM_TRANS_DIR_DEV2HOST));
   

  
   CNNL_CHECK(cnnlConvolutionForward(_handle, _conv.conv_desc, _conv.algo, nullptr, _conv.input_desc, input_mlu_ptr,_conv.weight_desc, _conv.weight_data.device, _conv.bias_desc, _conv.bias_data.device,_conv.workspace, _conv.workspace_size, nullptr, _conv.output_desc, _conv.output_data.device));
   
   //CNRT_CHECK(cnrtMemcpy(_conv.output_data.fp_data, _conv.output_data.device,_conv.output_data.fp_size, CNRT_MEM_TRANS_DIR_DEV2HOST));
   //CNRT_CHECK(cnrtQueueSync(_queue));

	return _conv.output_data.device;
}



//加载参数
void CnnlConvLayer::loadParam(std::vector<float> filter_data,
                   std::vector<float> bias_data,
                   int filter_position,
                   float filter_scale)
{


 for(int idx=0; idx< filter_data.size();idx++)
  {

     _conv.weight_data.fp_data[idx]=filter_data[idx];


  }

CNRT_CHECK(cnrtMemcpy(_conv.weight_data.device,_conv.weight_data.fp_data, _conv.weight_data.mlu_size,CNRT_MEM_TRANS_DIR_HOST2DEV));
 if(_conv_param.has_bias)
 {
   
   for(int idx=0; idx< bias_data.size();idx++)
   {
     
      _conv.bias_data.fp_data[idx]=bias_data[idx];

   }
   //拷贝数据到卡20230602
   CNRT_CHECK(cnrtMemcpy(_conv.bias_data.device,_conv.bias_data.fp_data, _conv.bias_data.mlu_size,CNRT_MEM_TRANS_DIR_HOST2DEV));

 } 

}


float* CnnlConvLayer::getoutputCpuData()
{
        return _conv.output_data.fp_data;
}

int CnnlConvLayer::getoutputCpulenth()
{
	return _conv.output_data.fp_size/sizeof(float) ;
}


//释放内存
CnnlConvLayer::~CnnlConvLayer()
{
  destroyconv(_queue, _handle,_conv);
  destroydeviceconv(_queue, _handle, _conv);
   cnrtQueueDestroy(_queue);

}



//mlp实现  全连接层

CnnlMlpLayer::CnnlMlpLayer(cnnlHandle_t handle, cnrtQueue_t  queue,std::vector<int> input_shape,std::vector<int> weight_shape,std::vector<int> output_shape,
		int input_position,float input_scale) 
{
  
    cnnlDataType_t DataType;
    DataType = CNNL_DTYPE_FLOAT;
    _handle=handle;
    //_queue=queue;
    cnnlGetQueue(_handle, &_queue);

   

 
     size_t input_length = 1;
    size_t weight_length = 1;
    size_t output_length = 1;

     // count input, filter, bias, output nums

     _batchsize=input_shape[0];
    if(input_shape.size()==3)
    {
      int input_dim[] = {input_shape[0],input_shape[1],input_shape[2]};
      cnnlTensorDescriptor_t input_desc;
      CNNL_CHECK(cnnlCreateTensorDescriptor(&_input_desc));
     CNNL_CHECK(cnnlSetTensorDescriptor(_input_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(input_dim)/4, input_dim));
     
       for (int idx = 0; idx < sizeof(input_dim) / 4; idx++) {
        input_length *= input_dim[idx];
       }

    }
    else if(input_shape.size()==2)
    {
     int input_dim[] = {input_shape[0],input_shape[1]};
     cnnlTensorDescriptor_t input_desc;
     CNNL_CHECK(cnnlCreateTensorDescriptor(&_input_desc));
     CNNL_CHECK(cnnlSetTensorDescriptor(_input_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(input_dim)/4, input_dim));
     
      for (int idx = 0; idx < sizeof(input_dim) / 4; idx++) {
        input_length *= input_dim[idx];
      }

    } 
    else if(input_shape.size()==4)
    {
      int input_dim[] = {input_shape[0],input_shape[1],input_shape[2],input_shape[3]};
      cnnlTensorDescriptor_t input_desc;
      CNNL_CHECK(cnnlCreateTensorDescriptor(&_input_desc));
      CNNL_CHECK(cnnlSetTensorDescriptor(_input_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(input_dim)/4, input_dim));
      

      for (int idx = 0; idx < sizeof(input_dim) / 4; idx++) {
        input_length *= input_dim[idx];
      }


    }   


    if(weight_shape.size()==3)
    {
      int weight_dim[] = {weight_shape[0],weight_shape[1],weight_shape[2]};
      cnnlTensorDescriptor_t weight_desc;
      CNNL_CHECK(cnnlCreateTensorDescriptor(&_weight_desc));
      CNNL_CHECK(cnnlSetTensorDescriptor(_weight_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(weight_dim)/4, weight_dim));
     
        for (int idx = 0; idx < sizeof(weight_dim) / 4; idx++) {
        weight_length *= weight_dim[idx];
     }


    }
    else if(weight_shape.size()==2)
    {
       int weight_dim[] = {weight_shape[0],weight_shape[1]};
       cnnlTensorDescriptor_t weight_desc;
       CNNL_CHECK(cnnlCreateTensorDescriptor(&_weight_desc));
      CNNL_CHECK(cnnlSetTensorDescriptor(_weight_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(weight_dim)/4, weight_dim));
      
       for (int idx = 0; idx < sizeof(weight_dim) / 4; idx++) {
        weight_length *= weight_dim[idx];
       }

    }
    else if(weight_shape.size()==4)
    {
      int weight_dim[] = {weight_shape[0],weight_shape[1],weight_shape[2],weight_shape[3]};
      cnnlTensorDescriptor_t weight_desc;
      CNNL_CHECK(cnnlCreateTensorDescriptor(&_weight_desc));
      CNNL_CHECK(cnnlSetTensorDescriptor(_weight_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(weight_dim)/4, weight_dim));
      
       for (int idx = 0; idx < sizeof(weight_dim) / 4; idx++) {
        weight_length *= weight_dim[idx];
       }

    }


    if(output_shape.size()==3)
    {
      int output_dim[] = {output_shape[0],output_shape[1],output_shape[2]};
      CNNL_CHECK(cnnlCreateTensorDescriptor(&_output_desc));
      CNNL_CHECK(cnnlSetTensorDescriptor(_output_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(output_dim)/4, output_dim));
      for (int idx = 0; idx < sizeof(output_dim) / 4; idx++) {
          output_length *= output_dim[idx];
        }



    }
    else if(output_shape.size()==2)
    {
       int output_dim[] = {output_shape[0],output_shape[1]};
       CNNL_CHECK(cnnlCreateTensorDescriptor(&_output_desc));
       CNNL_CHECK(cnnlSetTensorDescriptor(_output_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(output_dim)/4, output_dim));
       for (int idx = 0; idx < sizeof(output_dim) / 4; idx++) {
         output_length *= output_dim[idx];
       }


    }
    else if(output_shape.size()==4)
    {
       int output_dim[] = {output_shape[0],output_shape[1],output_shape[2],output_shape[3]};
        CNNL_CHECK(cnnlCreateTensorDescriptor(&_output_desc));
       CNNL_CHECK(cnnlSetTensorDescriptor(_output_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(output_dim)/4, output_dim));

        for (int idx = 0; idx < sizeof(output_dim) / 4; idx++) 
	{
          output_length *= output_dim[idx];
        }


    }

   
    _input_length=input_length;
    _weight_length=weight_length;
    _output_length=output_length;

    //分配卡内存
    
    CNRT_CHECK(cnrtMalloc((void**)&_weight_mlu_ptr, weight_length * sizeof(float)));
    CNRT_CHECK(cnrtMalloc((void**)&_output_mlu_ptr, output_length * sizeof(float)));

    

    if(_is_havebias)
    {
      
       int bias_dim[] = {output_shape[3]};


       
       CNNL_CHECK(cnnlCreateTensorDescriptor(&_bias_desc));
       CNNL_CHECK(cnnlSetTensorDescriptor(_bias_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(bias_dim)/4, bias_dim));
       
       _bias_length=output_shape[3];
       CNRT_CHECK(cnrtMalloc((void**)&_bias_mlu_ptr, _bias_length * sizeof(float)));
       _bias_cpu_ptr= (float *)malloc(_bias_length * sizeof(float));

        

        _workspace_size = 0;
       
       CNNL_CHECK(cnnlGetBiasAddWorkspaceSize(_handle, _bias_desc, _output_desc, &_workspace_size));
    
        if (_workspace_size > 0) {
           CNRT_CHECK(cnrtMalloc((void **)&_workspace, _workspace_size));
          }
       _alpha_cpu_ptr = (float *)malloc(1 * sizeof(float));
       _beta_cpu_ptr = (float *)malloc(1 * sizeof(float));
       _alpha_cpu_ptr[0]=1;
       _beta_cpu_ptr[0]=1;


    }


     _input_cpu_ptr= (float *)malloc(input_length * sizeof(float));

  
     _weight_cpu_ptr = (float *)malloc(weight_length * sizeof(float));

    
      unsigned int seed = 2;
      for (size_t idx = 0; idx < weight_length; idx++) {
        _weight_cpu_ptr[idx] = rand_r(&seed) % 10;
    }

    CNRT_CHECK(cnrtMemcpy(_weight_mlu_ptr,  _weight_cpu_ptr, weight_length * sizeof(float), CNRT_MEM_TRANS_DIR_HOST2DEV));
   /**************************************************/

    
    _output_cpu_ptr=(float *)malloc(output_length * sizeof(float));


}

//加载权重

void CnnlMlpLayer::loadParam(std::vector<float> filter_data,
                             std::vector<float> bias_data,
                             int filter_position,
                             float filter_scale) {

  if(_batchsize==1)
  {

     for(int idx=0; idx< filter_data.size();idx++)
    {
      _weight_cpu_ptr[idx]=filter_data[idx];
    
    }


  }
  else if(_batchsize>1)
  {
      for(int i=0;i < _batchsize;i++)
      {
	  for(int idx=0; idx< filter_data.size();idx++)
        {
          _weight_cpu_ptr[i*filter_data.size()+idx]=filter_data[idx];

        }
     

      }	  

  }
  

  CNRT_CHECK(cnrtMemcpy(_weight_mlu_ptr, _weight_cpu_ptr, _weight_length * sizeof(float), CNRT_MEM_TRANS_DIR_HOST2DEV));

  if(_is_havebias)
  {
    

     for(int idx=0; idx< bias_data.size();idx++)
    {
     
	    _bias_cpu_ptr[idx]=bias_data[idx];
	   
     }
    CNRT_CHECK(cnrtMemcpy(_bias_mlu_ptr, _bias_cpu_ptr, _bias_length * sizeof(float), CNRT_MEM_TRANS_DIR_HOST2DEV));

   }


 
}



//前向推理

void *CnnlMlpLayer::forward(void *input_mlu_ptr) 
{

  
  cnnlBatchMatMul(_handle,_is_transa,_is_transb, _input_desc, input_mlu_ptr, _weight_desc,_weight_mlu_ptr,_output_desc, _output_mlu_ptr);
 
 
 if(_is_havebias)
 {
    
    cnnlBiasAdd(_handle, _alpha_cpu_ptr, _bias_desc, _bias_mlu_ptr, _workspace, _workspace_size, _beta_cpu_ptr, _output_desc, _output_mlu_ptr);
    
 }
 //
  //CNRT_CHECK(cnrtMemcpy(_output_cpu_ptr, _output_mlu_ptr, _output_length * sizeof(float), CNRT_MEM_TRANS_DIR_DEV2HOST));
 
  //CNRT_CHECK(cnrtQueueSync(_queue));
  

  return _output_mlu_ptr;

}

float* CnnlMlpLayer::getoutputCpuData()
{
        return _output_cpu_ptr;
}

int CnnlMlpLayer::getoutputCpulenth()
{
        return _output_length;
}



//释放内存

CnnlMlpLayer::~CnnlMlpLayer() 
{



    //释放设备内存
    CNNL_CHECK(cnnlDestroyTensorDescriptor( _input_desc));
    CNNL_CHECK(cnnlDestroyTensorDescriptor(_weight_desc));
    CNNL_CHECK(cnnlDestroyTensorDescriptor(_output_desc));

    
    CNRT_CHECK(cnrtFree(_weight_mlu_ptr));
    CNRT_CHECK(cnrtFree(_output_mlu_ptr));
    
     //cpu内存分配
    free(_input_cpu_ptr);
    free(_weight_cpu_ptr);
    free(_output_cpu_ptr);
    cnrtQueueDestroy(_queue);

   if(_is_havebias)
   {
	  
	  CNNL_CHECK(cnnlDestroyTensorDescriptor( _bias_desc));
	  CNRT_CHECK(cnrtFree(_bias_mlu_ptr));
	  free(_bias_cpu_ptr);
	  free(_alpha_cpu_ptr);
	  free(_beta_cpu_ptr);


     if (_workspace) {
        CNRT_CHECK(cnrtFree(_workspace));
      }

 
   }


}




//pool实现
//初始化
CnnlPoolingLayer::CnnlPoolingLayer(cnnlHandle_t handle, cnrtQueue_t  queue,std::vector<int> input_shape,std::vector<int> output_shape,std::vector<int> kernel_shape,std::vector<int> stride) 
{

    cnnlDataType_t DataType;
    DataType = CNNL_DTYPE_FLOAT;
    
    _pool_mode=CNNL_POOLING_MAX;
    
    ////创建描述符

    _handle=handle;
    //_queue=queue;
    cnnlGetQueue(_handle, &_queue);

     int input_dim[] = {input_shape[0], input_shape[2], input_shape[3],input_shape[1]};
    
    CNNL_CHECK(cnnlCreateTensorDescriptor(&_input_desc));
    CNNL_CHECK(cnnlSetTensorDescriptor(_input_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(input_dim)/4, input_dim));
    

    
    int output_dim[] = {output_shape[0],output_shape[2],output_shape[3], output_shape[1]};
    
    CNNL_CHECK(cnnlCreateTensorDescriptor(&_output_desc));
    CNNL_CHECK(cnnlSetTensorDescriptor(_output_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(output_dim)/4, output_dim));
    

    
   _maxpooling_nan_opt=CNNL_NOT_PROPAGATE_NAN;
   
   int window_height=kernel_shape[0];
   int window_width=kernel_shape[1];




   int top_padding=0;
   int bottom_padding=0;
   int left_padding=0;
   int right_padding=0;

   int vertical_stride=stride[0];
   int horizon_stride=stride[1];


   

   
   cnnlCreatePoolingDescriptor(&_pooling_desc);
   CNNL_CHECK(cnnlSetPooling2dDescriptor(_pooling_desc, _pool_mode, _maxpooling_nan_opt, window_height,window_width,top_padding,bottom_padding,left_padding,right_padding,vertical_stride,horizon_stride));
   
   _workspace_size=0;
   int out_w_size=1;
   int out_h_size=1;

   CNNL_CHECK(cnnlGetPoolingWorkspaceSize(_handle,  _pool_mode,out_w_size,out_h_size,&_workspace_size));
   if (_workspace_size > 0) {
        CNRT_CHECK(cnrtMalloc((void **)&_workspace, _workspace_size));
   }


    size_t input_length = 1;
    size_t output_length = 1;
     for (int idx = 0; idx < sizeof(input_dim) / 4; idx++) {
        input_length *= input_dim[idx];
    }
    for (int idx = 0; idx < sizeof(output_dim) / 4; idx++) {
        output_length *= output_dim[idx];
    }
    _input_length=input_length;
    _output_length=output_length;

    CNRT_CHECK(cnrtMalloc((void**)&_input_mlu_ptr, input_length * sizeof(float)));//zkg
    CNRT_CHECK(cnrtMalloc((void**)&_output_mlu_ptr, output_length * sizeof(float)));


   
    _input_cpu_ptr = (float *)malloc(input_length * sizeof(float));
    _output_cpu_ptr = (float *)malloc(output_length * sizeof(float));



    

}



//前向推理
void *CnnlPoolingLayer::forward(void *input_mlu_ptr)
{

        
        cnnlPoolingForward(_handle,_pooling_desc,NULL, _input_desc,input_mlu_ptr,NULL,_output_desc,_output_mlu_ptr,_workspace,_workspace_size);
	
	//计算结果拷贝到cpu
        //CNRT_CHECK(cnrtMemcpy(_output_cpu_ptr, _output_mlu_ptr, _output_length * sizeof(float), CNRT_MEM_TRANS_DIR_DEV2HOST));
        //CNRT_CHECK(cnrtQueueSync(_queue));

	return _output_mlu_ptr;
}


float* CnnlPoolingLayer::getoutputCpuData()
{
        return _output_cpu_ptr;
}

int CnnlPoolingLayer::getoutputCpulenth()
{
        return _output_length;
}


//释放内存

CnnlPoolingLayer::~CnnlPoolingLayer() 
{


   //释放内存
    CNNL_CHECK(cnnlDestroyPoolingDescriptor(_pooling_desc));
    CNNL_CHECK(cnnlDestroyTensorDescriptor(_input_desc));
    CNNL_CHECK(cnnlDestroyTensorDescriptor(_output_desc));


     if (_workspace) {
        CNRT_CHECK(cnrtFree(_workspace));
    }
    CNRT_CHECK(cnrtFree(_input_mlu_ptr)); //zkg
    CNRT_CHECK(cnrtFree(_output_mlu_ptr));
    free(_input_cpu_ptr);
    free(_output_cpu_ptr);
    cnrtQueueDestroy(_queue);

}





//softmax
//初始化

CnnlSoftmaxLayer::CnnlSoftmaxLayer(cnnlHandle_t handle,cnrtQueue_t queue,std::vector<int> input_shape, int axis) 
{

   cnnlDataType_t DataType;
   DataType = CNNL_DTYPE_FLOAT;

   _handle=handle;
   //_queue=queue;
   cnnlGetQueue(_handle, &_queue);
   
    _soft_mode = CNNL_SOFTMAX_MODE_LOW_DIMENSION;

    size_t output_length = 1;
    size_t input_length=output_length;

   if(input_shape.size()==2)
   {
     int inputs_dim[] = { input_shape[0],input_shape[1]};
  
   CNNL_CHECK(cnnlCreateTensorDescriptor(&_input_desc));
   CNNL_CHECK(cnnlSetTensorDescriptor(_input_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(inputs_dim)/4, inputs_dim));
  

    int output_dim[] = { input_shape[0],input_shape[1]};
     CNNL_CHECK(cnnlCreateTensorDescriptor(&_output_desc));
    CNNL_CHECK(cnnlSetTensorDescriptor(_output_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(output_dim)/4, output_dim));
    
    for (int idx = 0; idx < sizeof(output_dim) / 4; idx++) {
        output_length *= output_dim[idx];
    }
     input_length=output_length;

   }
   else if(input_shape.size()==3)
   {

     int inputs_dim[] = { input_shape[0],input_shape[1],input_shape[2]};
     
     CNNL_CHECK(cnnlCreateTensorDescriptor(&_input_desc));
     CNNL_CHECK(cnnlSetTensorDescriptor(_input_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(inputs_dim)/4, inputs_dim));
     

    int output_dim[] = { input_shape[0],input_shape[1],input_shape[2]};
     CNNL_CHECK(cnnlCreateTensorDescriptor(&_output_desc));
    CNNL_CHECK(cnnlSetTensorDescriptor(_output_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(output_dim)/4, output_dim));
    

     for (int idx = 0; idx < sizeof(output_dim) / 4; idx++) {
        output_length *= output_dim[idx];
     }
     input_length=output_length;


   }



   _algorithm=CNNL_SOFTMAX_ACCURATE;

    _input_length=output_length;
    _output_length=output_length;
 
    
     CNRT_CHECK(cnrtMalloc((void**)&_output_mlu_ptr, output_length * sizeof(float)));
     
    _output_cpu_ptr = (float *)malloc(output_length * sizeof(float));
    _input_cpu_ptr = (float *)malloc(input_length * sizeof(float));

    
      _prefer= CNNL_COMPUTATION_HIGH_PRECISION;


}



//前向推理

void *CnnlSoftmaxLayer::forward(void *input_mlu_ptr)	
{
    
	 cnnlSoftmaxForward_v2(_handle,cnnlSoftmaxAlgorithm_t::CNNL_SOFTMAX_ACCURATE, cnnlSoftmaxMode_t::CNNL_SOFTMAX_MODE_LOW_DIMENSION,  cnnlComputationPreference_t::CNNL_COMPUTATION_HIGH_PRECISION,NULL,_input_desc,input_mlu_ptr,NULL,_output_desc, _output_mlu_ptr);

	//CNRT_CHECK(cnrtMemcpy(_output_cpu_ptr, _output_mlu_ptr, _output_length * sizeof(float), CNRT_MEM_TRANS_DIR_DEV2HOST));
    	//CNRT_CHECK(cnrtQueueSync(_queue));
	
	//拷贝数据到CPU
	return _output_mlu_ptr;

}


//获取计算结果值

float* CnnlSoftmaxLayer::getoutputCpuData()
{
	return _output_cpu_ptr;
}

int CnnlSoftmaxLayer::getoutputCpulenth()
{
        return _output_length;
}


//反向推理



//释放内存

CnnlSoftmaxLayer::~CnnlSoftmaxLayer() 
{

     CNNL_CHECK(cnnlDestroyTensorDescriptor(_output_desc));
     CNNL_CHECK(cnnlDestroyTensorDescriptor(_input_desc));
    
     CNRT_CHECK(cnrtFree(_output_mlu_ptr));
     free(_input_cpu_ptr);
     free(_output_cpu_ptr);
     cnrtQueueDestroy(_queue);

}




//relu层


CnnlReLuLayer::CnnlReLuLayer(cnnlHandle_t handle,cnrtQueue_t queue,std::vector<int> input_shape)
{
	
    cnnlDataType_t DataType;
    DataType = CNNL_DTYPE_FLOAT;

    _handle=handle;
    //_queue=queue;
    cnnlGetQueue(_handle, &_queue);


    if(input_shape.size()==4)
    {
	      // cnnl: prepare desc of input_tesnor
       int input_dim[] = {input_shape[0], input_shape[1], input_shape[2], input_shape[3]};
       //cnnlTensorDescriptor_t input_desc;
       CNNL_CHECK(cnnlCreateTensorDescriptor(&_input_desc));
       CNNL_CHECK(cnnlSetTensorDescriptor(_input_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(input_dim)/4, input_dim));
       

       // cnnl: prepare desc of output_tensor
       int output_dim[] = {input_shape[0], input_shape[1], input_shape[2], input_shape[3]};
       //cnnlTensorDescriptor_t output_desc;
       CNNL_CHECK(cnnlCreateTensorDescriptor(&_output_desc));
       CNNL_CHECK(cnnlSetTensorDescriptor(_output_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(output_dim)/4, output_dim));
       

       cnnlCreateActivationDescriptor(&_active_desc);
       CNNL_CHECK(cnnlSetActivationDescriptor(_active_desc, _active_mode, CNNL_NOT_PROPAGATE_NAN, 0.0));

       size_t input_length = 1;
       size_t output_length = 1;
       for (int idx = 0; idx < sizeof(input_dim) / 4; idx++) {
           input_length *= input_dim[idx];
       }
       for (int idx = 0; idx < sizeof(output_dim) / 4; idx++) {
           output_length *= output_dim[idx];
       }


      CNRT_CHECK(cnrtMalloc((void**)&_output_mlu_ptr, output_length * sizeof(float)));


       _input_cpu_ptr = (float *)malloc(input_length * sizeof(float));
       _output_cpu_ptr= (float *)malloc(output_length * sizeof(float));

       _input_length = input_length;
       _output_length = output_length;


    }
    else if(input_shape.size()==3)
    {
	      // cnnl: prepare desc of input_tesnor
      int input_dim[] = {input_shape[0], input_shape[1], input_shape[2]};
      //cnnlTensorDescriptor_t input_desc;
      CNNL_CHECK(cnnlCreateTensorDescriptor(&_input_desc));
      CNNL_CHECK(cnnlSetTensorDescriptor(_input_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(input_dim)/4, input_dim));
      

      // cnnl: prepare desc of output_tensor
      int output_dim[] = {input_shape[0], input_shape[1], input_shape[2]};
      //cnnlTensorDescriptor_t output_desc;
      CNNL_CHECK(cnnlCreateTensorDescriptor(&_output_desc));
      CNNL_CHECK(cnnlSetTensorDescriptor(_output_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(output_dim)/4, output_dim));
      
      cnnlCreateActivationDescriptor(&_active_desc);
      CNNL_CHECK(cnnlSetActivationDescriptor(_active_desc, _active_mode, CNNL_NOT_PROPAGATE_NAN, 0.0));

      size_t input_length = 1;
      size_t output_length = 1;
      for (int idx = 0; idx < sizeof(input_dim) / 4; idx++) {
          input_length *= input_dim[idx];
      }
      for (int idx = 0; idx < sizeof(output_dim) / 4; idx++) {
          output_length *= output_dim[idx];
      }

      CNRT_CHECK(cnrtMalloc((void**)&_output_mlu_ptr, output_length * sizeof(float)));


      _input_cpu_ptr = (float *)malloc(input_length * sizeof(float));
      _output_cpu_ptr= (float *)malloc(output_length * sizeof(float));

      _input_length = input_length;
      _output_length = output_length;


    }
    else if(input_shape.size()==2)
    {
                // cnnl: prepare desc of input_tesnor
      int input_dim[] = {input_shape[0], input_shape[1]};
      //cnnlTensorDescriptor_t input_desc;
      CNNL_CHECK(cnnlCreateTensorDescriptor(&_input_desc));
      CNNL_CHECK(cnnlSetTensorDescriptor(_input_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(input_dim)/4, input_dim));
      

      // cnnl: prepare desc of output_tensor
      int output_dim[] = {input_shape[0], input_shape[1]};
      //cnnlTensorDescriptor_t output_desc;
      CNNL_CHECK(cnnlCreateTensorDescriptor(&_output_desc));
      CNNL_CHECK(cnnlSetTensorDescriptor(_output_desc, CNNL_LAYOUT_NHWC, CNNL_DTYPE_FLOAT, sizeof(output_dim)/4, output_dim));
      
      cnnlCreateActivationDescriptor(&_active_desc);
      CNNL_CHECK(cnnlSetActivationDescriptor(_active_desc, _active_mode, CNNL_NOT_PROPAGATE_NAN, 0.0));

      size_t input_length = 1;
      size_t output_length = 1;
      for (int idx = 0; idx < sizeof(input_dim) / 4; idx++) {
          input_length *= input_dim[idx];
      }
      for (int idx = 0; idx < sizeof(output_dim) / 4; idx++) {
          output_length *= output_dim[idx];
      }


      //CNRT_CHECK(cnrtMalloc((void**)&_input_mlu_ptr, input_length * sizeof(float)));
      CNRT_CHECK(cnrtMalloc((void**)&_output_mlu_ptr, output_length * sizeof(float)));


      _input_cpu_ptr = (float *)malloc(input_length * sizeof(float));
      _output_cpu_ptr= (float *)malloc(output_length * sizeof(float));

      _input_length = input_length;
      _output_length = output_length;




    }



}


void* CnnlReLuLayer::forward(void *input_mlu_ptr)
{
	
  //CNRT_CHECK(cnrtMemcpy(_input_cpu_ptr, input_mlu_ptr, _input_length * sizeof(float), CNRT_MEM_TRANS_DIR_DEV2HOST));

  cnnlActivationForward(_handle,_active_desc,NULL,_input_desc,input_mlu_ptr,NULL,_output_desc,_output_mlu_ptr);
  
  //CNRT_CHECK(cnrtMemcpy(_output_cpu_ptr, _output_mlu_ptr, _output_length * sizeof(float), CNRT_MEM_TRANS_DIR_DEV2HOST));
  //CNRT_CHECK(cnrtQueueSync(_queue));
  return _output_mlu_ptr;
}


float* CnnlReLuLayer::getoutputCpuData()
{
        return _output_cpu_ptr;
}

int CnnlReLuLayer::getoutputCpulenth()
{
        return _output_length;
}

CnnlReLuLayer::~CnnlReLuLayer()
{

   //释放内存
    CNNL_CHECK(cnnlDestroyActivationDescriptor(_active_desc));
    CNNL_CHECK(cnnlDestroyTensorDescriptor(_input_desc));
    CNNL_CHECK(cnnlDestroyTensorDescriptor(_output_desc));

    //CNRT_CHECK(cnrtFree(_input_mlu_ptr));
    CNRT_CHECK(cnrtFree(_output_mlu_ptr));
    //CNRT_CHECK(cnrtFree(p_dev_indices));
    free(_input_cpu_ptr);
    free(_output_cpu_ptr);
    cnrtQueueDestroy(_queue);



}


