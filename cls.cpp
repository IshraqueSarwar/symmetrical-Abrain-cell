#include <iostream>
#include <vector>
#include "cls.h"

using namespace std;

// main constructor for 1-dimensional tensor
Tensor1D::Tensor1D():tensor(){}
Tensor1D::Tensor1D(const Tensor1D& other): tensor(other.tensor){}
		
		


Tensor1D::Tensor1D(vector<float> t1d){
	Tensor1D::tensor = t1d;
	Tensor1D::dimensions.push_back(t1d.size());

}


//main constructors for 2-dimensional tensor
Tensor2D::Tensor2D(): tensor() {}

Tensor2D::Tensor2D(vector<vector<float>> t2d, bool validify){
	if(Tensor2D::valid_tensor(t2d)){
		Tensor2D::tensor = t2d;
	}else{
		if(validify){
			Tensor2D::tensor = Tensor2D::fill_to_valid(t2d);
			return;
		}
		throw invalid_argument("error: Tensor shape is not right.");
	}
}


int main(int argc, char* argv[]){
	Tensor1D t({1.5,4.6, 5.6});
	Tensor1D tr;
	tr =t+1.5;
	tr.print();



	Tensor2D t2({{1.3,1.3,2.5}, {2.3,4.3,3.4}});
	t2.get();
	// t2.transpose();
	// t2.dim();



	



}