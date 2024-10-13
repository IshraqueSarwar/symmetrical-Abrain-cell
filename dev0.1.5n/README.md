# Creating a Neural Net library from scratch in c++


# DOC:
	--> ASSIGNING
	Tensor2D t; <--empty tensor
	Tensor2D t1({{1.5,1.5,2.5}, {2.5,4.6,3.4}});
	Tensor2D t2({{2,1.7,2.4}, {2,4.9,4.4}});
	t = t1;
	t = t2;
	t2 = t1;

	--> printing
	t.print() <--print tensor in human readable format
	t.shape(print=true) 
		|	|
		|	|--->when print=true(which is always on), it prints the dimensions/shape of the tensor
		|	|---> return the raw vector<int>dimensions vector that can be used to iterate etc.
		|
		|
		v
	vector<int>dim = t.shape(print=false);

	(t1+ 2).print() <--- also outputs the resultant tensor in human readable format.


	-->operations
	Tensor1D t({1.5, 3.0, 2.2});
	Tensor1D t2({2.0, 2.0, 2.0});
	auto x = Tensor1D({1.9,2.5,9.3});
	
	t+=t2; <-- adds each corresponding elements from both tensors
	t = t-t2 <-- subs each corresponding elements from both tensors
	t+=3 	<-- int/double addition to elements in the tensor
	t = t*t2 <-- muls each corresponding elements from both tensors
	t = t/t2 <-- divs each corresponding elements from both tensors

	(t+=t2).print() <-- directly prints the result of the operation within the bracket

	--> basic tensor builtins
	Tensor2D r;r=nl.random_randn(2, 5);	<--- creates a 2D tensor with dim 2x5 using gaussian distribution randomization of mean =0 and std-dev=1.0
	r.print();

	Tensor2D r;r = nl.zeros(2, 5)
	r.print();

	--> basic NN layer
	// Testing out weights and biases run...
	NNL nl;


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

	layer2_output.print();


	/* In shorter format*/
	Tensor2D X({{ 0.        ,  0.        },
		       { 0.1068272 , -0.22602643},
		       {-0.3565171 ,  0.35056463},
		       { 0.54027534, -0.52019477},
		       {-0.9980913 , -0.06175594},
		       {-0.        , -0.        },
		       { 0.09934813,  0.22941218},
		       { 0.35293192, -0.35417378},
		       {-0.73923534,  0.12661397},
		       { 0.97696507,  0.2133992 }});

	Layer_dense dense1(2,4);
	Tensor2D output = dense1.forward(X);
	output.print();

	--> adding activation function

	1. (Rectified linear activation function)
	Activation_ReLU activation1;
	output = activation1.forward(output);
	output.print();

	2. (softmax activation function)
	Activation_Softmax activation2;
	output = activation2.forward(output);
	output.print();

	--> aux func
	NNL nmain;

	// NOTE: Can output two types, so user must use holds_alternative<type>(var) to detect type and then assign using get<type>(var)
	nmain.n_max(Tensor1D, axis, keepdims);--> types: double/ Tensor1D(if dimension is kept)
	nmain.n_max(Tensor2D, axis, keepdims);--> types: Tensor1D/ Tensor2D(if dimension is kept)
	
	
	Example:
		NNL nl;
		Tensor1D r({1,2,53,2,33,2});
		variant<double, Tensor1D> temp = nl.n_max(r, 0,true);
		if(holds_alternative<double>(temp)){
			double res = get<double>(temp);
		}else{
			Tensor1D res = get<Tensor1D>(temp);
			res.print();
		}


		Tensor2D r2({{1,0.5,0.2,-1},
				{-5,0.3,-2,1}});

		variant<double, Tensor1D, Tensor2D> temp = nl.n_max(r2, 1, true);
		
		if(holds_alternative<double>(temp)){
			auto res = get<double>(temp);
			cout<<res<<endl;
		}else if(holds_alternative<Tensor2D>(temp)){
			auto res = get<Tensor2D>(temp);
			res.print();
		}else{
			auto res = get<Tensor1D>(temp);
			res.print();

		}


		3. Using Cross entropy loss function to calculate loss.
		TODO: WRITE THE DOC!





	current build command: (will change as I incorporate cmake)   g++ -std=c++17 -o main NNL.cpp tensor.cpp main.cpp layer.cpp activation_functions.cpp loss_functions.cpp optimizers.cpp dataloader.cpp



