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
		Tensor2D weights;
		Tensor2D biases;
	public:
		Layer_dense(int n_inputs, int n_neurons);
		Tensor2D forward(Tensor2D inputs);

		void print_weights_biases();
};


#endif