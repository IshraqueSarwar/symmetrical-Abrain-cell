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
}

void Layer_dense::print_weights_biases(){
	Layer_dense::weights.print();
	Layer_dense::biases.print();
}


Tensor2D Layer_dense::forward(Tensor2D inputs){
	Tensor2D output;
	output = nmain.dot(inputs, Layer_dense::weights);
	// += wont work until we fix cross class operators completely.
	output+=Layer_dense::biases;
	return output;
}