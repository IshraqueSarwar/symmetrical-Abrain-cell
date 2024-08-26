#ifndef CLS_H
#define CLS_H


using namespace std;


//TODO BOARD:
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
class Tensor2D: public NNL{
	vector<vector<float>> tensor;
	vector<int>dimensions;


	public:
		Tensor2D();
		Tensor2D(vector<vector<float>>t2d);

		//TODO: getter func

		//setter func
		void set(vector<vector<float>> t2d){
			tensor = t2d;
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
		
		

		//TODO: getter



		//setter
		void set(vector<float> t1d){
			tensor = t1d;
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

};


#endif