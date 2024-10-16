#include "layer.h"

#include <iostream>

using namespace std;

// initializing the Parent lib
NNL nmain;


Layer_dense::Layer_dense(int n_inputs, int n_neurons){
	
	// we initialize random weights using gaussian distrib
	// multiply by 0.01 to generate numbers a couple of mag smaller.
	Layer_dense::weights = nmain.random_randn(n_inputs, n_neurons);
	weights*=0.01;

	// initialize biases to zeros.
	Layer_dense::biases = nmain.zeros(1, n_neurons);


	// initialize momentum tensors 
	Layer_dense::weight_momentums = nmain.zeros_like(Layer_dense::weights);
	Layer_dense::bias_momentums = nmain.zeros_like(Layer_dense::biases);
}

void Layer_dense::print_weights_biases(){
	Layer_dense::weights.print();
	Layer_dense::biases.print();
}


Tensor2D Layer_dense::forward(Tensor2D inputs_given){
	Layer_dense::inputs = inputs_given;
	Layer_dense::output = nmain.dot(Layer_dense::inputs, Layer_dense::weights);
	// += wont work until we fix cross class operators completely.
	Layer_dense::output+=Layer_dense::biases;
	return Layer_dense::output;
}


void Layer_dense::backward(Tensor2D dvalues){
	auto inputs_t = Layer_dense::inputs.t();
	Layer_dense::dweights = nmain.dot(inputs_t, dvalues);

	auto d_val_sum = nmain.n_sum(dvalues, 0, true);

	Layer_dense::dbiases = get<Tensor2D>(d_val_sum);

	auto weights_t = weights.t();
	dinputs = nmain.dot(dvalues, weights_t);
}