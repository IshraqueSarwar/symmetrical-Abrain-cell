#ifndef NNL_H
#define NNL_H

#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <vector>
#include <random>
#include <variant>

using namespace std;


class Tensor1D;
class Tensor2D;

class NNL{

	public:
		NNL();
		virtual ~NNL();

		virtual void print(){
		}


		void printTensorDim(vector<int>d){

			cout<<"Tensor.shape(";
			for(auto i: d){
				cout<<std::setprecision(2);
				cout<<i<<", ";
			}
			cout<<")\n";
		}

		Tensor1D dot(Tensor1D& t1, Tensor1D& t2);
		double dot(double t1, double t2);
		/*dot netween Tensor2D and Tensor1D then matrix-vec mul*/
		Tensor1D dot(Tensor2D& t1, Tensor1D& t2);
		Tensor2D dot(Tensor2D& t1, Tensor2D& t2);


		/*when Tensor2D is mul by Tensor1D we use matric vec mul*/
		Tensor1D matvecmul(Tensor2D& a, Tensor1D& b);

		/* Matrix multiplication function for Tensor2D and Tensor2D operation*/
		Tensor2D matmul(Tensor2D& a, Tensor2D& b);


		
		/* randomized Tensor2D*/
		Tensor2D random_randn(int n_inputs, int n_neurons, int seed=0);

		/* tensor full of zeros */
		Tensor2D zeros(int n_inputs, int n_neurons);

		/* The maximum function:
			0. Tensor1D vs Tensor1D-Done
			1. Tensor1D vs Tensor2D-Done
			2. Tensor2D vs Tensor2D make sure if even the inner shape 
				matches we operate using the innder tensor
			3. Double/number vs Tensor2D-Done
			4. Double/number vs Tensor1D-Done
		*/
		Tensor1D maximum(Tensor1D& a, Tensor1D& b);
		
		Tensor1D maximum(double n, Tensor1D& a);
		Tensor1D maximum(Tensor1D& a, double n);

		Tensor2D maximum(double n, Tensor2D& a);
		Tensor2D maximum(Tensor2D& a, double n);

		Tensor2D maximum(Tensor2D& t2d, Tensor1D& t1d);
		Tensor2D maximum(Tensor1D& t1d, Tensor2D& t2d);

		Tensor2D maximum(Tensor2D& a, Tensor2D& b);


		/* The max function finds the max value(s) in a Tensor:
			1. Tensor2D (has 2 axis)
			2. Tensor1D (has 1 axis)*/
		/* NOTE: Can output two types, so user must use holds_alternative<type>(var) to detect type and then assign using gets<type>(var)*/

		variant<double, Tensor1D> n_max(Tensor1D& t, int axis=0, bool keepdims=false); 
		variant<double, Tensor1D, Tensor2D> n_max(Tensor2D& t2d, int axis=-1, bool keepdims = false);
		
		


		/* The n_sum function similar to n_max*/
		variant<double, Tensor1D> n_sum(Tensor1D& t, int axis=0, bool keepdims=false);
		variant<double, Tensor1D, Tensor2D> n_sum(Tensor2D& t, int axis=-1, bool keepdims=false);


		/* power of natural number(e)*/
		Tensor1D n_exp(Tensor1D& t1d);
		Tensor2D n_exp(Tensor2D& t2d);


		/*calculating mean for 1D and 2D Tensor */
		double n_mean(Tensor1D& t1d);
		double n_mean(Tensor2D& t2d);

		/*calculating log for Tensor1D and Tensor2D and double*/
		double n_log(double n);
		Tensor1D n_log(Tensor1D t1d);
		Tensor2D n_log(Tensor2D t2d);


		/*clipping values between min and max*/
		Tensor1D n_clip(Tensor1D t1d, double mn, double mx);
		Tensor2D n_clip(Tensor2D t2d, double mn, double mx);


		/* argmax function that returns the indices of the maximum val*/
		int n_argmax(Tensor1D t);
		Tensor1D n_argmax(Tensor1D t, int axis);
		int n_argmax(Tensor2D t);
		Tensor1D n_argmax(Tensor2D t, int axis);
		

};	


#endif