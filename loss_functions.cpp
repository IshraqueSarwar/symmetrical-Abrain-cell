#include "loss_functions.h"
#include "NNL.h"


using namespace std;

NNL nll;

Loss::Loss(){

}

Loss::~Loss(){

}

Loss_CategoricalCrossentropy::Loss_CategoricalCrossentropy(){

}


Loss_CategoricalCrossentropy::~Loss_CategoricalCrossentropy(){

}


Tensor2D Loss_CategoricalCrossentropy::forward(Tensor2D y_pred, Tensor1D y_true){
	Tensor2D y_pred_clipped = nll.n_clip(y_pred, 1e-7, 1- (1e-7));

	Tensor1D range;
	for(int i = 0;i<y_pred.shape()[0];i++)range.push(i);

	Tensor1D corrected_confidences = y_pred_clipped.get(range, y_true);
	

	//TODO: check the output shape and corrected confidences shape after calculations
	/* this shouldn't ne Tensor1D as output is tensor2d--->*/Tensor1D negative_log_likelihoods = nll.n_log(corrected_confidences);
	negative_log_likelihoods*=-1;

	return negative_log_likelihoods;
}

Tensor2D Loss_CategoricalCrossentropy::forward(Tensor2D y_pred, Tensor2D y_true){

}