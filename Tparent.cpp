#include "Tparent.h"
#include "t1d.h"
#include "t2d.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>


using namespace std;


// main constructor for 1-dimensional tensor
Tparent::Tparent(){

}

Tparent::~Tparent(){

}



Tensor1D Tparent::dot(Tensor1D& t1, Tensor1D& t2){
	return t1*t2;
}
