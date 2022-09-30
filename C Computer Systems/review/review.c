#include "review.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions for you to implement. Most of the work for this homework will be
// done in here, but you'll also need to make changes to review.h and yelling.c.

// Problem 1
void sum_and_difference(int a, int b, int *sum, int *difference) {
 *sum = a+b;
 *difference = a-b;
}

// Problem 2

// This one ought to be recursive.
size_t ll_length(LLint *node) {
  size_t count = 0;
  if(node==NULL)
	  return 0;
  else
	  return 1+ll_length(node->next);
}

// Do this one iteratively.
size_t ll_length_iterative(LLint *node) {
  size_t count = 0;
  struct LLint *head = node;
  while(head!=NULL){
          head=head->next;
          count++;
  }
  return count;
}

// Problem 3.

LLdouble *createdouble(double d){
	LLdouble *head = malloc(sizeof(LLdouble));
	head->val = d;
	head->next = NULL;
	return head;
}
void push(LLdouble **list, double val){
	LLdouble *head = createdouble(val);
	head->next = *list;
	*list = head;
}
double pop(LLdouble **head){
	if(*head==NULL)
		return 0;
	LLdouble *temp = *head;
	double out = temp->val;
	*head = (*head)->next;
	free(temp);
	return out;
}
void reverse_doubles_with_stack(double *array, size_t array_len) {
  LLdouble *stack = NULL;
  double out[array_len-1];
  for(size_t i =0;i<array_len;i++){
	  push(&stack,array[i]);
  }
  for(size_t i=0;i<array_len;i++){
	  double x = pop(&stack);
	  out[i]=x;
  }
  array = out;
}

// Problem 4.
tnode *word_observe(char *word, tnode *node) {
  // This function returns a pointer to a tnode because you may have to allocate
  // a new one. You might take a NULL pointer to start with.
  // Also, this means that you can very cleanly do this with recursion.
  if(node== NULL){
	  tnode *newll = malloc(sizeof(tnode));
	  newll->left = newll->right = NULL;
	  newll->count = 1;
	  newll->word = word;
	  return newll;
  }
  if(strcmp(word,node->word)<0&&node->left==NULL){
	  tnode *newll = malloc(sizeof(tnode));
          newll->left = NULL;
	  newll->right = node;
	  node->left = newll;
          newll->count = 1;
          newll->word = word;
          return newll;
  }
  else if(strcmp(word,node->word)>0&&node->right==NULL){
	  tnode *newll = malloc(sizeof(tnode));
          newll->left = node;
          newll->right = NULL;
          node->right = newll;
          newll->count = 1;
          newll->word = word;
          while(node->left!=NULL)
		  node = node->left;
	  return node;
  }
  else if(strcmp(word,node->word)>0 && strcmp(word,node->right->word)<0){
	  tnode *newll = malloc(sizeof(tnode));
	  newll->count = 1;
	  newll->word = word;
	  newll->left = node;
	  newll->right = node->right;
	  node->right->left = newll;
	  node->right = newll;
	  while(node->left!=NULL)
		  node = node->left;
	  return node;
  }
  else if(strcmp(word,node->word)==0){
	  node->count++;
	  while(node->left!=NULL)
		  node = node->left;
	  return node;
  }
  else
	  word_observe(word,node->right);
  return NULL;
}

int word_count(char *word, tnode *node) {
  while(node!=NULL){
	  if(strcmp(node->word,word)==0)
		  return node->count;
	  else
		  node = node->right;
  }
  puts("Word not found");
  return 0;
}
void delete_tree(tnode *node) {
  while(node!=NULL){
	  tnode *ptr;
	  ptr = node;
	  node = node->right;
	  free(ptr);
  }
}
