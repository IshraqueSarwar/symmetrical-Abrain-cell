

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
		vector<int> shape(bool print=true){
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
		// Tensor + n
	Tensor2D operator+(int n)const{
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

		// n + Tensor
	friend Tensor2D operator+(int n, Tensor2D& t){
		return t+n;
	}

		// (double)n + Tensor
	friend Tensor2D operator+(double n, Tensor2D& t){
		return t+n;
	}

		// Tensor + Tensor



	/* SUBTRACTION OVERLOADING */

		// Tensor - n

		// Tensor - (double) n

		//

};














// 1d tensor class

class Tensor1D: public NNL{
	private:
		vector<float> tensor;
		vector<int>dimensions;


	public:
		// main constructor
		Tensor1D();
		Tensor1D(vector<float> t1d);

		Tensor1D(const Tensor1D& other);
		
		



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