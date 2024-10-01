#include "NNL.h"
// #include "t1d.h"
#include "t2d.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <variant>
#include <limits>

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


/* NOTE: Can output two types, so user must use holds_alternative<type>(var) to detect type and then assign using gets<type>(var)*/
variant<double, Tensor1D> NNL::n_max(Tensor1D& t, int axis, bool keepdims){
	if(!axis){
		vector<double> t1 = t.get();
		double mx = t1[0];
		for(int i=1;i<t.shape()[0];i++){
			mx = max(mx, t1[i]);
		}
		

		if(keepdims){
			Tensor1D res;
			res.push(mx);
			return res;
		}

		return mx;
	}
	throw invalid_argument("Tensor1D doesn't have higher dimensions.");

}

variant<double, Tensor1D, Tensor2D> NNL::n_max(Tensor2D& t2d, int axis, bool keepdims){
	vector<vector<double>> t = t2d.get();
	if(axis==-1){
		double mx = t[0][0];
		for(int i=0;i<t2d.shape()[0];i++){
			for(int j=0;j<t2d.shape()[1];j++){
				mx = max(mx, t[i][j]);
			}
		}

		if(keepdims){
			Tensor2D res;
			res.push(vector<double>{mx});
			return res;
		}
		return mx;

	}else if(axis==0){
		vector<double> res;
		for(int j = 0;j<t2d.shape()[1];j++){
			double mx = numeric_limits<double>::infinity();
			for(int i = 0;i<t2d.shape()[0];i++){
				if(mx==numeric_limits<double>::infinity()){
					mx = t[i][j];
				}else{
					mx = max(mx, t[i][j]);
				}
			}

			res.push_back(mx);
		}
		if(keepdims){
			Tensor2D temp;
			temp.push(res);
			return temp;

		}
		return Tensor1D(res);


	}else if(axis==1){

		vector<double> res;
		for(int i =0;i<t2d.shape()[0];i++){
			double mx = numeric_limits<double>::infinity();
			for(int j = 0;j<t2d.shape()[1];j++){
				if(mx == numeric_limits<double>::infinity()){
					mx = t[i][j];
				}else{
					mx = max(mx, t[i][j]);
				}
			}
			res.push_back(mx);
		}
		if(keepdims){
			Tensor2D temp;
			for(auto i:res){

				temp.push(vector<double>{i});
			}
			return temp;
		}

		return Tensor1D(res);

	}

	throw invalid_argument("Tensor2D doesn't have higher dimensions.");
}


variant<double, Tensor1D> NNL::n_sum(Tensor1D& t, int axis, bool keepdims){
	if(!axis){
		vector<double> t1 = t.get();
		double sm = t1[0];
		for(int i=1;i<t.shape()[0];i++){
			sm += t1[i];
		}
		

		if(keepdims){
			Tensor1D res;
			res.push(sm);
			return res;
		}

		return sm;
	}
	throw invalid_argument("Tensor1D doesn't have higher dimensions.");

}



variant<double, Tensor1D, Tensor2D> NNL::n_sum(Tensor2D& t2d, int axis, bool keepdims){
	vector<vector<double>> t = t2d.get();
	if(axis==-1){
		double sm = 0;
		for(int i=0;i<t2d.shape()[0];i++){
			for(int j=0;j<t2d.shape()[1];j++){
				sm += t[i][j];
			}
		}

		if(keepdims){
			Tensor2D res;
			res.push(vector<double>{sm});
			return res;
		}
		return sm;

	}else if(axis==0){
		vector<double> res;
		for(int j = 0;j<t2d.shape()[1];j++){
			double sm = 0;
			for(int i = 0;i<t2d.shape()[0];i++){
				sm+=t[i][j];
			}

			res.push_back(sm);
		}
		if(keepdims){
			Tensor2D temp;
			temp.push(res);
			return temp;

		}
		return Tensor1D(res);


	}else if(axis==1){

		vector<double> res;
		for(int i =0;i<t2d.shape()[0];i++){
			double sm = 0;
			for(int j = 0;j<t2d.shape()[1];j++){
				sm+=t[i][j];
			}
			res.push_back(sm);
		}
		if(keepdims){
			Tensor2D temp;
			for(auto i:res){

				temp.push(vector<double>{i});
			}
			return temp;
		}

		return Tensor1D(res);

	}

	throw invalid_argument("Tensor2D doesn't have higher dimensions.");
}




Tensor1D NNL::n_exp(Tensor1D& t1d){
	vector<double> t = t1d.get();
	Tensor1D res;
	for(int i =0;i<t1d.shape()[0];i++){
		res.push(exp(t[i]));
	}
	return res;
}

Tensor2D NNL::n_exp(Tensor2D& t2d){
	vector<vector<double>> t = t2d.get();

	Tensor2D res;
	for(int i=0;i<t2d.shape()[0];i++){
		vector<double>v;
		for(int j = 0;j<t2d.shape()[1];j++){
			v.push_back(exp(t[i][j]));
		}
		res.push(v);
	}

	return res;
}


double NNL::n_mean(Tensor1D& t1d){
	double sum = 0;
	int size = t1d.shape()[0];
	vector<double> t = t1d.get();

	for(int i=0;i<size;i++){
		sum+=t[i];
	}

	return (sum/size);
}

double NNL::n_mean(Tensor2D& t2d){
	double sum = 0;
	int size = t2d.shape()[0]* t2d.shape()[1];
	vector<vector<double>> t = t2d.get();

	for(int i=0;i<t2d.shape()[0];i++){
		for(int j=0;j<t2d.shape()[1];j++){
			sum+= t[i][j];
		}
	}

	return (sum/size);
}

double NNL::n_log(double n){
	return log(n);
}


Tensor1D NNL::n_log(Tensor1D t1d){
	vector<double> t = t1d.get();

	for(int i = 0;i<t.size();i++){
		t[i]=log(t[i]);
	}

	return Tensor1D(t);

}


Tensor2D NNL::n_log(Tensor2D t2d){
	vector<vector<double>> t = t2d.get();

	for(int i=0;i<t2d.shape()[0];i++){
		for(int j=0;j<t2d.shape()[1];j++){
			t[i][j]=log(t[i][j]);
		}
	}
	return Tensor2D(t);
}


Tensor1D NNL::n_clip(Tensor1D t1d, double mn, double mx){
	vector<double> t = t1d.get();
	for(int i=0;i<t1d.shape()[0];i++){
		if(t[i]>mx){
			t[i] = mx;
		}else if(t[i]<mn){
			t[i]=mn;
		}
	}

	return Tensor1D(t);
}


Tensor2D NNL::n_clip(Tensor2D t2d, double mn, double mx){
	vector<vector<double>> t = t2d.get();
	for(int i = 0;i<t2d.shape()[0];i++){
		for(int j =0;j<t2d.shape()[1];j++){
			if(t[i][j]>mx){
				t[i][j]=mx;
			}else if(t[i][j]<mn){
				t[i][j]=mn;
			}
		}
	}

	return Tensor2D(t);
}