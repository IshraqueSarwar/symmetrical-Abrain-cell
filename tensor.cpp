#include <iostream>
#include <vector>
#include "t1d.h"
#include "t2d.h"

using namespace std;

// main constructor for 1-dimensional tensor



Tensor1D::Tensor1D():tensor(){}
Tensor1D::Tensor1D(const Tensor1D& other){
	// Tensor1D::tensor = other.tensor;
	Tensor1D::set(other.get());
	Tensor1D::update_dim();
}
Tensor1D::Tensor1D(vector<double> t1d){
	Tensor1D::tensor = t1d;
	Tensor1D::update_dim();

}

Tensor1D::~Tensor1D(){}



//main constructors for 2-dimensional tensor
Tensor2D::Tensor2D(): tensor() {}
Tensor2D::Tensor2D(const Tensor2D& other){
	Tensor2D::set(other.get());
	Tensor2D::update_dim();
}
Tensor2D::Tensor2D(vector<vector<double>> t2d, bool validify){
	if(Tensor2D::valid_tensor(t2d)){
		Tensor2D::tensor = t2d;
		// Tensor2D::set(t2d);
		Tensor2D::update_dim();
	}else{
		if(validify){
			Tensor2D::tensor = Tensor2D::fill_to_valid(t2d);
			return;
		}
		throw invalid_argument("error: Tensor shape is not right.");
	}
	
}
Tensor2D::~Tensor2D(){}


