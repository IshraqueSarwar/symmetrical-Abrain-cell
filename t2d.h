#ifndef T2D_H
#define T2D_H

//include whatever you want in NNL class
#include "NNL.h"
#include "t1d.h"

using namespace std;
	
	
// 2d tensor class
class Tensor2D: public NNL{
	private:
		vector<vector<float>> tensor;
		vector<int>dimensions;


	public:
		Tensor2D();
		Tensor2D(const Tensor2D& other);
		Tensor2D(vector<vector<float>>t2d, bool validify = false);

		virtual ~Tensor2D();
		


		vector<vector<float>> fill_to_valid(vector<vector<float>> t){
			int mx = 0;
			for(int i=0;i<t.size();i++){
				int sz = t[i].size();
				mx = max(mx, sz);
			}

			for(int i=0;i<t.size();i++){
				if(t[i].size()<mx){
					int dif = mx-t[i].size();
					while(dif){
						t[i].push_back(0.0);
						dif--;
					}
				}
			}

			return t;
		}

		bool valid_tensor(vector<vector<float>> t){
			if(!t.empty()){
				int col = t[0].size();

				for(int i=0;i<t.size();i++){
					if(t[i].size()!=col){
						return false;
					}
				}
				return true;
			}

			return false;
		}

		void push(vector<float> v){
			tensor.push_back(v);
		}

		

		//setter func
		void set(vector<vector<float>> t2d){
			tensor = t2d;
		}

		//getter func
		vector<vector<float>> get()const{
			return tensor;
		}


		// Transposing the tensor
		void transpose(){
			if(tensor.size()){
				vector<vector<float>> tensor_trans(tensor[0].size(), vector<float>(tensor.size()));

				for(int i = 0;i<tensor.size();i++){
					for(int j=0;j<tensor[i].size();j++){
						tensor_trans[j][i]= tensor[i][j];
					}
				}

				tensor = tensor_trans;
				tensor_trans.clear();
			}

		}

		// for displaying the tensor in human readable format.
		void print(){
			if(tensor.empty()){
				cout<<"Tensor<float, 2D>([[]])";
			}else{
				cout<<"Tensor<float, 2D>(\n[";
				for(int i = 0;i<tensor.size();i++){
					cout<<'[';
					for(int j = 0;j<tensor[i].size()-1;j++){
						cout<<tensor[i][j]<<", ";
					}
					cout<<tensor[i][tensor[i].size()-1];
					if(i!=tensor.size()-1){
						cout<<"],\n";
					}else{
						cout<<"]])\n";
					}
				
				}

			}
			
		}

		void update_dim(){
			dimensions.clear();
			dimensions.push_back(tensor.size());
			dimensions.push_back(tensor[0].size());
		}

		// returning dimesion vector;
		// shape function takes in arg:print that shows the dim if true
		vector<int> shape(bool print=false){
			update_dim();
			if(print)
				NNL::printTensorDim(dimensions);
			return dimensions;
		}



		//OVERLOADING
		
		/* EQUAL overload to assign new tensor*/
		Tensor2D operator=(const Tensor2D& other){
			tensor = other.tensor;
			// we need to update the dimension when we assign a new tensor, as the shape of the new
			// 		tensor can be different.
			update_dim();
			return tensor;
		}



		// TODO: make shorthands for tensor to tensor operations
		/* SHORTHAND OPERATORS*/
			// +=
		Tensor2D& operator+=(double n){
			for(int i=0;i<dimensions[0];i++){
				for(int j=0;j<dimensions[1];j++){
					this->tensor[i][j]+=n;
				}
			}
			return *this;
		}

