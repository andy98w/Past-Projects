/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#4 
* ListTest.c
* Test File for List ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   List A = newList();
   List B = newList();
   double D[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
   double E[]={0,5,10,15,20,2,4,6,8,10,12,14,16};
   for(int i=1; i<=13; i++){
      prepend(A, &E[13-i-1]);
      append(B, &D[i]);
   }
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%0.1f ", *(double*)get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%0.1f ", *(double*)get(B));
   }
   printf("\n");
   printf("\nLength A: %d", length(A));
   printf("\nLength B: %d", length(B));
   printf("\nFront A: %0.1f",*(double*)front(A));
   printf("\nBack B: %0.1f\n", *(double*)back(B));
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%0.1f ", *(double*)get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%0.1f ", *(double*)get(B));
   }
   printf("\n");
puts("---------------------");
   moveFront(A);
   printf("%d\n",index(A));
   for(int i=0; i<8; i++) moveNext(A); 
   printf("%d\n",index(A));
   set(A,&D[10]);
   insertBefore(A,&E[3]);
   for(int i=0; i<3; i++) moveNext(A);
  printf("%d\n", index(A));
   insertAfter(A, &E[5]);
   for(int i=0; i<5; i++) movePrev(A);
  printf("%d\n", index(A)); 
   delete(A);
   moveBack(A);
   set(A,&D[15]);
   deleteFront(A);
   deleteBack(A);
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%0.1f ", *(double*)get(A));
   }
   printf("\n");
   printf("Length A: %d\n", length(A));
   clear(A);
   printf("Length A: %d\n", length(A));
   freeList(&A);
   freeList(&B);
   return 0;
}

