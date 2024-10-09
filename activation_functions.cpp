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
	Activation_ReLU::dinputs = dvalues;
	Activation_ReLU::dinputs.remove_less_than(0);
}




/*SOFTMAX ACTIVATION FUNCTION*/
Activation_Softmax::Activation_Softmax(){

}

Activation_Softmax::~Activation_Softmax(){

}


Tensor2D Activation_Softmax::forward(Tensor2D& inputs_given){

	Activation_Softmax::inputs = inputs_given;

	auto temp = nl.n_max(inputs, 1, true);
	auto res = inputs-get<Tensor2D>(temp);
	auto exp_values = nl.n_exp(res);
	auto sum = get<Tensor2D>(nl.n_sum(exp_values, 1, true));
	auto probabilities = exp_values/sum;
	// probabilities.print();

	Activation_Softmax::output = probabilities;
	return Activation_Softmax::output;
}

void Activation_Softmax::backward(Tensor2D dvalues){
	Activation_Softmax::dinputs = nl.empty_like(dvalues);

	vector<vector<double>> output_v = Activation_Softmax::output.get();
	vector<vector<double>> dvalues_v = dvalues.get();

	int len = dvalues.shape()[0];
	for(int index = 0;index<len;index++){
		Tensor1D single_dvalues(dvalues_v[index]);

		vector<double>single_output_v = output_v[index];
		// we reshape this 1D vector to a single column 2D Tensor. we'd naturally reshape(-1,1)
		// but I'm too lazy to write the reshape function... ONEDAY I'LL if I find enough 
		// reasons or motivations.
		// HERE WE GO--->>.reshape(-1,1)
		Tensor2D single_output;
		// Tensor1D single_dvalues()
		for(auto x:single_output_v){
			vector<double>v = {x};
			single_output.push(v);
		}
		// HERE WE END--->>


		Tensor2D temp = nl.diagflat(single_output);

		Tensor2D single_output_t = single_output.t();
		Tensor2D temp2 = nl.dot(single_output, single_output_t);


		auto jacobian_matrix = temp-temp2;

		auto dot_jacob_single_dvals = nl.dot(jacobian_matrix, single_dvalues);

		Activation_Softmax::dinputs.push(dot_jacob_single_dvals);
	}

}