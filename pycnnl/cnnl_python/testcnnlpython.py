import pycnnl

testnet=pycnnl.CnnlNet()
testnet.setInputShape(1, 1, 1, 1)

input_shapem1=pycnnl.IntVector(4)  #np.array([batch_size,1,1,input_size],dtype=np.intc)
input_shapem1[0]=1
input_shapem1[1]=1
input_shapem1[2]=1
input_shapem1[3]=784
weight_shapem1=pycnnl.IntVector(4)  #np.array([batch_size,1,input_size,hidden1],dtype=np.intc)
weight_shapem1[0]=1
weight_shapem1[1]=1
weight_shapem1[2]=784
weight_shapem1[3]=32

output_shapem1=pycnnl.IntVector(4)  #np.array([batch_size,1,1,hidden1],dtype=np.intc)
output_shapem1[0]=1
output_shapem1[1]=1
output_shapem1[2]=1
output_shapem1[3]=32
testnet.createMlpLayer('fc1', input_shapem1, weight_shapem1, output_shapem1)

