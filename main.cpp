#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <variant>
#include <typeinfo>

#include "NNL.h"
#include "t1d.h"
#include "t2d.h"
#include "layer.h"
#include "activation_functions.h"
#include "loss_functions.h"
#include "optimizers.h"
#include "dataloader.h"


using namespace std;





void testTensor2D(){
	Tensor2D t1({{1.5,1.5,2.5}, {2.5,4.6,3.4}});
	Tensor2D t2({{2,1.7,2.4}, {2,4.9,4.4}});
	
	t2*=2;
	t2.print();
}


void testTensor1D(){
	Tensor1D t({6.4,4.0, 3.0});
	Tensor1D f({2,2, 2});
	

	
	Tensor1D tr(f);

	tr.print();

	(t/=f).print();

}



//TODO: make a dataset creator using the existing python library


int main(int argc, char* argv[]){
	/* demo of first run throught two layers of neurons and 
	two different activation functions and one loss function and calculating the loss*/


	// TODO: THERE IS NO CHANGE IN ACC THE NETWORK ISNT OPTIMIZING!!!
	
	NNL nl;
	// system("gnome-terminal -x sh -c 'python3 support/datagenerator.py'");
	/* reading in data generated from python file in support directory*/
	BasicDataLoaderFromTxt dataLoader;
	Tensor2D X = dataLoader.loadT2("support/xData.txt");
	Tensor1D y = dataLoader.loadT1("support/yData.txt");

	// Tensor2D X({{ 0.        ,  0.        },
	// 	       { 0.1068272 , -0.22602643},
	// 	       {-0.3565171 ,  0.35056463},
	// 	       { 0.54027534, -0.52019477},
	// 	       {-0.9980913 , -0.06175594},
	// 	       {-0.        , -0.        },
	// 	       { 0.09934813,  0.22941218},
	// 	       { 0.35293192, -0.35417378},
	// 	       {-0.73923534,  0.12661397},
	// 	       { 0.97696507,  0.2133992 }});
	// Tensor1D y({0, 0, 0, 0, 0, 1, 1, 1, 1, 1});


	// to pass inputs through layers we use the forward method.
	/* passing data to the first layer*/
	Layer_dense dense1(2,64);
	/* Rectified linear activation function*/
	Activation_ReLU activation1;
	/*passing it through sencond layer of neurons*/
	Layer_dense dense2(64,3);
	Activation_Softmax_Loss_CategoricalCrossentropy loss_activation;

	Optimizer_SGD optimizer(1,1e-2);
	for(int epoch = 0;epoch<10001;epoch++){
		auto output = dense1.forward(X);
		output = activation1.forward(output);
		output = dense2.forward(output);

		long double loss = loss_activation.forward(output, y);

		

		// loss_activation.output.print();
		auto predictions = nl.n_argmax(loss_activation.output, 1);
		auto y_1d = nl.n_argmax(y, 1);



		long double corr_pred = 0;
		for(int i= 0;i<predictions.shape()[0];i++){
			if(predictions[i]==y_1d[i]){
				corr_pred++;
			}
		}

		long double acc = corr_pred/(predictions.shape()[0]);

		if(!(epoch%100)){
			cout<<"epoch: "<<epoch<<"\nacc: "<<acc<<"\nloss: "<<loss<<"\nlr: "<<optimizer.current_learning_rate<<"\n\n";
			// loss_activation.output.print();
		}


		loss_activation.backward(loss_activation.output, y);
		dense2.backward(loss_activation.dinputs);
		activation1.backward(dense2.dinputs);
		dense1.backward(activation1.dinputs);

		optimizer.pre_update_params();
		dense1 = optimizer.update_params(dense1);
		dense2 = optimizer.update_params(dense2);
		optimizer.post_update_params();
	}
	


	/* <-------TESTING-----> */
	// Tensor2D softmax_outputs({{0.7,0.1,0.2},
	// 							{0.1,0.5,0.4},
	// 							{0.02, 0.9,0.08}});

	// Tensor1D class_target({0,1,1});

	// Tensor2D testTensor({{0.1,0.2,0.2},
	// 					{0.3,0.2,0.2},
	// 					{0.2,0.2,0.2}});

	// Tensor2D testTensor2({{1,1,1}});

	// Tensor2D testTensor3({{2},
	// 						{2},
	// 						{2}});


	// (softmax_outputs+2).print();
	// Activation_Softmax_Loss_CategoricalCrossentropy softmax_loss;
	// softmax_loss.backward(softmax_outputs, class_target);

	// auto dvalues1 = softmax_loss.dinputs;

	// Activation_Softmax activation;
	// activation.output = softmax_outputs;

	// Loss_CategoricalCrossentropy loss;
	// loss.backward(softmax_outputs, class_target);
	

	// activation.backward(loss.dinputs);
	// auto dvalues2 = activation.dinputs;

	// dvalues1.print();
	// dvalues2.print();

}	
