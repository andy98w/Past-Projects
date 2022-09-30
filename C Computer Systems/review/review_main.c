#include "review.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int sum = 0;
	int difference = 0;
	sum_and_difference(50,40,&sum,&difference);
	printf("%d\n",sum);
	printf("%d\n",difference);
	double array[12] = {1,2,3,5,6,3,123,4325,56,32,12,3};
	reverse_doubles_with_stack(array,12);
	for(int i=0;i<12;i++)
		printf("%f ",array[i]);
	return 0;
}
