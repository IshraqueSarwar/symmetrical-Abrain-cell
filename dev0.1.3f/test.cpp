#include <iostream>
#include <vector>

using namespace std;


vector<int> returnDim(vector<auto>v){
	vector<int>d;
	//if the vector consists of floating point numners
	d.push_back(v.size())
	if(typeid(v[0])==typeid(1.0)){
		return d;
	}

	vector<int>x = returnDim(v[0]);

	for(auto i: x){
		d.push_back(i);
	}

	return d;
}



int main(){
	vector<float>v = {1.4, 2.5, 3.6};
	vector<float>r = {4.3};
	vector<vector<float>>v2 = {{1.2, 4.3, 6.7}, {3.4, 9.9, 6.5}};


	vector<int>Dim = returnDim(v2);
	return 0;
}