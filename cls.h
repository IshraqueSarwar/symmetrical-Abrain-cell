#ifndef CLS_H
#define CLS_H


using namespace std;


class NNL{

	public:
		virtual void print(){
		}


		void printTensorDim(vector<int>d){
			cout<<"Tensor.dim(";
			if(d.size()==2){
				cout<<d[0]<<", "<<d[1];
			}else{
				cout<<d[0];
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

		//returning dimesion vector;
		vector<int> dim(){
			NNL::printTensorDim(dimensions);
			return dimensions;
		}


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




		Tensor1D transpose(){
			// transposing a 1D tensor gives us the same tensor
			return tensor;
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