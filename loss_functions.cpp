#include "loss_functions.h"
#include "NNL.h"


using namespace std;

NNL nll;

Loss::Loss(){

}

Loss::~Loss(){

}




double Loss::calculate(Tensor2D output, Tensor1D y){
	Loss_CategoricalCrossentropy catLoss;
	Tensor1D sample_losses= catLoss.forward(output, y);

	double data_loss = nll.n_mean(sample_losses);

	return data_loss;
}


double Loss::calculate(Tensor2D output, Tensor2D y){
	Loss_CategoricalCrossentropy catLoss;
	Tensor1D sample_losses= catLoss.forward(output, y);
	
	double data_loss = nll.n_mean(sample_losses);

	return data_loss;
}




Loss_CategoricalCrossentropy::Loss_CategoricalCrossentropy(){

}


Loss_CategoricalCrossentropy::~Loss_CategoricalCrossentropy(){

}


Tensor1D Loss_CategoricalCrossentropy::forward(Tensor2D y_pred, Tensor1D y_true){
	Tensor2D y_pred_clipped = nll.n_clip(y_pred, 1e-7, 1- (1e-7));

	Tensor1D range;
	for(int i = 0;i<y_pred.shape()[0];i++)range.push(i);

	Tensor1D corrected_confidences = y_pred_clipped.get(range, y_true);
	

	Tensor1D negative_log_likelihoods = nll.n_log(corrected_confidences);
	negative_log_likelihoods*=-1;

	return negative_log_likelihoods;
}

Tensor1D Loss_CategoricalCrossentropy::forward(Tensor2D y_pred, Tensor2D y_true){
	Tensor2D y_pred_clipped = nll.n_clip(y_pred, 1e-7, 1-(1e-7));

	Tensor2D inner_prod = y_pred_clipped*y_true;
	Tensor1D corrected_confidences = get<Tensor1D>(nll.n_sum(inner_prod, 1));
	Tensor1D negative_log_likelihoods = nll.n_log(corrected_confidences);
	negative_log_likelihoods*=-1;

	return negative_log_likelihoods;
}



void Loss_CategoricalCrossentropy::backward(Tensor2D dvalues, Tensor1D y_true){
	int samples = dvalues.shape()[0];
	int labels = dvalues.shape()[1];

	Tensor2D y_true_onehot = nll.convert_to_onehot(labels, y_true);

	y_true_onehot*=-1;
	
	// calculating the gradient and then normalizing it by sample size
	Loss_CategoricalCrossentropy::dinputs = y_true_onehot/dvalues;
	Loss_CategoricalCrossentropy::dinputs = Loss_CategoricalCrossentropy::dinputs/samples;

}


void Loss_CategoricalCrossentropy::backward(Tensor2D dvalues, Tensor2D y_true){
	double samples = dvalues.shape()[0];
	double labels = dvalues.shape()[1];

	y_true*=-1;

	//calculating the gradient and then normalizing it by sample size
	Loss_CategoricalCrossentropy::dinputs = y_true/dvalues;
	Loss_CategoricalCrossentropy::dinputs = Loss_CategoricalCrossentropy::dinputs/samples;
}