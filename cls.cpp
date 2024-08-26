#include <iostream>
#include <vector>
#include "cls.h"

using namespace std;

// main constructor for 1-dimensional tensor
Tensor1D::Tensor1D():tensor(){}

Tensor1D::Tensor1D(vector<float> t1d){
	Tensor1D::tensor = t1d;
	Tensor1D::dimensions.push_back(t1d.size());

}


//main constructors for 2-dimensional tensor
Tensor2D::Tensor2D(): tensor() {}

Tensor2D::Tensor2D(vector<vector<float>> t2d){
	Tensor2D::tensor = t2d;
}


int main(int argc, char* argv[]){
	Tensor1D tensor({1.5,4.6, 5.6});
	// tensor.print();


	Tensor2D tensor2({{1.3,1.3,2.5}, {6.3,4.3,3.4}});
	// tensor2.dim();
	// tensor2.transpose();
	// tensor2.dim();



	



}