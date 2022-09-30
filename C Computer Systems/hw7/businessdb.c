#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20000
#include "businessdb.h"

char *printstr(Customer *c, char*out) { //doesn't actually print string
  char string[20]; //this is to store shoesize later as a string
  strncat(out, c->email, strlen(c->email));
  strncat(out, "\t", 1);
  strncat(out, c->name, strlen(c->name));
  strncat(out, "\t", 1);
  sprintf(string, "%d", c->shoesize);
  strncat(out, string, strlen(string)); //put everything in string format for save later
  strncat(out, "\t", 1);
  strncat(out, c->food, strlen(c->food));
  strncat(out, "\0", 1);
  return out;
}
unsigned long hash(char *email) { //hash function that will return index of an email input
  unsigned long val = 0;
  for (int i = 0; email[i]; i++)
    val += email[i];
  return val % MAX;
}
ll *ll_allocate() { //allocates memory to an array
  ll *newlist = malloc(sizeof(ll));
  return newlist;
}
void ll_free(ll* l) { //frees list for later
  ll *head = l;
  while (l!=NULL) {
    head = l;
    l = l->next;
    free(head->customer->email); //free everything
    free(head->customer->name);
    free(head->customer->food);
    free(head->customer);
    free(head);
  }
}
ll **create_buckets(HashTable *table) { //create buckets for hash table
  ll **buckets = (ll **)calloc(table->size, sizeof(ll *)); //allocate memory
  for (int i = 0; i < table->size; i++)
    buckets[i] = NULL; //set all blocks to null
  return buckets;
}
void free_buckets(HashTable *table) {
  ll **buckets = table->buckets; //frees bucket list for later
  for (int i = 0; i < table->size; i++)
    ll_free(buckets[i]);
  free(buckets);
}
Customer *new_customer(char *email, char *name, int shoesize, char *food) {
  Customer *newcustomer = (Customer *)malloc(sizeof(Customer));
  newcustomer->email = (char *)malloc(strlen(email) + 1);
  newcustomer->name = (char *)malloc(strlen(name) + 1); //creates a customer object/struct
  newcustomer->food = (char *)malloc(strlen(food) + 1);
  strcpy(newcustomer->email, email);
  strcpy(newcustomer->name, name); //stores all values inside that object
  newcustomer->shoesize = shoesize;
  strcpy(newcustomer->food, food);
  return newcustomer;
}
HashTable *create(int size) {
  HashTable *table = (HashTable *)malloc(sizeof(HashTable));
  table->size = size; //creates a hash table with the max size of 50k
  table->customers = (Customer **)calloc(table->size, sizeof(Customer *));
  for (int i = 0; i < table->size; i++)
    table->customers[i] = NULL; //sets all values in the pointer to linked lists to null
  table->buckets = create_buckets(table); //creates linked list buckets
  return table;
}
void free_customer(Customer *customer) {
  free(customer->email);
  free(customer->name); 
  free(customer->food); //frees everything in customer
  free(customer);
}
void free_table(HashTable *hashtable) { //frees everything in table
  for (int i = 0; i < hashtable->size; i++) {
    Customer *customer = hashtable->customers[i];
    if (hashtable->customers[i] != NULL)
      free_customer(customer);
  }
  free_buckets(hashtable);
  free(hashtable->customers);
  free(hashtable);
}
Customer *lookup(HashTable *table, char *email) {
  int index = hash(email); //lookup given email from our hash table using hash function
  Customer *customer = table->customers[index];
  ll *head = table->buckets[index]; //sets temporary head to linked list index
  while (customer != NULL) { //if its not null, we will compare the emails
    if (strcmp(customer->email, email) == 0)
      return customer; //return if the same
    if (head == NULL)
      return NULL; //if head gets to end (null) and hasn't found one, we will return null
    customer = head->customer;
    head = head->next; //go to next linked list
  }
  return NULL; 
}
void addt(HashTable *table, char *email, char *name, int shoesize, char *food) {
  unsigned long index = hash(email); //take index from hash function in our parameter
  Customer *current_customer = table->customers[index];
  Customer *customer = new_customer(email, name, shoesize, food);
  if (current_customer == NULL) { //if it doesn't exist, make a new customer at the index
    table->customers[index] = customer;
    return;
  } else { //if it does exist we will update the info on the email
      strcpy(table->customers[index]->food, food);
      table->customers[index]->shoesize = shoesize;
      strcpy(table->customers[index]->name, name);
      return;
  }
}
void delete (HashTable *table, char *email) { //deletes object from hashtable
  int index = hash(email);
  Customer *customer = table->customers[index]; //takes index of email once again
  ll *head = table->buckets[index];
  if(strcmp(customer->email, email) == 0) { //remove buckets from linked list
      table->customers[index] = NULL;
      free_customer(customer); //set value of index to null
      return;
    }
  ll *previous = NULL;
  ll *current = head;
  while (current!=NULL) {
    if (strcmp(current->customer->email, email) == 0) {
      if(previous==NULL){
	table->buckets[index] = NULL;
        ll_free(head); //iterates until current reaches the end, reconnects linked list
        return;
      }else{
	table->buckets[index] = head;
        previous->next = current->next; //depending on what we deleted
        current->next = NULL;
        ll_free(current); //free memory for deletion
        return;
      }
    }
    current = current->next;
    previous = current;
  }
}
void print_table(HashTable *table) { //prints table 
  for (int i = 0; i < table->size; i++) {
    if (table->customers[i]) {
      Customer *print = table->customers[i];
      printf("email: %s", print->email);
      printf("\n"); //only if table->customers has info
      printf("name: %s", print->name);
      printf("\n");
      printf("shoe size: %d", print->shoesize);
      printf("\n");
      printf("favorite food: %s", print->food);
      printf("\n");
    }
  }
}
int main(int argc, char **argv) {
  char *ptr = NULL;
  char buf[50];
  FILE *infile = fopen("customers.tsv", "r"); //reads file
  HashTable *Customers = create(MAX);
  while (fgets(buf, 50, infile) != NULL) {
    int i = 0;
    char *email = NULL;
    char *name = NULL; //declares null pointers
    char *food = NULL;
    int shoesize = 0;
    ptr = strtok(buf, "\t"); //\t is tab seperated
    email = ptr;
    while (NULL != (ptr = strtok(NULL, "\t"))) {
      i++;
      if (i == 1) //gets information based on what tab seperated entry its reading
        name = ptr;
      else if (i == 2)
        shoesize = atoi(ptr);
      else if (i == 3)
        food = ptr;
    }
    addt(Customers, email, name, shoesize, food); //add to hash table
  }
  fclose(infile);
  while (1) {	  
    char str[20]; //user input for commands
    printf("Enter command: ");
    scanf("%s", str);
    if (strcmp(str, "quit") == 0) //quit
      break;
    else if (strcmp(str, "save") == 0) { //save
      FILE *out = fopen("customers.tsv", "w");
      for (int i = 0; i < Customers->size; i++) {
        if (Customers->customers[i]!=NULL) {
	  char *print = calloc(50, sizeof(char));
	  print = printstr(Customers->customers[i], print);
	  fputs(print,out);
	  char *ptr = print;
	  free(ptr);
	 }
      }
      fclose(out);
    } else if (strcmp(str, "add") == 0) { //add asks for user input
      char email[20];
      char name[20];
      int shoesize;
      char food[20];
      printf("email address? ");
      scanf("%s", email);
      printf("name? ");
      scanf("%s", name);
      printf("shoe size? ");
      scanf("%d", &shoesize);
      printf("favorite food? ");
      scanf("%s", food);
      strncat(food,"\n",1);
      printf("");
      addt(Customers, email, name, shoesize, food);
    } else if (strcmp(str, "lookup") == 0) { //lookup
      char email[20];
      printf("email address? ");
      scanf("%s", email);
      Customer *ptr = lookup(Customers, email);
      if (ptr != NULL) {
	printf("\n");
        printf("email: %s", ptr->email);
        printf("\n");
        printf("name: %s", ptr->name); //prints lookup
        printf("\n");
        printf("shoe size: %d", ptr->shoesize);
        printf("\n");
        printf("favorite food: %s", ptr->food);
        printf("\n");
      } else
        puts("user not found!");
    } else if (strcmp(str, "delete") == 0) { //delete
      char email[20];
      printf("email address? ");
      scanf("%s", email);
      Customer *ptr = lookup(Customers, email);
      if (ptr == NULL){
        puts("user not found!");
      }else
	delete (Customers, email);
    } else if (strcmp(str, "list") == 0) {
      printf("\n"); //prints table
      print_table(Customers);
    } else
      puts("unknown command"); //unknown
  }
  free_table(Customers);
  return 0;
}