# TODO BOARD(objective):
	(IMPORTANT Tensor2D += etc are not immutable right now. Need to do this asap)
	0. TRY TO FIND A MORE ACCURATE DATATYPE FOR STORING DATA. DOUBLE is rounding the numbers up
	1. 
	2. find how to override double subscript for Tensor2D [][]
	3. Change all vec<vec<double>> access temp for Tensor2D to direct access of Tensor2D using [][] after completing objective 1.
	4. Tensor print() func should always show decimal place
	5. Precompiled headers to speed up compilation time?
	6. Work on n/tensor & n-tensor overload for t1d and t2d.
	7. try to replicate random_randn just like numpy random.
	8. try to fix the random_randn's seed functionality.
	9. make sure the special case -, +, *, / operations work viceversa <--- DO THIS
	





# ERROR:
	1. after nnl.random_randn(n,m), if we multiply it by any DOUBLE, it throws SEGMENTATION FAULT--> just do the operations one at a time


# WARNINGS:
	1. Currently using NULL for double inital assignment. which isn't completely valid.


# DONE:
	1. Add validation while a new tensor is created making sure the dimensions are correct
		|
		|
		|---> this should solve problems with dimension errors in transpose and dot

	2. We can use typeid(var)==typeid(object) to check for obj-type
		|
		|--> this will help us to make a dynamic dot product function
				|
				|
				|--->a) 1D vs int
						b) 1D vs matrix --> check dimensions
						c) matrix vs matrix -->check dimenstions

	3. operator overloading:(for 1D Tensor) 
			|--->equal(for assiging another tensor) X
			|--->addition-auto type X
			|--->addition(w/another tensor)
			|--->subtraction
			|--->division
			|--->multiplication
	4. MAKE THE OVERLOAD WORK VICEVERSA.

	5. make explicit int and double overload 
			func(currently using auto)			<--- if not done, compiler will keep throwing warnings
												may not work below c++17
		Solution was to just use double as arg.


	6. Make the division operation more efficient using mul--> tensor*(1/n)

	7. make separate headers
			|
			|	<--- need to think about this--->
			|--->NNL.h (Main class/ parent class)?
			|--->t2d.h (Tensor2D definition)??
			|--->t1d.h (Tensor1D definition)???

	8. fix t+=(int/double) n and other shorthand operators
		*=, /=, -=

	9. t+=f where t & f are tensors(Tensor1D) and (Tensor2D)

	10. Create overloads for Tensor2D

	11. covered most of dot product for Tensor1D

	12. implemented Matric-vector multiplication

	13. changed Tparent class to NNL class

	14. Implement Matrix multiplication.

	15. Implement Matrix vector multiplication

	16. Now we can do cross class addition,

	17. Tested 2 layers of pass.

	18. Created gaussian distrbution based Tensor2D randomized generator

	19. update res.tensor.push_bach --> res.push

	20. overloading operator for cross-class operations ie.tensor2d *=tensor1d

	21. If the other tensor is of shape(1, N), we operate the first tensor to all

	22. Maybe develop += etc operators for cross class??

	23. Tensor::tensor = other.tensor ---> Tensor::set(other.get());

	24. created the categorical cross entropy loss function for calculating the loss of the network.

	25. complete the Layer_dense class
		focus on overloading them from the main parent class.
	
	26.  optimize the subtraction operators using addition.

	27. check the output shape and corrected confidences shape after calculations

	28.  create the calculate loss function for main loss class

	29. Maybe implement [] access for tensors.

	30. create a separate .t() function that doesnt transpose the main tensor but rather returns a transposed tensor for use.

	31. Change the direct usage of dimension variable from t1d and t2d files, user this->shape() or t.shape() to access the dimensions.

	32. make a dataset creator using the existing python library <--will be useful for testing.