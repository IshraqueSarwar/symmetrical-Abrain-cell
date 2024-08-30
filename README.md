
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
	
	t+=t2; <-- adds each corresponding elements from both tensors
	t = t-t2 <-- subs each corresponding elements from both tensors
	t+=3 	<-- int/float addition to elements in the tensor
	t = t*t2 <-- muls each corresponding elements from both tensors
	t = t/t2 <-- divs each corresponding elements from both tensors





# TODO BOARD:

	2. Tensor print() func should always show decimal place
	3. Make the division operation more efficient using mul--> tensor*(1/n)
	3. make separate headers
			|
			|	<--- need to think about this--->
			|--->NNL.h (Main class/ parent class)?
			|--->t2d.h (Tensor2D definition)??
			|--->t1d.h (Tensor1D definition)???
	4. Create overloads for Tensor2D




# ERROR:
	1. t+=f where t & f are tensors(Tensor1D)




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



