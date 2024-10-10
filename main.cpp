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

	
	NNL nl;
	Tensor2D X({{ 0.        ,  0.        },
		       { 0.1068272 , -0.22602643},
		       {-0.3565171 ,  0.35056463},
		       { 0.54027534, -0.52019477},
		       {-0.9980913 , -0.06175594},
		       {-0.        , -0.        },
		       { 0.09934813,  0.22941218},
		       { 0.35293192, -0.35417378},
		       {-0.73923534,  0.12661397},
		       { 0.97696507,  0.2133992 }});

	Tensor1D y({0, 0, 0, 0, 0, 1, 1, 1, 1, 1});



	// to pass inputs through layers we use the forward method.

	/* passing data to the first layer*/
	Layer_dense dense1(2,3);
	// Tensor2D output = dense1.forward(X);

	/* Rectified linear activation function*/
	Activation_ReLU activation1;
	/*passing it through sencond layer of neurons*/
	Layer_dense dense2(3,3);
	


	// /* Softmax activation function*/
	Activation_Softmax activation2;

	/* calculating Loss of the network */
	Loss loss_function;


	double lowest_loss = 999999;
	Tensor2D best_dense1_weights = dense1.weights;
	Tensor2D best_dense1_biases = dense1.biases;
	Tensor2D best_dense2_weights = dense2.weights;
	Tensor2D best_dense2_biases = dense2.biases;


	Tensor2D output;

	for(int iteration = 0;iteration<10000000;iteration++){
		Tensor2D rand;
		rand = nl.random_randn(2,3);
		rand*=0.05;
		dense1.weights = rand;

		rand = nl.random_randn(1,3);
		rand*=0.05;
		dense1.biases =  rand;

		rand = nl.random_randn(3, 3);
		rand*=0.05;
		dense2.weights = rand;

		rand = nl.random_randn(1,3);
		rand*=0.05;
		dense2.biases = rand;


		// cout<<"tes\n";
		output = dense1.forward(X);
		output = activation1.forward(output);
		output = dense2.forward(output);
		output = activation2.forward(output);

		// output.print();

		double loss = loss_function.calculate(output, y);

		double correct_pred = 0;
		Tensor1D predictions = nl.n_argmax(output, 1);
		Tensor1D y_1d = nl.n_argmax(y,1);

		for(int i=0;i<predictions.shape()[0];i++){
			if(predictions[i]==y_1d[i]){
				correct_pred++;
			}
		}

		double accuracy = correct_pred/predictions.shape()[0];

		if(loss<lowest_loss){
			cout<<"New set of weights found, iteration: "<<iteration<<" loss: "<<loss<<" acc: "<<accuracy<<endl;

			best_dense1_weights= dense1.weights;
			best_dense1_biases = dense1.biases;
			best_dense2_weights = dense2.weights;
			best_dense2_biases = dense2.biases;

			lowest_loss = loss;
		}
	}
	


	/* <-------TESTING-----> */
	// Tensor2D dvalues({{1,1,1},
	// 			{2,2,2},
	// 			{3,3,3}});

	// Tensor2D inputs({{1, 2, 3, 2.5},
	// 				{2., 5., -1., 2},
	// 				{-1.5, 2.7, 3.3, -0.8}});


	// Tensor2D weights({{0.2, 0.8, -0.5, 1},
	// 					{0.5, -0.91, 0.26, -0.5},
	// 					{-0.26, -0.27, 0.17, 0.87}});



	// weights.transpose(); // transpose the weights tensor


	// Tensor2D biases({{2,3,0.5},
	// 				{2,3,4},
	// 				{2,4,2}});

	// Tensor1D c({2,3.4,3});

	



	// auto layer_outputs = nl.dot(inputs, weights)+biases;
	// auto relu_output = nl.maximum(0, layer_outputs);

	// auto drelu = relu_output;
	// drelu.remove_less_than(0);
	
	// auto weights_t = weights.t();
	// auto dinputs = nl.dot(drelu, weights_t);

	// auto inputs_t = inputs.t();
	// auto dweights = nl.dot(inputs_t, drelu);


	// auto dbiases_variant = nl.n_sum(drelu, 0, true);
	// Tensor2D dbiases = get<Tensor2D>(dbiases_variant);

	

	// auto temp = dweights*-0.001;
	// cout<<temp.shape()[0]<<' '<<temp.shape()[1]<<endl;
	// cout<<weights.shape()[0]<<' '<<weights.shape()[1]<<endl;
	// weights+=temp;


	// auto temp2 = dbiases*-0.001;
	// biases+=temp2;
	// cout<<dbiases.shape()[0]<<' '<<dbiases.shape()[1]<<endl;
	// cout<<biases.shape()[0]<<' '<<biases.shape()[1]<<endl;

	// weights.print();
	// biases.print();

	// Tensor1D t({1,2,5,3});
	// Tensor2D res = nl.convert_to_onehot(5, t);
	// res.print();



	// Tensor2D out();
	
}	
