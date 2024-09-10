#ifndef T1D_H
#define T1D_H

// include whatever you want in NNL class
#include "NNL.h"
// #include "t2d.h"

using namespace std;








// 1d tensor class

class Tensor1D: public NNL{
	private:
		vector<float> tensor;
		vector<int>dimensions;


	public:
		// main constructor
		Tensor1D();
		Tensor1D(const Tensor1D& other);
		Tensor1D(vector<float> t1d);

		virtual ~Tensor1D();
		
		

		//setter
		void set(const Tensor1D& other){
			tensor = other.tensor;
		}

		//getter
		vector<float> get()const{
			return tensor;
		}


		//push function for 1D tensor to add element in the end
		void push(double d){
			tensor.push_back(d);
		}


		void transpose(){
			// transposing a 1D tensor gives us the same tensor
			
		}



		void print(){
			if(tensor.size()){
				cout<<"Tensor<float, 1D>([";
				for(int i=0;i< dimensions[0]-1; i++){
					cout<<tensor[i]<<", ";
				}
				cout<<tensor[dimensions[0]-1]<<"])\n";
			}else{
				cout<<"Tensor<float, 1D>([])";
			}
			
		}


		void update_dim(){
			dimensions.clear();
			dimensions.push_back(tensor.size());
		}


		// get dimensions of the tensor
		// shape function takes in arg:print that shows the dim if true
		vector<int> shape(bool print=false){
			update_dim();
			if(print)
				NNL::printTensorDim(dimensions);
			return dimensions;
		}

		//overloading
		



		/* EQUAL to assign */
		Tensor1D operator=(const Tensor1D& other){
			tensor = other.tensor;
			// we need to update the dimension when we assign a new tensor, as the shape of the new
			// 		tensor can be different.
			update_dim();
			return tensor;
		}

		/* SHORTHAND OPERATORS*/
			// +=
		Tensor1D& operator+=(double n){
			for(int i=0;i<dimensions[0];i++){
				this->tensor[i]+=n;
			}
			return *this;
		}

		Tensor1D& operator+=(Tensor1D& other){
			if(dimensions==other.shape()){
				for(int i = 0;i<dimensions[0];i++){
					this->tensor[i]+=other.tensor[i];
				}
				return *this;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
		
		}


			//-=
		Tensor1D& operator-=(double n){
			for(int i=0;i<dimensions[0];i++){
				this->tensor[i]-=n;
			}
			return *this;
		}
		Tensor1D& operator-=(Tensor1D& other){
			if(dimensions==other.shape()){
				for(int i = 0;i<dimensions[0];i++){
					this->tensor[i]-=other.tensor[i];
				}
				return *this;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
		
		}


			//*=
		Tensor1D& operator*=(double n){
			for(int i=0;i<dimensions[0];i++){
				this->tensor[i]*=n;
			}
			return *this;
		}
		Tensor1D& operator*=(Tensor1D& other){
			if(dimensions==other.shape()){
				for(int i = 0;i<dimensions[0];i++){
					this->tensor[i]*=other.tensor[i];
				}
				return *this;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
		
		}

			// /=
		Tensor1D& operator/=(double n){
			double x = 1/n;
			for(int i=0;i<dimensions[0];i++){
				this->tensor[i]*=x;
			}
			return *this;
		}
		Tensor1D& operator/=(Tensor1D& other){
			if(dimensions==other.shape()){
				for(int i = 0;i<dimensions[0];i++){
					double x = (1/other.tensor[i]);
					this->tensor[i]*=x;
				}
				return *this;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
		
		}



		/* ADDITION overload*/
			//Tensor1D + (double)n
		Tensor1D operator+(double n)const{
			Tensor1D res;

			for(int i = 0;i<dimensions[0];i++){
				res.tensor.push_back(tensor[i]+n);
			}
			
			return res;
		}

			// (double)n + Tensor1D
		friend Tensor1D operator+(double n, Tensor1D& t){
			return t+n;
		}

			// Tensor1D + Tensor1D
		Tensor1D operator+(Tensor1D& t){
			if(dimensions==t.shape()){
				Tensor1D res;
				for(int i=0;i<dimensions[0];i++){
					res.tensor.push_back(t.tensor[i]+tensor[i]);
				}
				return res;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
			
		}

		
	
		

		
		

		

		/* SUBTRACTION overlaod */
			// Tensor1D - n
		Tensor1D operator-(double n)const{
			Tensor1D res;
			for(int i=0;i<dimensions[0];i++){
				res.tensor.push_back(tensor[i]-n);
			}
			return res;
		}

		//TODO:	//(double)n -tensor 
		// Tensor1D operator-(double n, Tensor1D& t){
		// 	Tensor1D res;
		// 	for(int i=0;i<dimensions[0];i++){
		// 		res.tensor.push_back(n-tensor[i]);
		// 	}

		// 	return res;
		// }

			// Tensor1D - Tensor1D
		Tensor1D operator-(Tensor1D& t){
			if(dimensions==t.shape()){
				Tensor1D res;
				for(int i=0;i<dimensions[0];i++){
					res.tensor.push_back(t.tensor[i]-tensor[i]);
				}
				return res;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");

		}


		/* MULTIPLICATION overlaod */
		
			// Tensor1D x (double)n
		Tensor1D operator*(double n)const{
			Tensor1D res;

			for(int i = 0;i<dimensions[0];i++){
				res.tensor.push_back(tensor[i]*n);
			}
			
			return res;
		}


			// Tensor x Tensor
		Tensor1D operator*(Tensor1D& t){
			if(dimensions==t.shape()){
				Tensor1D res;
				for(int i=0;i<dimensions[0];i++){
					res.tensor.push_back(t.tensor[i]*tensor[i]);
				}
				return res;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
		}


			// (double)n x Tensor1D
		friend Tensor1D operator*(double n, Tensor1D& t){
			return t*n;
		}


		/* DIVISION overload */
			// Tensor / n
		Tensor1D operator/(double n)const{
			double x = 1/n;
			return (*this) *x;
		}

		//TODO:	// n / tensor
		// Tensor1D operator/(double n, Tensor1D& t){
		// 	Tensor1D res;
		// 	for(int i=0;i<dimensions[0];i++){
		// 		res.tensor.push_back(n/tensor[i]);
		// 	}

		// 	return res;
		// }

			// Tensor / Tensor
		Tensor1D operator/(Tensor1D& t){
			if(dimensions==t.shape()){
				Tensor1D res;
				for(int i=0;i<dimensions[0];i++){
					res.tensor.push_back(tensor[i]/t.tensor[i]);
				}
				return res;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
		}





};



#endif