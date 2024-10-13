#ifndef OPTIMIZERS_H
#define OPTIMIZERS_H


#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <vector>
#include <random>
#include "t2d.h"
#include "layer.h"


class Optimizer_SGD{
	public:
		Optimizer_SGD(double learning_rate=1.0);
		~Optimizer_SGD();


		Layer_dense update_params(Layer_dense layer);


	private:
		double learning_rate = 1.0;
};


#endif