#ifndef LOSS_FUNCTIONS_H
#define LOSS_FUNCTIONS_H


#include "t2d.h"
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <vector>

class Loss{

	public:
		Loss();
		virtual ~Loss();

		double calculate(Tensor2D output, Tensor1D y);
		double calculate(Tensor2D output, Tensor2D y);

		

	private:

};


class Loss_CategoricalCrossentropy: public Loss{
	public:
		Tensor2D dinputs;

		Loss_CategoricalCrossentropy();
		virtual ~Loss_CategoricalCrossentropy();


		Tensor1D forward(Tensor2D y_pred, Tensor1D y_true);
		Tensor1D forward(Tensor2D y_pred, Tensor2D y_true);


		void backward(Tensor2D dvalues, Tensor1D y_true);
		void backward(Tensor2D dvalues, Tensor2D y_true);

	private:


};


#endif