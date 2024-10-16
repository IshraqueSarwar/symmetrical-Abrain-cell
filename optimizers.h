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
		// TODO: LOOK AT THE variable assignment
		double current_learning_rate;// = learning_rate;
		double momentum;// = 0;
		Optimizer_SGD(double learning_rate=1.0, double decay = 0.0, double momentum = 0.0);
		~Optimizer_SGD();


		void pre_update_params();
		Layer_dense update_params(Layer_dense layer);
		void post_update_params();


	private:
		double learning_rate = 1.0;
		double decay = decay;
		int iterations = 0;


};


#endif