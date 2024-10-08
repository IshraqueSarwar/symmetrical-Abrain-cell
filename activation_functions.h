#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H

#include "t2d.h"
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <vector>


class Activation_ReLU{
	public:
		Tensor2D output;
		Tensor2D inputs;
		Tensor2D dinputs;


		Activation_ReLU();
		virtual ~Activation_ReLU();



		Tensor2D forward(Tensor2D& inputs);
		void backward(Tensor2D& dvalues);

};


class Activation_Softmax{
	public:
		Tensor2D output;

		Activation_Softmax();
		virtual ~Activation_Softmax();


		Tensor2D forward(Tensor2D& inputs);
};


#endif