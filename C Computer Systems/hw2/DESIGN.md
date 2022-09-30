Hw2
Andrew Wu

In this program, we will write functions to perform tasks on arrays of integers. 
Given:
Makefile (do not change)
Hw2.c (do not change)
Num_array.h (do not change)
Write:
Num_array.c 
Design.md

Num_array.c:

finding the maximum element of an array

We can do this in many ways, but the easiest way we could do this is just by setting a max of 0, and comparing each element to that max, and changing the max when one element is greater. This is the pseudocode for the mentioned concept:
maximum(nums, size)
Int max = 0
	For (i = 0; i<size; i++)
		If nums[i] > max
			Max = nums[i]
	Return max

summing all of the positive elements of an array

We can do this with another for loop but with an if statement that checks for negative integers. We will initialize the sum to 0, and add numbers with the for loop and return when the last term is added.

sum_positive(nums, size)
	Int sum = 0
	For (i=0; i<size; i++)
		If nums[i]>-1
			Sum += nums[i]
	Return sum

Reduce

Reduce is similar to map in that it takes a function and a value and “reduces” the array to a value. We use pointers to the array and the functions so that their actual value does not change. The pseudocode looks something like this.

int reduce(int *nums, int len, int (*f)(int,int), int initial)
	Count = len
	Int *updated=nums 
	If count = 0
		Return initial
	Else
		Initial = *f(first element of updated,initial)
		Updated++
		count = count-1
		Return reduce(*updated, count, (*f), initial)


finding the maximum element of an array with reduce

The helper function will compare 2 ints and return the greater one. In this case, we should be comparing the next integer in the pointer array to the maximum that we have. Y will be set to initial and X will be the testing integer.

compare(x,y)
	If (x>y)
		Return x
	Else
		Return y

Since we already have the reduce code, we can just run that code with the maximum function.

maximum_with_reduce(nums, size)
	Return reduce(*nums, size, *compare, 0)

We use a pointer to the array nums, the size of the array, the helper function compare, and 0 to initialize the maximum to 0.

summing all of the positive elements of an array with reduce

The helper function will add two positive ints. The y value will be set to initial in the reduce function, so we will be adding x to y.

add(x,y)
	if (x>-1)
		Return y+x
	else 
		Return y

sum_positive_with_reduce(nums, size);
	Return reduce(*nums, size, *add, 0)

We use a pointer to the array nums, the size of the array, our helper function add, and 0 to initialize the maximum to 0.

counting the negative numbers in an array with reduce

We could use a helper function to verify if a number is negative or not. This function could be called is_negative(int):

#this function will test if x is less than 0. If it is, y, which should be set to initial in the reduce function will increment, giving us a count. Otherwise, it will return the count without incrementing.
is_negative(x,y):
	If x<0
		y++
		Return y
	Else
		Return y
count_negative_with_reduce(nums, size);
	Return reduce(*nums, size, *is_negative(num,size),0)
#the count negative reduce function just runs the reduce function with helper function “is_negative”


