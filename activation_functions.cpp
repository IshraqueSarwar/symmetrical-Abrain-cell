#include "activation_functions.h"
#include "NNL.h"
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

NNL nl;

Activation_ReLU::Activation_ReLU(){

}

Activation_ReLU::~Activation_ReLU(){
	
}

Tensor2D Activation_ReLU::forward(Tensor2D& inputs){
	Activation_ReLU::output = nl.maximum(0, inputs);
	return Activation_ReLU::output;
}