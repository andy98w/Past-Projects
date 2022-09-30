#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct Customer Customer;
struct Customer {
  char *email;
  char *name;
  int shoesize;
  char *food;
};
typedef struct ll ll;
struct ll {
  Customer *customer;
  ll *next;
};
typedef struct HashTable HashTable;
struct HashTable {
  Customer **customers;
  ll **buckets;
  int size;
};
char *printstr(Customer *c, char *out);

unsigned long hash(char *c);

ll *ll_allocate();

ll *ll_add(ll *list, Customer *customer);

void ll_free(ll *list);

static ll **create_buckets(HashTable *table);

static void free_buckets(HashTable *table);

Customer *new_customer(char *email, char *name, int shoesize, char *food);

HashTable *create(int size);

void free_customer(Customer *customer);

void free_table(HashTable *table);

void replace(HashTable *table, unsigned long index, Customer *customer);

void addt(HashTable *table, char *email, char *name, int shoesize, char *food);

Customer *lookup(HashTable *table, char *email);

void delete (HashTable *table, char *email);

void print_table(HashTable *table);
