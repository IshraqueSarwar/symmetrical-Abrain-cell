#ifndef TPARENT_H
#define TPARENT_H

#include <stdexcept>
#include <iomanip>

using namespace std;


class NNL{

	public:
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


		
};


#endif