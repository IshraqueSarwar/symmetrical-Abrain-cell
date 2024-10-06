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

	Tensor1D y()



	/* passing data to the first layer*/
	Layer_dense dense1(2,4);
	Tensor2D output = dense1.forward(X);
	// output.print();

	

	// /* Rectified linear activation function*/
	Activation_ReLU activation1;
	output = activation1.forward(output);
	// output.print();



	/*passing it through sencond layer of neurons*/
	Layer_dense dense2(4,2);
	output = dense1.forward(output);
	// output.print()


	// /* Softmax activation function*/
	Activation_Softmax activation2;
	output = activation2.forward(output);
	output.print();



	/* calculating Loss of the network */
	Loss_CategoricalCrossentropy loss_func;
	double loss = loss_func(output, )
	


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
