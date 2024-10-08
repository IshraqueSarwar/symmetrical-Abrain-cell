#include "activation_functions.h"
#include "NNL.h"
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

NNL nl;


/* ReLU ACTIVATION FUNCTION*/
Activation_ReLU::Activation_ReLU(){

}

Activation_ReLU::~Activation_ReLU(){
	
}

Tensor2D Activation_ReLU::forward(Tensor2D& inputs_given){
	Activation_ReLU::inputs = inputs_given;
	Activation_ReLU::output = nl.maximum(0, Activation_ReLU::inputs);
	return Activation_ReLU::output;
}

void Activation_ReLU::backward(Tensor2D& dvalues){
	// Activation_ReLU::dinputs = dvalues;
	// Activation_ReLU::dinputs.remove_less_than(0);
}




/*SOFTMAX ACTIVATION FUNCTION*/
Activation_Softmax::Activation_Softmax(){

}

Activation_Softmax::~Activation_Softmax(){

}


Tensor2D Activation_Softmax::forward(Tensor2D& inputs){
	auto temp = nl.n_max(inputs, 1, true);
	auto res = inputs-get<Tensor2D>(temp);
	auto exp_values = nl.n_exp(res);
	auto sum = get<Tensor2D>(nl.n_sum(exp_values, 1, true));
	auto probabilities = exp_values/sum;
	// probabilities.print();

	Activation_Softmax::output = probabilities;
	return Activation_Softmax::output;
}