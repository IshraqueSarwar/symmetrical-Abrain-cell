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
	// Tensor2D t2d({{1,1,1},{1,2,3}});
	// Tensor1D t1d({1,2,4});
	// (1/t1d).print();
	// Tensor2D res(t2d+t1d);
	// res.print();
	// (t2d+t1d).print();
	// (t1d+t2d).print();
	// (t2d/t1d).print();
	// (t1d/t2d).print();


	
	// Testing out weights and biases run...
	NNL nl;
	/*


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

	Tensor2D r(nl.random_randn(2, 5));
	r.print();
	



}
