#include "dataloader.h"
#include <cstdlib>
#include <string>
using namespace std;



BasicDataLoaderFromTxt::BasicDataLoaderFromTxt(){}


BasicDataLoaderFromTxt::~BasicDataLoaderFromTxt(){}


Tensor1D BasicDataLoaderFromTxt::loadT1(string filename){
	ifstream datafile(filename);

	vector<double> dv;

	string l1;
	while(getline(datafile, l1, ',')){
		double d1 = stod(l1);
		dv.push_back(d1);
	}




	return Tensor1D(dv);


}

Tensor2D BasicDataLoaderFromTxt::loadT2(string filename){
	ifstream datafile(filename);

	Tensor2D data;
	string l1;
	while(getline(datafile, l1, ',')){
		double d1 = stod(l1);

		string l2;
		getline(datafile, l2, '\n');
		double d2 = stod(l2);

		vector<double> dv = {d1, d2};

		data.push(dv);
	}

	return data;
}