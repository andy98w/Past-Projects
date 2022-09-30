#include <stdio.h>
#include <stdlib.h>
#include "num_arrays.h"
int maximum(int *nums, int len) {
    int max = 0;
    for (int i = 0; i<len; i++){
		if (nums[i] > max)
			max = nums[i];
    }
	return max;
}

int sum_positive(int *nums, int len) {
	int sum = 0;
	for (int i=0; i<len; i++){
		if(nums[i]>-1)
			sum += nums[i];
	}
	return sum;

}
int reduce(int *nums, int len, int (*f)(int,int), int initial){
    int count = len;
    int *updated=nums;
	if(count == 0){
		return initial;
	}
	else {
		initial = (*f)(updated[0],initial);
		updated++;
		count = count-1;
		return reduce(updated, count,(*f), initial);
	}
}
  
int compare(int x, int y){
	if (y>x)
		return y;
	else
		return x;
}

int maximum_with_reduce(int *nums, int size){	return reduce(nums, size, (*compare), 0);
}

int add(int x, int y){
    if (x>-1)
		return y+x;
	else 
		return y;
}

int sum_positive_with_reduce(int *nums, int size){
	return reduce(nums, size,(*add), 0);
}

int is_negative(int x,int y){
	if(x<0){
	    y++;
		return y;
	}
	else{
	    return y;
	}
}
int count_negative_with_reduce(int *nums,int size){
	return reduce(nums, size, (*is_negative),0);
}



