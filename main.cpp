#include <stdexcept>
#include <iomanip>
#include <iostream>

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
	/* 1D testing */
	// testTensor1D();


	/* 2D testing */
	// testTensor2D();



	// cross class operations..
	// Tensor2D t2d({{1,6, -2, -1},
	// 			{-7, -2, -5, 1}});
	// Tensor2D t({{1,2,4,1}});
	// Tensor1D t1d({1,2,4,1});
	// t1d*=-1;
	// t2d/=t1d;
	// t2d.print();

	// Tensor2D res(t2d+t1d);
	// res.print();
	// (t2d+t1d).print();
	// (t1d+t2d).print();
	// (t2d/t1d).print();
	// (t1d/t2d).print();


	
	// Testing out weights and biases run...
	
	/*
	NNL nl

	//Layer 1
	Tensor2D inputs({{1.0,2.0,3.0,2.5},
						{2.0,5.0,-1.0,2.0},
						{-1.5,2.7,3.3,-0.8}});

	Tensor2D weights({{0.2,0.8,-0.5,1},
						{0.5,-0.91,0.26,-0.5},
						{-0.26,-0.27,0.17,0.87}});

	Tensor2D weights2({{0.1,-0.14,0.5},
						{-0.5,0.12,-0.33},
						{-0.44,0.73,-0.13}});

	Tensor1D biases({2.0,3.0,0.5});
	Tensor1D biases2({-1,2,-0.5});

	
	// transpose the weights first. to match the shape.
	weights.transpose();
	Tensor2D iw(nl.dot(inputs, weights));
	Tensor2D layer1_output(iw+biases);

	weights2.transpose();
	iw = nl.dot(layer1_output, weights2);
	Tensor2D layer2_output(iw+biases2);

	layer2_output.print();*/

	

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



	Tensor1D r({1,2,4,1});
	Tensor2D r2({{1,0.5,0.2,-1},
               {-5,0.3,-2,1}});

	NNL nmain;
	cout<<nmain.n_max(r2)<<endl;

	Tensor1D res = nmain.n_max(r2,0);
	res.print();
	res = nmain.n_max(r2,1);
	res.print();

	// double x =nmain.n_max(r);
	// cout<<x<<endl;

	// Tensor2D rand = nmain.random_randn(2,3);
	// rand.print();


}
