#include "final.h"

#include <stdio.h>

void find_two_biggest(LLint *linkedlist, int *biggest, int *nextbiggest) {
  int a = linkedlist->val;
  int b = linkedlist->next->val;
  linkedlist = linkedlist->next;
  linkedlist = linkedlist->next;
  while(linkedlist!=NULL){
	  if(b>a){
		  int tmp = a;
		  a = b;
		  b = tmp;
	  }
	  if(linkedlist->val>a){
		  b = a;
		  a = linkedlist->val;
	  }
	  else if(linkedlist->val>b&&linkedlist->val<=a){
		  b = linkedlist->val;
	  }
	  linkedlist = linkedlist->next;
  }
	  *biggest = a;
	  *nextbiggest = b;
}