		Tensor2D& operator+=(Tensor2D& other){
			if(dimensions==other.shape()){
				for(int i=0;i<dimensions[0];i++){
					for(int j = 0;j<dimensions[1];j++){
						this->tensor[i][j]+=other.tensor[i][j];
					}
				}
				return *this;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
			
		}

			// -=
		Tensor2D& operator-=(double n){
			for(int i=0;i<dimensions[0];i++){
				for(int j=0;j<dimensions[1];j++){
					this->tensor[i][j]-=n;
				}
			}
			return *this;
		}
		Tensor2D& operator-=(Tensor2D& other){
			if(dimensions==other.shape()){
				for(int i=0;i<dimensions[0];i++){
					for(int j = 0;j<dimensions[1];j++){
						this->tensor[i][j]-=other.tensor[i][j];
					}
				}
				return *this;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
			
		}

			// *=
		Tensor2D& operator*=(double n){
			for(int i=0;i<dimensions[0];i++){
				for(int j=0;j<dimensions[1];j++){
					this->tensor[i][j]*=n;
				}
			}
			return *this;
		}
		Tensor2D& operator*=(Tensor2D& other){
			if(dimensions==other.shape()){
				for(int i=0;i<dimensions[0];i++){
					for(int j = 0;j<dimensions[1];j++){
						this->tensor[i][j]*=other.tensor[i][j];
					}
				}
				return *this;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
			
		}

			// /=
		Tensor2D& operator/=(double n){
			double x = 1/n;
			for(int i=0;i<dimensions[0];i++){
				for(int j=0;j<dimensions[1];j++){
					this->tensor[i][j]*=x;
				}
			}
			return *this;
		}
		Tensor2D& operator/=(Tensor2D& other){
			if(dimensions==other.shape()){
				for(int i=0;i<dimensions[0];i++){
					for(int j = 0;j<dimensions[1];j++){
						double x = (1/other.tensor[i][j]);
						this->tensor[i][j]*=x;
					}
				}
				return *this;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
			
		}



		/* ADDITION OVERLOADING */
			// Tensor + (double)n
		Tensor2D operator+(double n)const{
			Tensor2D res;
			for(int i = 0;i<dimensions[0];i++){
				vector<float>row;
				for(int j=0;j<dimensions[1];j++){
					row.push_back(tensor[i][j]+n);
				}
				res.tensor.push_back(row);
			}
			return res;
		}


			// (double)n + Tensor
		friend Tensor2D operator+(double n, Tensor2D& t){
			return t+n;
		}



			//Tensor2D+Tensor1D
		friend Tensor2D operator+(Tensor2D& t2d, Tensor1D& t1d){
			vector<int> t1d_shape = t1d.shape();
			vector<int> t2d_shape = t2d.shape();
		
			
			if(t1d_shape[0]==t2d_shape[1]){
				vector<float> t1d_v = t1d.get();
				vector<vector<float>> t2d_v = t2d.get();
			
				Tensor2D c;
				for(int i = 0;i<t2d_shape[0];i++){
					vector<float>r;
					for(int j = 0;j<t2d_shape[1];j++){
						float x = t1d_v[j]+t2d_v[i][j];
						r.push_back(x);
					}
					c.push(r);
				}

				return c;
			}

			throw invalid_argument("The inner shape of Tensor2D doesn't match that of Tensor1D");
		}
		
		friend Tensor2D operator+(Tensor1D& t1d, Tensor2D& t2d){
			return t2d+t1d;
		}


		




		/* SUBTRACTION OVERLOADING */
			// Tensor - (double) n
		Tensor2D operator-(double n)const{
			Tensor2D res;
			for(int i = 0;i<dimensions[0];i++){
				vector<float>row;
				for(int j=0;j<dimensions[1];j++){
					row.push_back(tensor[i][j]-n);
				}
				res.tensor.push_back(row);
			}
			return res;
		}

			// Tensor - Tensor
		Tensor2D operator-(Tensor2D& t){
			if(dimensions==t.shape()){
				Tensor2D res;
				for(int i = 0;i<dimensions[0];i++){
					vector<float> row;
					for(int j =0;j<dimensions[1];j++){
						row.push_back(tensor[i][j]-t.tensor[i][j]);
					}
					res.tensor.push_back(row);
				}
				return res;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");

		}


			//Tensor2D-Tensor1D
		friend Tensor2D operator-(Tensor2D& t2d, Tensor1D& t1d){
			Tensor1D r(t1d* -1);
			return t2d+r;
		}
		
		friend Tensor2D operator-(Tensor1D& t1d, Tensor2D& t2d){
			Tensor2D r(t2d* -1);
			return t1d+r;
		}




		/* MULTIPLICATION OVERLOADING */
			// Tensor x (double) n
		Tensor2D operator*(double n) const{
			Tensor2D res;
			for(int i = 0;i<dimensions[0];i++){
				vector<float>row;
				for(int j=0;j<dimensions[1];j++){
					row.push_back(tensor[i][j]*n);
				}
				res.tensor.push_back(row);
			}
			return res;
		}


			// Tensor x Tensor
		Tensor2D operator*(Tensor2D& t){
			if(dimensions==t.shape()){
				Tensor2D res;
				for(int i = 0;i<dimensions[0];i++){
					vector<float> row;
					for(int j =0;j<dimensions[1];j++){
						row.push_back(tensor[i][j]*t.tensor[i][j]);
					}
					res.tensor.push_back(row);
				}
				return res;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
		}


		/* DIVISION OVERLOADING */
			//Tensor / (double) n
		Tensor2D operator/(double n)const{
			double x = 1/n;
			return *(this) * x;
		}

			//Tensor / Tensor
		Tensor2D operator/(Tensor2D& t){
			if(dimensions == t.shape()){
				Tensor2D res;
				for(int i = 0;i<dimensions[0]; i++){
					vector<float> row;
					for(int j = 0;j<dimensions[1];j++){
						row.push_back(tensor[i][j]/t.tensor[i][j]);
					}
					res.tensor.push_back(row);
				}
				return res;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
		}

};





#endif