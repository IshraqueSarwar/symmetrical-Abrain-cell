#include "optimizers.h"


using namespace std;


Optimizer_SGD::Optimizer_SGD(double learning_rate, double decay, double momentum){
	Optimizer_SGD::learning_rate = learning_rate;
	Optimizer_SGD::current_learning_rate = learning_rate;
	Optimizer_SGD::decay = decay;
	Optimizer_SGD::momentum = momentum;
}


Optimizer_SGD::~Optimizer_SGD(){}




void Optimizer_SGD::pre_update_params(){
	if(Optimizer_SGD::decay){
		Optimizer_SGD::current_learning_rate = Optimizer_SGD::learning_rate *(1.0/(1.0+Optimizer_SGD::decay * Optimizer_SGD::iterations));
	}

}



Layer_dense Optimizer_SGD::update_params(Layer_dense layer){
	
	if (Optimizer_SGD::momentum){
		/* we do momentum calculation the weight momentums and bias momentums*/

		Tensor2D wmXm = layer.weight_momentums *  Optimizer_SGD::momentum;
		Tensor2D clrXdw = layer.dweights * Optimizer_SGD::current_learning_rate;

		// THIS SECTION --- WHY DO WE NEED TO DO THE OPERATIONS SEPARATELY
		clrXdw*=-1;
		Tensor2D weight_updates = wmXm+clrXdw;
		//THIS SECTION --- something wrong w the (-) operator.

		/*Udating the momentums inside the layer*/
		layer.weight_momentums = weight_updates;


		Tensor2D bmXm = layer.bias_momentums * Optimizer_SGD::momentum;
		Tensor2D clrXdb = layer.dbiases * Optimizer_SGD::current_learning_rate;
		
		// THIS SECTION --- WHY DO WE NEED TO DO THE OPERATIONS SEPARATELY
		clrXdb*=-1;
		Tensor2D bias_updates = bmXm + clrXdb;
		//THIS SECTION --- something wrong w the (-) operator.

		/*Udating the momentums inside the layer*/
		layer.bias_momentums = bias_updates;


		layer.weights+= weight_updates;
		layer.biases += bias_updates;


	}else{

		// TODO: optimizer w out momentum not workign as was

		double neg_lr = Optimizer_SGD::current_learning_rate*-1;
		// we calculate the weight updates
		Tensor2D weight_updates = layer.dweights * neg_lr;
		// we calculate the bias_updates
		Tensor2D bias_updates = layer.dbiases * neg_lr;

		layer.weights+= weight_updates;
		layer.biases += bias_updates;
	}

	// layer.weights+= weight_updates;
	// layer.biases += bias_updates;

	

	return layer;
}




void Optimizer_SGD::post_update_params(){
	Optimizer_SGD::iterations++;
}