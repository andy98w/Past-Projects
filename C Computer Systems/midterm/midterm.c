#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include<math.h>

// PROBLEM 1

long long *fibonacci_numbers(int n) {
  // You're going to have to allocate an array, fill it in, and return it.
  // The array should be of length n.
  // Recall the first few entries should be 1, 1, 2, 3, 5, 8, ...
  long long *ret;
  ret = (long long*)malloc(n * sizeof(long long));
  *ret=0;
  *(ret+1)=1;
  if (n < 2) {
      return ret;
  }
  for (int i = 2; i < n; ++i) {
    *(ret +i) = *(ret + (i-1)) + *(ret + (i-2));
  }
  return ret;
}


// PROBLEM 2

typedef struct {
  int shoe_size;
  int customer_id;
  int num_purchases;
} ShoeCustomer;

void bubble_sort_customers(ShoeCustomer* customers, int n_customers) {
  // Your code here! Make them sorted!
    ShoeCustomer temp;
    for (int i = 0; i < n_customers-1; i++){
        for (int j = 0; j < (n_customers-i-1); j++){
            if (customers[j].shoe_size > customers[j + 1].shoe_size){
                temp = customers[j];
                customers[j] = customers[j + 1];
                customers[j + 1] = temp;
            } 
        }
    }
}

// PROBLEM 3

// A linked list of floating point numbers.
typedef struct LLfloat {
  float val;
  struct LLfloat *next;
} LLfloat;

LLfloat *map_floats(float (*f)(float), LLfloat *numbers)  {
  // finish this function.
  // Should it be recursive? It's up to you, but it could be recursive!
  LLfloat *head=(LLfloat*)malloc(sizeof(LLfloat));
  LLfloat *curr;
  head->val = f(numbers->val);
  curr = head;
  numbers = numbers->next;
  while(numbers != NULL) {
      LLfloat *new=(LLfloat*)malloc(sizeof(LLfloat));
      new->val=f(numbers->val);
      curr -> next = new;
      curr = curr->next;
      numbers = numbers->next;
   }
   return head;
}

// PROBLEM 4

unsigned long compute_availability(unsigned long *calendars, int num_users) {
    unsigned long availability = 0;
    for (int x=1; x <= 64; ++x){
        unsigned long calc = pow(2,x);
        int count = 0;
        for (int y=0; y<num_users; ++y){
            int mod = calendars[y]%calc;
            calendars[y]=calendars[y]-pow(2,x-1);
            if(mod==1){
                calendars[y]=calendars[y]-pow(2,x-1);
                count++;
            }
        }
        if(count == num_users){
            availability+=calc-pow(2,x-1);
        }
    }
  return availability;
}
// put examples for testing your functions in the main! You're going to have to
// figure out how to test these.
int main(void) {
  return 0;
}

