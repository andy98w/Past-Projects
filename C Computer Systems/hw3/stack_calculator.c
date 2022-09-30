#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack_calculator.h"

// Allocate a new Stack struct and return a pointer to it.
Stack *stack_create(void) {
  // this one is complete, no need to change it!
  Stack *out;
  out = (Stack *)calloc(1, sizeof(Stack));
  return out;
}

// Add a new node at the front of the stack. Return false if we are unable to do
// so (eg, if memory allocation fails).
bool stack_push(Stack *s, CalculatorItem item) {
    Node *newtop = (Node *)calloc(1, sizeof(Node));
    if (newtop==NULL){
        return false;
    }
    newtop->item = item;
    newtop->next = s->top;
    
    s->top = newtop;
    return true;
}

// Pop the stack and put the result into the output pointer.
// return false if the stack is NULL or if it is empty.
bool stack_pop(Stack *s, CalculatorItem *output) {
    if (s == NULL || s->top == NULL){
        return false;
    }
    CalculatorItem result = s->top->item;
    *output = result;
    Node *delete_this = s->top;
    free(delete_this);
    s->top = s->top->next;
    return true;
}

// Returns true if the specified stack is empty.
bool stack_empty(Stack *s) {
	if (s->top == NULL){
		return true;
	}
	else {
		return false;
	}
}

// Free all of the memory used by this stack, including its linked list.
// When you are done, set the pointer to NULL.
void stack_delete(Stack **s) {
	CalculatorItem delete;
	while(!stack_empty(*s)){
		stack_pop(*s, &delete);
	}
	*s = NULL;
}

// Returns true if we were able to successfully perform the computation step,
// and false if there was an error of some kind.
bool stack_compute_step(Stack *s, CalculatorItem item) {
	if(item.type==NUMBER){
		stack_push(s, item);
		return true;
	}
	CalculatorItem x;
	CalculatorItem y;
	CalculatorItem z;
	if(!stack_empty(s))
		stack_pop(s, &x);
	else
		return false;
	if(!stack_empty(s)) 
		stack_pop(s, &y);
	else
		return false;
	if(item.type==ADD) {
		z.value = x.value+y.value;
		stack_push(s,z);
	}
	if(item.type==SUBTRACT) {
		z.value = x.value-y.value;
		stack_push(s,z);
	}
	if(item.type==DIVIDE) {
		z.value = y.value/x.value;
		stack_push(s,z);
	}
	if(item.type==MULTIPLY) {
		z.value = x.value*y.value;
		stack_push(s,z);
	}
  return true;
}
