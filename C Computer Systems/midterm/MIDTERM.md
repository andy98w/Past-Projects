# CSE 13s, Winter 2022 -- Midterm Exam

  * name: Your Name Goes Here
  * email: sammyslug@ucsc.edu  (put yours here)

*I understand that getting help from a classmate or an external source would
be a violation of academic integrity. So I did all of this work myself.*
signed: YOUR NAME HERE


**HOWTO do this midterm** -- this is a take-home exam, to be done by just you,
with your notes, with the reading materials, and with your ability to read man
pages and search the web. Do not consult with other students, and do not ask
people other than the course staff for help!

The midterm is due in 24 hours (+ accommodations), and turned in the same way
that we turn in homeworks. You must check in your materials into your
course git repository *and* upload the relevant commit ID on Canvas by then.
For most students, this is due at *1:20pm on Thursday 10 February 2022*. 

So make sure you check in *at least* these files into a directory called
`midterm` in your git repository:
  * your completed `MIDTERM.md` (ie, this file, filled out)
  * your completed `midterm.c`
  * your `Makefile` for compiling the code -- make sure to turn on the strict
    compiler flags before turning in.

For short answer questions, write your response in this file. For the
programming problems, write a short explanation of what your code does (and *why
it does it!*) in this file, and complete the program in `midterm.c`.

## problem 1

Write a function that returns the first *n* Fibonacci numbers, in a dynamically
allocated array of type `long long`. Recall that the sequence goes 1, 1, 2, 3,
5, 8...

Should this be done iteratively or recursively?

This should be done iteratively because we're taking user input for the n number of terms we are computing 
for the Fibonacci sequence. Furthermore, we would have to dynamically allocate memory so to call the function
again recursively would be to keep allocating memory which we don't need. We are going to use a for loop to 
run through the pointer of long long ret and compute the next term based on term ret + i-1 and ret + i-2.
pseudocode:
long long* ret
dynamically allocate array of length n*size of long long
*ret = 0
*ret+1 = 1
if n smaller than 2
  return ret
for loop with i as count
  *ret + i = (ret + i-1) + (ret + i-2)
return ret

## problem 2

[Bubble sort](https://en.wikipedia.org/wiki/Bubble_sort) is a simple (but
relatively inefficient) sorting algorithm that works by comparing elements in an
array and swapping them if they are in the incorrect order.

The pseudocode looks like:

* keep doing this...
  * for every element x of my input array
    * for every *other* element y of my input array
      * if x should go before y but does not, swap x and y's position in the
        array
* stop if I did not perform any swaps

Imagine that we are working at an online shoe retailer, and we want to sort our
customers by their shoe size.

Implement a function for bubble sorting procedure that sorts customers by shoe
size, ascending. Smallest shoe sizes should go first, larger shoe sizes later.

We are going to be changing the pointer to customers given to us in the function
header. N_customers will be the size of the array and a counter for how many
iterations we are going to have to run the 2 for loops implemented. If we check
the shoesize of a customer and it's larger than the one next to it, we swap them.
pseudocode
Declare temporary shoecustomer temporary variable
for i loop smaller than shoecustomers length
  for j loop smaller than shoecustomers length
    if customers[j] larger than customers[j+1]
      temporary = customers[j]
      customers[j] = customers[j+1]
      customers[j+1] = temporary

## problem 3

Recall in homework 2, we wrote a function `reduce`, which took a collection of
numbers and reduced it down to a single number, essentially a summary of that
collection.

Here we will write a version of the companion function to *reduce*, which is
called [*map*](https://en.wikipedia.org/wiki/Map_(higher-order_function)). Map
takes a function and applies that function to each element in the collection,
and returns a collection of the same shape.

In this version, we will take in a linked list of floating point numbers (see
`LLfloat` in the code) and return a *new* linked list of floating point numbers,
of the same length, where each element of the new list is the result of calling
the specified function on the corresponding number in the input list.

For example, if your input list consisted of:
`[0, 1, 2, 3]`

And your specified function computed the square of the input number, then your
function would return a new linked list (you'll have to allocate it with
`malloc` or `calloc` !) containing:
`[0, 1, 4, 9]`

In map, we take a function f and a linked list of LLfloat structs that contain 
value of float numbers. I was thinking we could use an iterative function to 
add float numbers to a seperate linked list declared in the function. Memory 
will be allocated based on each while loop run while checking if the numbers list
is null. We will also declare a head node and return that at the end. We will use
3 different variables, and stop when the while loop stops. 
pseudocode:
LLflot head = malloc size of LLfloat
LLfloat curr
head = first value of numbers
curr = head
numbers next
while numbers is not null:
  llfloat new = malloc
  new value = function(numbers)
  curr next = new
  curr = curr next
  numbers = numbers next
return head
## problem 4

Imagine that we are building a calendar system, and we want to find out when a
group of different users are available for a meeting. Here we will represent a
user's availability with a bit vector in the form of an `unsigned long` -- we
get 64 different appointment slots during a week, and a user can be either
*available* (the bit is set to 1) or *unavailable* (the bit is set to 0) for
that appointment slot.

Write a function that takes an array (ie, a pointer to an array) of these
bit-vector calendars, a number of users (ie, the size of the array) and returns
a single `unsigned long` where each bit in the unsigned long is set to 1 if *all
users* are available at that time.

For this problem we are trying to find an unsigned long value. Using an array of
unsigned long numbers, we can convert this to a long boolean bit vector, that
displays 'True' for 1, and 'False' for 0. If every value in the array has a '1'
for a certain digit, our output 'result' unsigned long value will have a '1' in
that digit (in binary form). We can do this by calculating modulus and subtracting
based on if a number previously had a 1 in that slot (in decimal form)
pseudocode:
for x = 0, x smaller than 64, increment by 1
  long availability
  unsigned long calc to store power (2 to x)
  count = 0
  for y=0, y smaller than length of users, increment by 1
    z = calendars[y] mod calc
    calendars y = calendars y - decimal form of binary rep
    if mod = 1
      calendars y = calendars y - decimal form of binary rep
      count++
    if count equal num users
      availability+=calc-decimal form of binary rep
  return availability

## problem 5 (short answer)

Consider the following code snippet:

```
float f[10];
float *p;
p = f;
p++;
```

Say that you found out that the array `f` was at memory address `0xC0FF33`. In
your own words, what did we do on the line `p++`, and what is the value of `p`
after this code runs? What is the value of `p + 5`? (give these as hexidecimal
numbers)

The line p++ incremented p by one. This does not change the memory address. This is 
because variables in the same scope have the same memory address. P+5, incrementing
P by 5 will also not change the memory address of the pointer. 

## problem 6 (short answer)
In math, how many real numbers are there? Comparatively, in a computer, how many
floating point numbers (C type `float`) are there? How could you find out how
many floating point numbers there are, for sure?

In math, there are infinitely many real numbers. In a computer, there are roughly
4 billion, which is 2^32 different numbers. You calculate this by taking each bit
which represents 0 or 1, and multiplying the number of possible outcomes you can make.
Since floating numbers have 32 bits, there are 2^32 possible outcomes.
