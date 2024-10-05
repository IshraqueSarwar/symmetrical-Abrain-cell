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

		// int calculate(Tensor2D output, Tensor1D y);
		// int calculate(Tens)

	private:

};


class Loss_CategoricalCrossentropy: Loss{
	public:
		Loss_CategoricalCrossentropy();
		virtual ~Loss_CategoricalCrossentropy();


		Tensor1D forward(Tensor2D y_pred, Tensor1D y_true);
		Tensor1D forward(Tensor2D y_pred, Tensor2D y_true);

	private:


};


#endif