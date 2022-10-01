/****************************************************************************************
*  ListClient.c
*  Test client for List ADT
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   List A = newList();
   List B = newList();
   List C = NULL;
   for(int i=1; i<=21; i=i+3){
      append(A,i);
   }
   for(int j = 2; j<=20;j=j+2){
	   prepend(B,i);
   }
   printList(stdout,A);
   printf("\n");
   printList(stdout,B);
   printf("\n");
   printf("\nLength A: ", length(A));
   printf("\nLength B: ", length(B));
   printf("\nFront A: ", front(A));
   printf("\nBack B: ", back(B));
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
   }
   printf("\n");

   C = copyList(B);
   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(B,C)?"true":"false");
   printf("%s\n", equals(C,A)?"true":"false");
puts("---------------------");
   moveFront(A);
   printf("%d\n",index(A));
   for(i=0; i<8; i++) moveNext(A); // at index 8
   printf("%d\n",index(A));
   set(A,-1);
   insertBefore(A, -2);            // at index 6
   for(i=0; i<9; i++) moveNext(A); // at index 15
   insertAfter(A, -3);
   for(i=0; i<5; i++) movePrev(A); // at index 10
   delete(A);
   moveBack(A);
   set(A,-4);
   printList(stdout,A);
   deleteFront(A);
   deleteBack(A);
   printList(stdout,A);
   printf("\n");
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));
   freeList(&A);
   freeList(&B);
   freeList(&C);
   return 0;
}
