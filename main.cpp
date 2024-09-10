#include <stdexcept>
#include <iomanip>
#include <iostream>

#include "NNL.h"
#include "t1d.h"
#include "t2d.h"

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
	Tensor2D t2d({{1,1,1},{1,2,3}});
	Tensor1D t1d({1,1,1});

	(t1d-t2d).print();


	
	// Testing out weights and biases run...

	// NNL nl;
	// // Tensor1D inputs({1.0,2.0,3.0,2.5});


	// Tensor2D inputs({{1.0,2.0,3.0,2.5},
	// 					{2.0,5.0,-1.0,2.0},
	// 					{-1.5,2.7,3.3,-0.8}});

	// Tensor2D weights({{0.2,0.8,-0.5,1},
	// 					{0.5,-0.91,0.26,-0.5},
	// 					{-0.26,-0.27,0.17,0.87}});

	// Tensor1D biases({2.0,3.0,0.5});

	
	// // transpose the weights first. to match the shape.
	// weights.transpose();

	// Tensor2D layer_output(nl.dot(weights, inputs)+biases);

	// layer_output.print();
}
