#ifndef CLS_H
#define CLS_H
#include <stdexcept>

using namespace std;


//TODO BOARD:
	// 1. operator overloading:(for 1D Tensor) 
		// |--->equal(for assiging another tensor) X
		// |--->addition-auto type X
		// |--->addition(w/another tensor)
		// |--->
		// |--->
		// |--->
		// |--->
	// 2. MAKE THE OVERLOAD WORK VICEVERSA.
	




// DONE:
	// 1. Add validation while a new tensor is created making sure the dimensions are correct
		// |
		// |
		// |---> this should solve problems with dimension errors in transpose and dot

	// 2. We can use typeid(var)==typeid(object) to check for obj-type
		// |
		// |--> this will help us to make a dynamic dot product function
				// |
				// |
				// |--->a) 1D vs int
				// 		b) 1D vs matrix --> check dimensions
				//		c) matrix vs matrix -->check dimenstions
	

class NNL{

	public:
		virtual void print(){
		}


		void printTensorDim(vector<int>d){

			cout<<"Tensor.shape(";
			for(auto i: d){
				cout<<i<<", ";
			}
			cout<<")\n";
		}


		
};






// 2d tensor class
// DOC: 
class Tensor2D: public NNL{
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
		Tensor2D get(){
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

		//returning dimesion vector;
		vector<int> dim(){
			update_dim();
			NNL::printTensorDim(dimensions);
			return dimensions;
		}



	//operation overload
	// Tensor2D operator+(int& n){

	// }

	private:


};





// 1d tensor class

class Tensor1D: public NNL{
	vector<float> tensor;
	vector<int>dimensions;


	public:
		// main constructor
		Tensor1D();
		Tensor1D(vector<float> t1d);

		Tensor1D(const Tensor1D& other);
		
		

		//TODO: getter



		//setter
		void set(const Tensor1D& other){
			tensor = other.tensor;
		}

		//getter
		Tensor1D get(){
			return tensor;
		}



		void transpose(){
			// transposing a 1D tensor gives us the same tensor
			
		}



		void print(){
			cout<<"Tensor<float, 1D>([";
			for(int i=0;i< tensor.size()-1; i++){
				cout<<tensor[i]<<", ";
			}
			cout<<tensor[tensor.size()-1]<<"])\n";
		}





		vector<int> dim(){
			NNL::printTensorDim(dimensions);
			return dimensions;
		}

		//overloading
		Tensor1D operator+(auto n)const{
			Tensor1D res;

			for(int i = 0;i<tensor.size();i++){
				res.tensor.push_back(tensor[i]+n);
			}
			
			return res;
		}
		// Tensor1D operator+(double n){
		// 	Tensor1D res;

		// 	for(int i = 0;i<tensor.size();i++){
		// 		res.tensor.push_back(tensor[i]+n);
		// 	}
			
		// 	return res;
		// }
		friend Tensor1D operator+(auto n, Tensor1D& t){
			return t+n;
		}



		Tensor1D operator=(const Tensor1D& other){
			tensor = other.tensor;
			return tensor;
		}


};


#endif