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

		Activation_ReLU();
		virtual ~Activation_ReLU();



		Tensor2D forward(Tensor2D& inputs);

};


#endif