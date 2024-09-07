#include "Tparent.h"
#include "t1d.h"
#include "t2d.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>


using namespace std;


// main constructor for 1-dimensional tensor
Tparent::Tparent(){

}

Tparent::~Tparent(){

}



Tensor1D Tparent::dot(Tensor1D& t1, Tensor1D& t2){
	return t1*t2;
}

double Tparent::dot(double t1, double t2){
	return t1*t2;
}

Tensor1D Tparent::dot(Tensor2D& t1, Tensor1D& t2){
	return Tparent::matvecmul(t1,t2);
}


Tensor2D Tparent::dot(Tensor2D& t1, Tensor2D& t2){
	return Tparent::matmul(t1, t2);
}


Tensor1D Tparent::matvecmul(Tensor2D& a, Tensor1D& b){
	
	vector<int> t1_shape = a.shape();
	vector<int> t2_shape = b.shape();

	if(t1_shape[1]==t2_shape[0]){
		vector<vector<float>> t1 = a.get();
		vector<float> t2 = b.get();
		Tensor1D res;
		for(int i = 0;i<t1_shape[0];i++){
			double prodsum = 0;
			for(int j = 0;j<t1_shape[1];j++){
				prodsum+= t1[i][j]*t2[j];
			}
			res.push(prodsum);
		}

		return res;

	}
	throw invalid_argument("Error: Shapes ("+to_string(t1_shape[0]) + ", "+ to_string(t1_shape[1])+") and ("+ to_string(t2_shape[0])+") not aligned" );
}


Tensor2D Tparent::matmul(Tensor2D& a, Tensor2D& b){
	vector<int> t1_shape = a.shape();
	vector<int> t2_shape = b.shape();

	if(t1_shape[1]==t2_shape[0]){
		vector<vector<float>> t1 = a.get();
		vector<vector<float>> t2 = b.get();

		Tensor2D res;
		for(int i = 0;i<t1_shape[0];i++){
			vector<float> x;
			for(int j = 0;j<t2_shape[1];j++){
				double z = 0;
				for(int k = 0;k<t1_shape[1];k++){
					z+=t1[i][k]*t2[k][j];
				}
				x.push_back(z);
			}
			res.push(x);
		}

		return res;
	
	}

	throw invalid_argument("Error: Shapes ("+to_string(t1_shape[0]) + ", "+ to_string(t1_shape[1])+") and ("+ to_string(t2_shape[0])+") not aligned" );

}