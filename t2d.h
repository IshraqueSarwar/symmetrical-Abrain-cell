#ifndef T2D_H
#define T2D_H

/* include whatever you want in NNL class*/
#include "NNL.h"
#include "t1d.h"

using namespace std;
	
	
/* 2d tensor class */
class Tensor2D: public NNL{
	private:
		vector<vector<double>> tensor;
		vector<int>dimensions;


	public:
		Tensor2D();
		Tensor2D(const Tensor2D& other);
		Tensor2D(vector<vector<double>>t2d, bool validify = false);

		virtual ~Tensor2D();
		


		vector<vector<double>> fill_to_valid(vector<vector<double>> t){
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

		bool valid_tensor(vector<vector<double>> t){
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

		void push(vector<double> v){
			tensor.push_back(v);
		}

		

		/* setter func*/
		void set(vector<vector<double>> t2d){
			tensor = t2d;
		}

		/*getter func*/
		vector<vector<double>> get()const{
			return tensor;
		}

		Tensor1D get(vector<int> rows, vector<int> class_target)const{
			vector<double> ret;
			
			for(auto index: rows){
				double x = this->tensor[index][class_target[index]];
				ret.push_back(x);
			}
			
			return Tensor1D(ret);
		}

		Tensor1D get(Tensor1D rows, Tensor1D class_target)const{
			vector<double>rows_v = rows.get();
			vector<double>class_target_v = class_target.get();

			vector<double>ret;

			for(auto index: rows_v){
				double x = this->tensor[index][class_target_v[index]];
				ret.push_back(x);
			}

			return Tensor1D(ret);
		}


		/* Transposing the tensor*/
		void transpose(){
			if(tensor.size()){
				vector<vector<double>> tensor_trans(tensor[0].size(), vector<double>(tensor.size()));

				for(int i = 0;i<tensor.size();i++){
					for(int j=0;j<tensor[i].size();j++){
						tensor_trans[j][i]= tensor[i][j];
					}
				}

				tensor = tensor_trans;
				tensor_trans.clear();
			}

		}

		/* for displaying the tensor in human readable format.*/
		void print(){
			if(tensor.empty()){
				cout<<"Tensor<double, 2D>([[]])";
			}else{
				cout<<"Tensor<double, 2D>(\n[";
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

		/* returning dimesion vector;
		 shape function takes in arg:print that shows the dim if true*/
		vector<int> shape(bool print=false){
			update_dim();
			if(print)
				NNL::printTensorDim(dimensions);
			return dimensions;
		}



		//OVERLOADING
		
		// double& operator[][](int i, int j){
		// 	if(i>=dimensions[0] || j>=dimensions[1]){
		// 		throw invalid_argument("ERROR: The indicies are out of bound!");
		// 	}

		// 	return this->tensor[i][j];
		// }


		/* EQUAL overload to assign new tensor*/
		Tensor2D operator=(const Tensor2D& other){
			tensor = other.tensor;
			/* we need to update the dimension when we assign a new tensor, as the shape of the new
			 		tensor can be different.*/
			update_dim();
			return tensor;
		}



		
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

		/*We are checking if one of the Tensor is 2D and matches the inner
				dimension but has a single row that it still works.
				mainly integrating it in the *= and += operators and using it
				in -= and /= */
		/* NxN adds with Nx1
			NxN adds with 1xN*/
		Tensor2D& operator+=(Tensor2D& other){
			if(dimensions==other.shape()){
				for(int i=0;i<dimensions[0];i++){
					for(int j = 0;j<dimensions[1];j++){
						this->tensor[i][j]+=other.tensor[i][j];
					}
				}
				return *this;
			}else if( (dimensions[0] == other.shape()[0]) && (other.shape()[1]==1) ){
				
				//NxN + Nx1
				for(int i = 0;i<dimensions[0];i++){
					for(int j=0;j<dimensions[1];j++){
						this->tensor[i][j]+=other.tensor[i][0];
					}
				}
			
				return *this;

			}else if((dimensions[1] == other.shape()[1]) && (other.shape()[0]==1)){

				//NxN + 1xN
				for(int i=0;i<dimensions[0];i++){
					for(int j = 0;j<dimensions[1];j++){
						this->tensor[i][j]+=other.tensor[0][j];
					}
				}

				return *this;

			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
			
		}


		Tensor2D& operator+=(Tensor1D& other){
			Tensor2D temp(this->tensor);
			Tensor2D res = temp+other;
			this->set(res.get());
			return *this;

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
			Tensor2D r = other*-1;
			(*this)+=(r);
			return *this;
			
		}

		Tensor2D& operator-=(Tensor1D& other){
			Tensor2D temp(this->tensor);
			Tensor2D res = temp-other;
			this->set(res.get());
			return *this;

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
			}else if( (dimensions[0] == other.shape()[0]) && (other.shape()[1]==1) ){
				
				//NxN * Nx1
				for(int i = 0;i<dimensions[0];i++){
					for(int j=0;j<dimensions[1];j++){
						this->tensor[i][j]*=other.tensor[i][0];
					}
				}
			
				return *this;

			}else if((dimensions[1] == other.shape()[1]) && (other.shape()[0]==1)){

				//NxN * 1xN
				for(int i=0;i<dimensions[0];i++){
					for(int j = 0;j<dimensions[1];j++){
						this->tensor[i][j]*=other.tensor[0][j];
					}
				}

				return *this;

			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
			
		}

		Tensor2D& operator*=(Tensor1D& other){
			Tensor2D temp(this->tensor);
			Tensor2D res = temp*other;
			this->set(res.get());
			return *this;
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
			Tensor2D r = 1/other;
			(*this)*=r;
			return *this;
		}


		Tensor2D& operator/=(Tensor1D& other){
			Tensor2D temp(this->tensor);
			Tensor2D res = temp/other;
			this->set(res.get());
			return *this;
		}


		/* ADDITION OVERLOADING */
			// Tensor + (double)n
		Tensor2D operator+(double n)const{
			Tensor2D res;
			for(int i = 0;i<dimensions[0];i++){
				vector<double>row;
				for(int j=0;j<dimensions[1];j++){
					row.push_back(tensor[i][j]+n);
				}
				res.push(row);
			}
			return res;
		}

		Tensor2D operator+(Tensor2D& t){
			if(dimensions==t.shape()){
				Tensor2D res;
				for(int i = 0;i<dimensions[0];i++){
					vector<double> row;
					for(int j =0;j<dimensions[1];j++){
						row.push_back(tensor[i][j]+t.tensor[i][j]);
					}
					res.push(row);
				}
				return res;
			}else if(dimensions[0]==t.shape()[0]){
				// if the parent of the operator is single element 2D tensor
				if( dimensions[1]==1){
					Tensor2D res;
					for(int i = 0;i<dimensions[0];i++){
						vector<double> row;
						for(int j = 0;j<t.shape()[1];j++){
							row.push_back(tensor[i][0]+t.tensor[i][j]);
						}
						res.push(row);
					}
					return res;

				}
				// if the operated Tensor is single element 2D tensor
				else if(t.shape()[1]==1){
					Tensor2D res;
					for(int i = 0;i<dimensions[0];i++){
						vector<double> row;
						for(int j = 0;j<dimensions[1];j++){
							row.push_back(tensor[i][j]+t.tensor[i][0]);
						}
						res.push(row);
					}
					return res;
				}

				
			}else if(dimensions[1]==t.shape()[1]){
				if(dimensions[0]==1){
					Tensor2D res;
					for(int i = 0;i<t.shape()[0];i++){
						vector<double> row;
						for(int j = 0;j<t.shape()[1];j++){
							row.push_back(tensor[0][j]+t.tensor[i][j]);
						}
						res.push(row);
					}
					return res;
				}
				else if(t.shape()[0]==1){
					Tensor2D res;
					for(int i = 0;i<dimensions[0];i++){
						vector<double> row;
						for(int j = 0;j<dimensions[1];j++){
							row.push_back(tensor[i][j]+t.tensor[0][j]);
						}
						res.push(row);
					}
					return res;
				}
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");

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
				vector<double> t1d_v = t1d.get();
				vector<vector<double>> t2d_v = t2d.get();
			
				Tensor2D c;
				for(int i = 0;i<t2d_shape[0];i++){
					vector<double>r;
					for(int j = 0;j<t2d_shape[1];j++){
						double x = t1d_v[j]+t2d_v[i][j];
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
				vector<double>row;
				for(int j=0;j<dimensions[1];j++){
					row.push_back(tensor[i][j]-n);
				}
				res.push(row);
			}
			return res;
		}

			// Tensor - Tensor
		// TODO: Add (n,1)operator(n,m) or viceversa, - and / dome

		Tensor2D operator-(Tensor2D& t){
			Tensor2D r = t*-1;
			Tensor2D res = (*this)+r;
			return res;
			// if(dimensions==t.shape()){
			// 	Tensor2D res;
			// 	for(int i = 0;i<dimensions[0];i++){
			// 		vector<double> row;
			// 		for(int j =0;j<dimensions[1];j++){
			// 			row.push_back(tensor[i][j]-t.tensor[i][j]);
			// 		}
			// 		res.push(row);
			// 	}
			// 	return res;
			// }else if(dimensions[0]==t.shape()[0]){
			// 	// if the parent of the operator is single element 2D tensor
			// 	if( dimensions[1]==1){
			// 		Tensor2D res;
			// 		for(int i = 0;i<dimensions[0];i++){
			// 			vector<double> row;
			// 			for(int j = 0;j<t.shape()[1];j++){
			// 				row.push_back(tensor[i][0]-t.tensor[i][j]);
			// 			}
			// 			res.push(row);
			// 		}
			// 		return res;

			// 	}
			// 	// if the operated Tensor is single element 2D tensor
			// 	else if(t.shape()[1]==1){
			// 		Tensor2D res;
			// 		for(int i = 0;i<dimensions[0];i++){
			// 			vector<double> row;
			// 			for(int j = 0;j<dimensions[1];j++){
			// 				row.push_back(tensor[i][j]-t.tensor[i][0]);
			// 			}
			// 			res.push(row);
			// 		}
			// 		return res;
			// 	}

				
			// }
			// throw invalid_argument("Error: The shape of the Tensors don't match");

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
				vector<double>row;
				for(int j=0;j<dimensions[1];j++){
					row.push_back(tensor[i][j]*n);
				}
				res.push(row);
			}
			return res;
		}


			// Tensor x Tensor
		Tensor2D operator*(Tensor2D& t){
			if(dimensions==t.shape()){
				Tensor2D res;
				for(int i = 0;i<dimensions[0];i++){
					vector<double> row;
					for(int j =0;j<dimensions[1];j++){
						row.push_back(tensor[i][j]*t.tensor[i][j]);
					}
					res.push(row);
				}
				return res;
			}else if(dimensions[0]==t.shape()[0]){
				// if the parent of the operator is single element 2D tensor
				if( dimensions[1]==1){
					Tensor2D res;
					for(int i = 0;i<dimensions[0];i++){
						vector<double> row;
						for(int j = 0;j<t.shape()[1];j++){
							row.push_back(tensor[i][0]*t.tensor[i][j]);
						}
						res.push(row);
					}
					return res;

				}
				// if the operated Tensor is single element 2D tensor
				else if(t.shape()[1]==1){
					Tensor2D res;
					for(int i = 0;i<dimensions[0];i++){
						vector<double> row;
						for(int j = 0;j<dimensions[1];j++){
							row.push_back(tensor[i][j]*t.tensor[i][0]);
						}
						res.push(row);
					}
					return res;
				}
			}
			
			throw invalid_argument("Error: The shape of the Tensors don't match");
		}

			// Tensor2D X Tensor1D
		friend Tensor2D operator*(Tensor2D& t2d, Tensor1D& t1d){
			vector<int> t1d_shape = t1d.shape();
			vector<int> t2d_shape = t2d.shape();
		
			
			if(t1d_shape[0]==t2d_shape[1]){
				vector<double> t1d_v = t1d.get();
				vector<vector<double>> t2d_v = t2d.get();
			
				Tensor2D c;
				for(int i = 0;i<t2d_shape[0];i++){
					vector<double>r;
					for(int j = 0;j<t2d_shape[1];j++){
						double x = t1d_v[j]*t2d_v[i][j];
						r.push_back(x);
					}
					c.push(r);
				}

				return c;
			}

			throw invalid_argument("The inner shape of Tensor2D doesn't match that of Tensor1D");
		}


		friend Tensor2D operator*(Tensor1D& t1d, Tensor2D& t2d){
			return t2d*t1d;
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
					vector<double> row;
					for(int j = 0;j<dimensions[1];j++){
						row.push_back(tensor[i][j]/t.tensor[i][j]);
					}
					res.push(row);
				}
				return res;
			}else if(dimensions[0]==t.shape()[0]){
				// if the parent of the operator is single element 2D tensor
				if( dimensions[1]==1){
					Tensor2D res;
					for(int i = 0;i<dimensions[0];i++){
						vector<double> row;
						for(int j = 0;j<t.shape()[1];j++){
							row.push_back(tensor[i][0]/t.tensor[i][j]);
						}
						res.push(row);
					}
					return res;

				}
				// if the operated Tensor is single element 2D tensor
				else if(t.shape()[1]==1){
					Tensor2D res;
					for(int i = 0;i<dimensions[0];i++){
						vector<double> row;
						for(int j = 0;j<dimensions[1];j++){
							row.push_back(tensor[i][j]/t.tensor[i][0]);
						}
						res.push(row);
					}
					return res;
				}
			}
				

			throw invalid_argument("Error: The shape of the Tensors don't match");
		}

		friend Tensor2D operator/(double n, Tensor2D& t){
			Tensor2D res;
			for(int i = 0;i<t.dimensions[0];i++){
				vector<double>row;
				for(int j=0;j<t.dimensions[1];j++){
					row.push_back(n/t.tensor[i][j]);
				}
				res.push(row);
			}
			return res;
		}

			//Tensor2d / Tensor1d;
		friend Tensor2D operator/(Tensor2D& t2d, Tensor1D& t1d){
			Tensor1D r;
			r = 1/t1d;
			return t2d*r;
		}

		friend Tensor2D operator/(Tensor1D& t1d, Tensor2D& t2d){
			Tensor2D r(1/t2d);
			return t1d*r;
		}

};





#endif