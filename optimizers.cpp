#include "optimizers.h"


using namespace std;


Optimizer_SGD::Optimizer_SGD(double learning_rate, double decay){
	Optimizer_SGD::learning_rate = learning_rate;
	Optimizer_SGD::decay = decay;
}


Optimizer_SGD::~Optimizer_SGD(){}



Layer_dense Optimizer_SGD::update_params(Layer_dense layer){
	double neg_lr = Optimizer_SGD::current_learning_rate*-1;
	
	// we update the weights
	auto lrxdw = layer.dweights * neg_lr;
	layer.weights+= lrxdw;

	// we update the biases
	auto lrxdb = layer.dbiases * neg_lr;
	layer.biases = lrxdb;

	return layer;
}


void Optimizer_SGD::pre_update_params(){
	if(Optimizer_SGD::decay){
		Optimizer_SGD::current_learning_rate = Optimizer_SGD::learning_rate *(1.0/(1.0+Optimizer_SGD::decay * Optimizer_SGD::iterations));
	}

}

void Optimizer_SGD::post_update_params(){
	Optimizer_SGD::iterations++;
}