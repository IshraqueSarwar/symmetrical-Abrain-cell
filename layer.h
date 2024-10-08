#ifndef LAYER_H
#define LAYER_H

#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <vector>
#include <random>
#include "t2d.h"

using namespace std;

class Layer_dense{
	private:
		int n_inputs, n_neurons;
		
		
	public:
		
		Tensor2D weights;
		Tensor2D biases;
		Tensor2D inputs;
		Tensor2D output;

		// for backpropagation
		//gradiant on parameters
		Tensor2D dweights;
		Tensor2D dbiases;

		//gradiant on values
		Tensor2D dinputs;




		Layer_dense(int n_inputs, int n_neurons);
		Tensor2D forward(Tensor2D inputs);

		void backward(Tensor2D dvalues);

		void print_weights_biases();
};


#endif