//TODO BOARD:

	// 2. Tensor print() func should always show decimal place
	// 3. Make the division operation more efficient using mul--> tensor*(1/n)
	// 3. make separate headers
	//		|
	//		|	<--- need to think about this--->
	//		|--->NNL.h (Main class/ parent class)?
	//		|--->t2d.h (Tensor2D definition)??
	//		|--->t1d.h (Tensor1D definition)???
	// 4. Create overloads for Tensor2D




//ERROR:
	// 1. t+=f where t & f are tensors(Tensor1D)




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

	// 3. operator overloading:(for 1D Tensor) 
			// |--->equal(for assiging another tensor) X
			// |--->addition-auto type X
			// |--->addition(w/another tensor)
			// |--->subtraction
			// |--->division
			// |--->multiplication
	// 4. MAKE THE OVERLOAD WORK VICEVERSA.

	// 5. make explicit int and double overload 
	// 		func(currently using auto)			<--- if not done, compiler will keep throwing warnings
	//													may not work below c++17



#ifndef CLS_H
#define CLS_H
#include <stdexcept>

using namespace std;
	
class Tensor1D;
class Tensor2D;


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
		vector<float> get(){
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

		// EQUAL to assign
		Tensor1D operator=(const Tensor1D& other){
			tensor = other.tensor;
			// we need to update the dimension when we assign a new tensor, as the shape of the new
			// 		tensor can be different.
			update_dim();
			return tensor;
		}



		/* ADDITION overload*/
			//Tensor1D + n
		Tensor1D operator+(int n)const{
			Tensor1D res;

			for(int i = 0;i<tensor.size();i++){
				res.tensor.push_back(tensor[i]+n);
			}
			
			return res;
		}
			//Tensor1D + (double)n
		Tensor1D operator+(double n)const{
			Tensor1D res;

			for(int i = 0;i<tensor.size();i++){
				res.tensor.push_back(tensor[i]+n);
			}
			
			return res;
		}


			// n + Tensor1D
		friend Tensor1D operator+(int n, Tensor1D& t){
			return t+n;
		}	
			// (double)n + Tensor1D
		friend Tensor1D operator+(double n, Tensor1D& t){
			return t+n;
		}

			// Tensor1D + Tensor1D
		Tensor1D operator+(Tensor1D& t){
			if(dimensions==t.shape()){
				Tensor1D res;
				for(int i=0;i<tensor.size();i++){
					res.tensor.push_back(t.tensor[i]+tensor[i]);
				}
				return res;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
			
		}

		


		/* SUBTRACTION overlaod */
			// Tensor1D - n
		Tensor1D operator-(int n)const{
			Tensor1D res;

			for(int i=0;i<tensor.size();i++){
				res.tensor.push_back(tensor[i]-n);
			}

			return res;
		}

			// Tensor1D - n
		Tensor1D operator-(double n)const{
			Tensor1D res;

			for(int i=0;i<tensor.size();i++){
				res.tensor.push_back(tensor[i]-n);
			}

			return res;
		}

			// Tensor1D - Tensor1D
		Tensor1D operator-(Tensor1D& t){
			if(dimensions==t.shape()){
				Tensor1D res;
				for(int i=0;i<tensor.size();i++){
					res.tensor.push_back(t.tensor[i]-tensor[i]);
				}
				return res;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");

		}


		/* MULTIPLICATION overlaod */
			// Tensor1D x n
		Tensor1D operator*(int n)const{
			Tensor1D res;

			for(int i = 0;i<tensor.size();i++){
				res.tensor.push_back(tensor[i]*n);
			}
			
			return res;
		}
			// Tensor1D x (double)n
		Tensor1D operator*(double n)const{
			Tensor1D res;

			for(int i = 0;i<tensor.size();i++){
				res.tensor.push_back(tensor[i]*n);
			}
			
			return res;
		}


			// Tensor x Tensor
		Tensor1D operator*(Tensor1D& t){
			if(dimensions==t.shape()){
				Tensor1D res;
				for(int i=0;i<tensor.size();i++){
					res.tensor.push_back(t.tensor[i]*tensor[i]);
				}
				return res;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
		}


			// n x Tensor1D
		friend Tensor1D operator*(int n, Tensor1D& t){
			return t*n;
		}
			// (double)n x Tensor1D
		friend Tensor1D operator*(double n, Tensor1D& t){
			return t*n;
		}





		/* DIVISION overload */
			// Tensor / n
		Tensor1D operator/(int n)const{
			Tensor1D res;
			for(int i =0;i<tensor.size();i++){
				res.tensor.push_back(tensor[i]/n);
			}
			return res;
		}

			// Tensor / n
		Tensor1D operator/(double n)const{
			Tensor1D res;
			for(int i =0;i<tensor.size();i++){
				res.tensor.push_back(tensor[i]/n);
			}
			return res;
		}

			// Tensor / Tensor
		Tensor1D operator/(Tensor1D& t){
			if(dimensions==t.shape()){
				Tensor1D res;
				for(int i=0;i<tensor.size();i++){
					res.tensor.push_back(tensor[i]/t.tensor[i]);
				}
				return res;
			}
			throw invalid_argument("Error: The shape of the Tensors don't match");
		}




};


#endif