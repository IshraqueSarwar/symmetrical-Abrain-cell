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




int main(int argc, char* argv[]){
	/* demo of single layer neuron rundown*/
	NNL nl;
	Tensor2D inputs({{ 0.        ,  0.        },
		       { 0.1068272 , -0.22602643},
		       {-0.3565171 ,  0.35056463},
		       { 0.54027534, -0.52019477},
		       {-0.9980913 , -0.06175594},
		       {-0.        , -0.        },
		       { 0.09934813,  0.22941218},
		       { 0.35293192, -0.35417378},
		       {-0.73923534,  0.12661397},
		       { 0.97696507,  0.2133992 }});

	Layer_dense dense1(2,4);
	Tensor2D output = dense1.forward(inputs);
	output.print();

	cout<<"\n\n";

	/* Rectified linear activation function*/
	Activation_ReLU activation1;
	output = activation1.forward(output);
	output.print();

	/* Softmax activation function*/
	Activation_Softmax activation2;
	output = activation2.forward(output);
	output.print();


	// Tensor2D t({{1,2,3},
	// 			{2,3,4},
	// 			{1,1,2}});
	// Tensor2D g({{1,2,3}});

	// Tensor2D f({{1},{3},{2}});


	// Tensor2D z = f+t;
	// z.print();



}
