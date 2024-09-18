#include "NNL.h"
// #include "t1d.h"
#include "t2d.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>



using namespace std;


// main constructor for 1-dimensional tensor
NNL::NNL(){

}

NNL::~NNL(){

}



Tensor1D NNL::dot(Tensor1D& t1, Tensor1D& t2){
	return t1*t2;
}

double NNL::dot(double t1, double t2){
	return t1*t2;
}

Tensor1D NNL::dot(Tensor2D& t1, Tensor1D& t2){
	return NNL::matvecmul(t1,t2);
}


Tensor2D NNL::dot(Tensor2D& t1, Tensor2D& t2){
	return NNL::matmul(t1, t2);
}


Tensor1D NNL::matvecmul(Tensor2D& a, Tensor1D& b){
	
	vector<int> t1_shape = a.shape();
	vector<int> t2_shape = b.shape();

	if(t1_shape[1]==t2_shape[0]){
		vector<vector<double>> t1 = a.get();
		vector<double> t2 = b.get();
		Tensor1D res;
		for(int i = 0;i<t1_shape[0];i++){
			double prodsum = 0;
			for(int j = 0;j<t1_shape[1];j++){
				prodsum+= t1[i][j]*t2[j];
			}
			res.push(prodsum);
		}

		return res;

	}
	throw invalid_argument("Error: Shapes ("+to_string(t1_shape[0]) + ", "+ to_string(t1_shape[1])+") and ("+ to_string(t2_shape[0])+") not aligned" );
}


Tensor2D NNL::matmul(Tensor2D& a, Tensor2D& b){
	vector<int> t1_shape = a.shape();
	vector<int> t2_shape = b.shape();

	if(t1_shape[1]==t2_shape[0]){
		vector<vector<double>> t1 = a.get();
		vector<vector<double>> t2 = b.get();

		Tensor2D res;
		for(int i = 0;i<t1_shape[0];i++){
			vector<double> x;
			for(int j = 0;j<t2_shape[1];j++){
				double z = 0;
				for(int k = 0;k<t1_shape[1];k++){
					z+=t1[i][k]*t2[k][j];
				}
				x.push_back(z);
			}
			res.push(x);
		}

		return res;
	
	}

	throw invalid_argument("Error: Shapes ("+to_string(t1_shape[0]) + ", "+ to_string(t1_shape[1])+") and ("+ to_string(t2_shape[0])+") not aligned" );

}



Tensor2D NNL::random_randn(int n_inputs, int n_neurons, int seed){
	random_device rd;
	mt19937 gen(rd());
	
	// if(seed){
	// 	mt19937 gen(seed);
	// }else{
		
	// }

	// uniform_real_distribution<double> dis(-1.0, 1.0);
	normal_distribution<double>dis(0.0,1.0);//GAUSSIAN DISTRIB: mean, standard deviation

	Tensor2D res;
	for(int i = 0;i<n_inputs;i++){
		vector<double> row;
		for(int j = 0;j<n_neurons;j++){
			// double random_number = dis(gen);
			// cout<<random_number<<endl;
			row.push_back(dis(gen));
		}

		res.push(row);

	}

	return res;
}


Tensor2D NNL::zeros(int n_inputs, int n_neurons){
	Tensor2D res;
	for(int i=0;i<n_inputs;i++){
		vector<double>row;
		for(int j = 0;j<n_neurons;j++){
			row.push_back(0.0);
		}
		res.push(row);
	}
	return res;
}

//The maximum function:
Tensor1D NNL::maximum(Tensor1D& a, Tensor1D& b){
	vector<int>t1_shape = a.shape();
	vector<int>t2_shape = b.shape();
	if(t1_shape==t2_shape){
		vector<double> t1 = a.get();
		vector<double> t2 = b.get();

		Tensor1D res;
		for(int i = 0;i<t1_shape[0];i++){
			res.push(max(t1[i], t2[i]));
		}
		return res;
	}
	throw invalid_argument("The shape of the Tensors aren't same.");
}

Tensor1D NNL::maximum(double n, Tensor1D& a){
	Tensor1D res;
	vector<double> a_v = a.get();
	for(int i = 0;i<a.shape()[0];i++){
		res.push(max(n, a_v[i]));
	}
	return res;
}

Tensor1D NNL::maximum(Tensor1D& a, double n){
	return NNL::maximum(n,a);
}


Tensor2D NNL::maximum(double n, Tensor2D& a){
	Tensor2D res;
	vector<vector<double>> a_v = a.get();
	for(int i=0;i<a.shape()[0];i++){
		vector<double>row;
		for(int j = 0;j<a.shape()[1];j++){
			row.push_back(max(n, a_v[i][j]));
		}
		res.push(row);
	}
	return res;
}

Tensor2D NNL::maximum(Tensor2D& a, double n){
	return NNL::maximum(n, a);
}



Tensor2D NNL::maximum(Tensor2D& t2d, Tensor1D& t1d){
	vector<int>t1d_shape = t1d.shape();
	vector<int>t2d_shape = t2d.shape();

	if(t1d_shape[0]==t2d_shape[1]){
		Tensor2D res;

		vector<vector<double>> t2 = t2d.get();
		vector<double> t1 = t1d.get();
		

		for(int i= 0;i<t2d_shape[0];i++){
			vector<double>row;
			for(int j=0;j<t2d_shape[1];j++){
				row.push_back( max(t1[j], t2[i][j]) );
			}
			res.push(row);
		}
		return res;
	}
	throw invalid_argument("The inner shape of Tensor2D doesn't match that of Tensor1D");
}

Tensor2D NNL::maximum(Tensor1D& t1d, Tensor2D& t2d){
	return NNL::maximum(t2d, t1d);
}


Tensor2D NNL::maximum(Tensor2D& a, Tensor2D& b){
	vector<int> a_shape = a.shape();
	vector<int> b_shape = b.shape();

	vector<vector<double>> a_v = a.get();
	vector<vector<double>> b_v = b.get();
	
	if(a_shape==b_shape){
		Tensor2D res;
		for(int i=0;i<a_shape[0];i++){
			vector<double>row;
			for(int j = 0;j<a_shape[1];j++){
				row.push_back(max(a_v[i][j], b_v[i][j]));
			}
			res.push(row);
		}
		return res;

	}else if(a_shape[1]==b_shape[1]){
		Tensor2D res;
		if(a_shape[0]==1){
			for(int i=0;i<b_shape[0];i++){
				vector<double>row;
				for(int j = 0;j<b_shape[1];j++){
					row.push_back(max(a_v[0][j], b_v[i][j]));
				}
				res.push(row);
			}


		}else if(b_shape[0]==1){
			for(int i=0;i<b_shape[0];i++){
				vector<double>row;
				for(int j = 0;j<b_shape[1];j++){
					row.push_back(max(a_v[i][j], b_v[0][j]));
				}
				res.push(row);
			}
		}
		return res;
	}
	throw invalid_argument("The shapes don't match");
}


double NNL::n_max(Tensor1D& t, int axis){
	if(!axis){
		vector<double> t1 = t.get();
		double mx = t1[0];
		for(int i=1;i<t.shape()[0];i++){
			mx = max(mx, t1[i]);
		}
		return mx;
	}
	throw invalid_argument("Tensor1D doesn't have higher dimensions.");

}