#ifndef TPARENT_H
#define TPARENT_H

#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;


class Tensor1D;

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


		
};


#endif