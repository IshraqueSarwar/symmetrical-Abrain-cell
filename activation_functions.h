#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H

#include "t2d.h"
#include "loss_functions.h"
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
		Tensor2D inputs;

		Tensor2D dinputs;

		Activation_Softmax();
		virtual ~Activation_Softmax();


		Tensor2D forward(Tensor2D& inputs);
		void backward(Tensor2D dvalues);
};



class Activation_Softmax_Loss_CategoricalCrossentropy{
	public:
		// we need the activation softmax class and
		Activation_Softmax activation;
		// Categorical cross entropy loss class
		Loss loss;

		Tensor2D output;
		Tensor2D dinputs;


		Activation_Softmax_Loss_CategoricalCrossentropy();
		~Activation_Softmax_Loss_CategoricalCrossentropy();

		double forward(Tensor2D inputs, Tensor1D y_true);
		double forward(Tensor2D inputs, Tensor2D y_true);


		void backward(Tensor2D dvalues, Tensor1D y_true);
		void backward(Tensor2D dvalues, Tensor2D y_true);


	private:

};



#endif