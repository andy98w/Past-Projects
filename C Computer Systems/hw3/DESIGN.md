Andrew Wu
CSE13s

This is the Design document for homework 3 of CSE13s. In this homework, we will be about data structures, linked lists, and stacks. We will be implementing a stack-based calculator that takes inputs from a text file and does arithmetic functions. 

The main function in the “hw3.c” file will read the input text and either determine if the line is a number or an arithmetic function. Numbers will go onto the calculation stack and arithmetic functions will pop two values in the calculation stack and compute them. We push this resulting value onto the stack. 


PSEUDOCODE FOR STACK CALCULATOR

Stack *stack_create(void) { // this one is complete, no need to change it!
  Stack *out;
  out = (Stack *)calloc(1, sizeof(Stack));
  return out;
}


For Stack Push, we will just be adding a number to the stack S. First, we must use calloc to allocate memory for the stack of 1, and use the size of the stack to determine the address of the new node. 

// Add a new node at the front of the stack. Return false if we are unable to do
// so (eg, if memory allocation fails).
bool stack_push(Stack *s, CalculatorItem item) {
	Node *newtop = (node *)calloc(1, sizeof(node))
	If newtop = null: 
		Return false
	Set newtop = item
	Set newtop next to top of stack
	Set stack top to new top
	
  return true;
}

For Stack Pop, we need to run an if statement to check if the stack is null because if it is, we return false. We need to set the output to the top of the stack, and then set a pointer to the top of the stack and delete it. We then set the top of the stack to the next value.

// Pop the stack and put the result into the output pointer.
// return false if the stack is NULL or if it is empty.
bool stack_pop(Stack *s, CalculatorItem *output) {
 	If  s = null
		Return false
	Calculatoritem output result = top of stack
	Output = result
	Node delete_this = top
	free(delete_this)
	Top of stack = next top of stack
  return true;
}

This will be simple. All we need to do is check if the top of the stack is NULL, that means it’s an empty stack. 

// Returns true if the specified stack is empty.
bool stack_empty(Stack *s) {
  	If s->top = null
		Return true
	Else
		Return false
}

For delete, we could just pop all values of the stack. 

// Free all of the memory used by this stack, including its linked list.
// When you are done, set the pointer to NULL.
void stack_delete(Stack **s) {
  	For loop to pop all values
	Set pointer to null
}

Stack compute step takes the “item” inputted which is an operator, and pops two values of the stack and performs the operation on them. If we check for a number though, we should pop the number onto the stack.

// Returns true if we were able to successfully perform the computation step,
// and false if there was an error of some kind.
bool stack_compute_step(Stack *s, CalculatorItem item) {
	If item type = number
		Push item onto stack
	Calculatoritem x
	Calculatoritem y
	Calculatoritem z
	if (stack not empty)
		Stack pop at x
	Else 
		Return false
	if (stack not empty)
		Stack pop at y
	else	
		Return false
	If item type = add
		Z value = x value + y value
	If item type = subtract
		Z value = x value - y value
	If item type = multiply
		Z value = x value * y value
	If item type = divide
		Z value = x value/yvalue
	Push z onto stack
  return true;
}



