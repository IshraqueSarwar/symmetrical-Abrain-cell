#include <iostream>
#include <vector>
#include "cls.h"

using namespace std;

// main constructor for 1-dimensional tensor
Tensor1D::Tensor1D():tensor(){}
Tensor1D::Tensor1D(const Tensor1D& other): tensor(other.tensor){}
		
		


Tensor1D::Tensor1D(vector<float> t1d){
	Tensor1D::tensor = t1d;
	Tensor1D::update_dim();

}


//main constructors for 2-dimensional tensor
Tensor2D::Tensor2D(): tensor() {}

Tensor2D::Tensor2D(vector<vector<float>> t2d, bool validify){
	if(Tensor2D::valid_tensor(t2d)){
		Tensor2D::tensor = t2d;
		Tensor2D::update_dim();
	}else{
		if(validify){
			Tensor2D::tensor = Tensor2D::fill_to_valid(t2d);
			return;
		}
		throw invalid_argument("error: Tensor shape is not right.");
	}
	
}


int main(int argc, char* argv[]){
	/* 1D testing */
	Tensor1D t({6.4,4.0, 3.0});
	Tensor1D f({2,2, 2});
	Tensor1D tr;

	tr +=2;
	tr.print();



	/* 2D testing */

	// Tensor2D t1({{1.5,1.5,2.5}, {2.5,4.6,3.4}});
	// Tensor2D t2({{2,1.7,2.4}, {2,4.9,4.4}});
	// (t1/t2).print();


	



}