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
	/* demo of single layer neuron rundown*/
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



	/* passing data to the first layer*/
	Layer_dense dense1(2,3);
	// Tensor2D output = dense1.forward(X);
	// output.print();

	

	// /* Rectified linear activation function*/
	Activation_ReLU activation1;
	// output = activation1.forward(output);
	// output.print();




	/*passing it through sencond layer of neurons*/
	Layer_dense dense2(3,3);
	// output = dense2.forward(output);
	// output.print()


	// /* Softmax activation function*/
	Activation_Softmax activation2;
	// output = activation2.forward(output);
	// output.print();



	/* calculating Loss of the network */
	Loss loss_function;
	// double loss = loss_func.calculate(output, y);
	// cout<<loss<<endl;


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
	// Tensor2D softmax_outputs({{0.7, 0.2, 0.1},
	// 						{0.5, 0.1, 0.4},
	// 						{0.02, 0.9, 0.08}});

	// // Tensor2D class_targets({{1,0,0},
	// // 						{0,1,0},
	// // 						{0,1,0}});

	// Tensor1D class_targets({0,1,1});
	
	// Tensor1D predictions = nl.n_argmax(softmax_outputs, 1);
	// double correct_pred = 0;
	

	// Tensor1D class_target_1D = nl.n_argmax(class_targets,1);

	// for(int i=0;i<predictions.shape()[0];i++){
	// 	if(predictions[i]==class_target_1D[i]){
	// 		correct_pred++;
	// 	}
	// }

	// double accuracy = correct_pred/predictions.shape()[0];
	// cout<<accuracy<<endl;

	
	
}
