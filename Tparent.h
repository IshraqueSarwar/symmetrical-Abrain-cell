#ifndef TPARENT_H
#define TPARENT_H

#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;


class Tensor1D;
class Tensor2D;

class Tparent{

	public:
		Tparent();
		virtual ~Tparent();

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


		//dot product between Tensor2Ds are matrix mul.

		//dot netween Tensor2D and Tensor1D then matrix-vec mul
		Tensor1D dot(Tensor2D& t1, Tensor1D& t2);

		//when Tensor2D is mul by Tensor1D we use matric vec mul
		Tensor1D matvecmul(Tensor2D& t1, Tensor1D& t2);
		
};


#endif