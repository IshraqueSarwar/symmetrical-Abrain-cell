#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <variant>

#include "NNL.h"
#include "t1d.h"
#include "t2d.h"
#include "layer.h"
#include "activation_functions.h"



using namespace std;





void testTensor2D(){
	Tensor2D t1({{1.5,1.5,2.5}, {2.5,4.6,3.4}});
	Tensor2D t2({{2,1.7,2.4}, {2,4.9,4.4}});
	
	t2*=2;
	t2.print();
}


void testTensor1D(){
	Tensor1D t({6.4,4.0, 3.0});
	Tensor1D f({2,2, 2});
	

	
	Tensor1D tr(f);

	tr.print();

	(t/=f).print();

}


variant<Tensor1D, Tensor2D> testFunc(bool keepdims){
	Tensor1D r({1,2,4});
	Tensor2D t({{1,2,5}, {2,3,6}});

	if(keepdims){
		return t;
	}else{
		return r;
	}
}



int main(int argc, char* argv[]){
	/* demo of single layer neuron rundown*/
	// Tensor2D X({{ 0.        ,  0.        },
	// 	       { 0.1068272 , -0.22602643},
	// 	       {-0.3565171 ,  0.35056463},
	// 	       { 0.54027534, -0.52019477},
	// 	       {-0.9980913 , -0.06175594},
	// 	       {-0.        , -0.        },
	// 	       { 0.09934813,  0.22941218},
	// 	       { 0.35293192, -0.35417378},
	// 	       {-0.73923534,  0.12661397},
	// 	       { 0.97696507,  0.2133992 }});

	// Layer_dense dense1(2,4);
	// Tensor2D output = dense1.forward(X);
	// output.print();

	// cout<<"\n\n";
	
	// Activation_ReLU activation1;
	// output = activation1.forward(output);
	// output.print();

	NNL nl;
	Tensor1D r({1,2,2,2,1,2});
	// variant<double, Tensor1D> temp = nl.n_sum(r);
	// if(holds_alternative<double>(temp)){
	// 	double res = get<double>(temp);
	// 	cout<<res<<endl;
	// }else{
	// 	Tensor1D res = get<Tensor1D>(temp);
	// 	res.print();
	// }
	

	Tensor2D r2({{1,1,2,1},
				{2,3,1,4}});

	variant<double, Tensor1D, Tensor2D> temp = nl.n_sum(r2,1, true);
	
	if(holds_alternative<double>(temp)){
		auto res = get<double>(temp);
		cout<<res<<endl;
	}else if(holds_alternative<Tensor2D>(temp)){
		auto res = get<Tensor2D>(temp);
		res.print();
	}else{
		auto res = get<Tensor1D>(temp);
		res.print();

	}


	r = nl.n_exp(r);
	r.print();
	r2 = nl.n_exp(r2);
	r2.print();





}
