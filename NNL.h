#ifndef NNL_H
#define NNL_H

#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <vector>
#include <random>

using namespace std;


class Tensor1D;
class Tensor2D;

class NNL{

	public:
		NNL();
		virtual ~NNL();

		virtual void print(){
		}


		void printTensorDim(vector<int>d){

			cout<<"Tensor.shape(";
			for(auto i: d){
				cout<<std::setprecision(2);
				cout<<i<<", ";
			}
			cout<<")\n";
		}

		Tensor1D dot(Tensor1D& t1, Tensor1D& t2);
		double dot(double t1, double t2);
		//dot netween Tensor2D and Tensor1D then matrix-vec mul
		Tensor1D dot(Tensor2D& t1, Tensor1D& t2);
		Tensor2D dot(Tensor2D& t1, Tensor2D& t2);


		//when Tensor2D is mul by Tensor1D we use matric vec mul
		Tensor1D matvecmul(Tensor2D& a, Tensor1D& b);

		// Matrix multiplication function for Tensor2D and Tensor2D operation
		Tensor2D matmul(Tensor2D& a, Tensor2D& b);


		
		// randomized Tensor2D
		Tensor2D random_randn(int n_inputs, int n_neurons);

		// tensor full of zeros
		Tensor2D zeros(int n_inputs, int n_neurons);

		
};


#endif