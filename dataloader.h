#ifndef DATALOADER_H
#define DATALOADER_H

#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include "t2d.h"


class BasicDataLoaderFromTxt{
	public:



		BasicDataLoaderFromTxt();
		~BasicDataLoaderFromTxt();

		/* we're writing this class to be able to read the data
			that is being outputted by the datagenerator.py file
			the output of the python file is string of datapoints
			we need to manually load data that is either Tensor1D or 2D*/
		Tensor1D loadT1(string filename);
		Tensor2D loadT2(string filename);


	private:
};


#endif