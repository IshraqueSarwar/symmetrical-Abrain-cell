#ifndef T2D_H
#define T2D_H
#include <stdexcept>
#include <iomanip>
#include "Tparent.h"
#include "t1d.h"

using namespace std;
	
class Tensor1D;
class Tensor2D;



// 2d tensor class
class Tensor2D: public NNL{
	private:
		vector<vector<float>> tensor;
		vector<int>dimensions;


	public:
		Tensor2D();
		Tensor2D(vector<vector<float>>t2d, bool validify = false);


		


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

		

		//setter func
		void set(vector<vector<float>> t2d){
			tensor = t2d;
		}

		//getter func
		vector<vector<float>> get(){
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

		// Tensor + Tensor
	Tensor2D operator+(Tensor2D& t){
		if(dimensions==t.shape()){
			Tensor2D res;
			for(int i = 0;i<dimensions[0];i++){
				vector<float> row;
				for(int j =0;j<dimensions[1];j++){
					row.push_back(t.tensor[i][j]+tensor[i][j]);
				}
				res.tensor.push_back(row);
			}
			return res;
		}else{
			throw invalid_argument("Error: The shape of the Tensors don't match");
		}
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
		}else{
			throw invalid_argument("Error: The shape of the Tensors don't match");
		}

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
		}else{
			throw invalid_argument("Error: The shape of the Tensors don't match");
		}
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
		}else{
			throw invalid_argument("Error: The shape of the Tensors don't match");
		}
	}

};





#endif