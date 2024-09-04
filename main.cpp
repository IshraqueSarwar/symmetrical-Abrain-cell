#include <stdexcept>
#include <iomanip>
#include <iostream>

#include "Tparent.h"
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


	
	Tensor2D t2({{2,1.7,2.4}, {2,4.9,4.4}});
	Tensor1D t({6.4,4.0, 3.0});
	Tparent nmath;
	(nmath.dot(t2,t)).print();
	// Tensor1D d(nmath.dot(t,f));
	// d.print();


}