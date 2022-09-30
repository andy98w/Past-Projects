Andrew Wu
Alex Rudnick
CSE 13s
HW7 DESIGN

In this lab, we are going to be programming from scratch a program that takes in a customers.tsv file and reading it. This code will then make a hash table for the tab separated values in the customers file, with customer nodes containing an email, a name, a shoesize, and a favorite food. We will store these values in a hashtable of a linked list of customer structs. First, we will have to declare the customer, linked list, and hashtable structs in the header file, along with all of the functions we are going to use. 

It is also important to declare our capacity for hashtable, which will be 50,000.
#DEFINE MAX = 50000

typedef struct {
        char *email;
        char *name;
        int shoesize;
        char *food;
} Customer;
typedef struct ll {
        Customer *customer;
        struct ll *next;
} ll;
typedef struct Hashtable {
        Customer **customers;
        ll **buckets;
        int size;
        Int count;
} Hashtable;

After this, we can begin programming our code. First we can declare some helper functions to print our strings. We will have this output a character just to make it easy to save to our file later on. For this purpose, we will need to tab separate each of the entries and also take in a customer struct.

Char* printstr(customer*c)
	Out = malloc
	Declare empty string for shoesize
	Add c->email,name,shoesize,food to out
	Tab separate each
	Return out
}

We will then need to implement our list functions for our linked list struct. We can use a create list, a free list, and add to list. 

Create list will create a list for the hashtable. It will only be done once. This is to connect all the customer structures later on.

ll** allocate(Hashtable *table){
	Linkedlist** buckets = allocate memory
	Return buckets;

Free_linkedlist will only be done once as well near the end of our program. Thiss will free the memory associated with each customer struct in the list as well as the list itself.
void free_linkedlist(Linkedlist* list){
	Linkedlist*temp = list
	While list is not null
		Temp = list
		List = list next
		Free everything
		Free temp

For more list functions, we should create the hashtable buckets and free hashtable buckets for later. These two functions will do just that. The free buckets function will utilize our linked list free function from earlier.

ll*createbuckets(Hashtable t)
	Ll ** buckets = calloc
	For i =0, i<table->size;i++
		Buckets[i] = null
	Return buckets
ll*freebuckets(Hashtable t)
	Ll buckets = t->buckets
	For i=0;i<table->size;i++
		ll_free(buckets[i])
	free(buckets)

Next we will make a create_table and create_customer functions to create our hash table. This will simply allocate memory to a hash table and set its size and array.

Hashtable *create_table()
	Hashtable allocate memory
	Hashtable size = 0
	Hashtable->customers allocate memory
	Hashtable[0] = NULL
	Hashtable list = create list
	Return table

We should also create a customer function that takes all four of the customer values (email, name, shoesize, and food) and make a customer struct out of those.

Customer *create_customer(char *email, char*name,int shoesize,char*food)
	Malloc memory to customer->email,name,shoesize,food
	strcpy email,name,shoesize,food into customer->email,customer->name, etc.
	Return customer;

Next, our hash function will be important in determining where the hash is stored (identifying by an email to our customer struct). We can do this through an algorithm that computes a value based on where it’s stored in memory through pointers. 

Unsigned hash(char *c)
	Unsigned val = 0
	for(int j =0, c[j], j++
		val+=c[j];
	Return val

The free functions will help us free dynamically allocated memory at the end. Free_customer will be called by free_table multiple times as it frees all memory in the hashtable.

Void freecustomer(customer c)
	Free c->email, name, etc.
	Free c
Void freetable(table)
	For i<table size
	Customer c = table->customers[i]
	If c is not null
		Free
	Free buckets
	Free table->customers
	Free table

Here will be the main part of our program, which includes lookup, add_customer, and delete_customer functions. We should also include replace to be called by add_customer just in case there are two overlapping values.

This will be our main function in a separate .c file which is the executable for our code, businessdb.c.

Lookup will take our hashtable and an email identifier and return a Customer struct. We will use our hash identifier function to find the index of our Customer struct. We will continuously check if head is null so that we know we have reached the end of our linked list, and if we do, we return null because the email is not in our table. If it is, then we return our pointer to our customer c.

Customer *lookup(hashtable table, char email)
	Int index = hash(email)
	Customer c = customers index
	Linkedlist head = list index
	While c is not null
		If c email is email
			Return c
		If head is null
			Return null
		C = head customer
		Head = next
	Return NULL

Next we will implement addt. This will use our linked lists and our replace function. We should create a customer node and assign it to an index, then we should point to that index with a pointer. This is to test if that pointer already exists under that email and if it does, we should update the pointer with the new information provided. If it doesn’t, we can reallocate memory for the customers linked list and add our customer object to the list. 

Hashtable *addt(Hashtable *Customers, char*email, char*name, int shoesize, char *food)
	New Customer c
	Unsigned index = hash(email)
	Customer ptr = index of customers
	If there are no customers yet
		Table ->customers[index] = customer
		Table count ++
	Else
		Update name, shoesize, food for that customer
		Return

Delete will take our hash table and the string for the email that we are trying to delete. We’ll call upon our hash function to find the address of the email in question, and from there we will mess around with our linked lists. It will check if the head is the last element in the hash table, and if it is, we just free it without doing anything else. If it is not, however, we will have to relink the linked list together without the node. We can do this by using pointers named curr and prev. 

Void delete(table t, email)
	Index = hash(email)
	Customer *c = table->customers[index]
	Ll *head = start of buckets
	If customer email matches email,
		Table ->customers[index] = null
		Free_customer
		Table count minus 1
	Ll curr = head
	Ll prev = null
	While curr is not null
		If curr customer email = email
			If prev = null
				Free head
				Table buckets[index] = null
				Return
			Else
				Prev next = curr next
				Curr next = null
				Free curr
				Table buckets[index] = head
				Return
		Curr next
		Prev = curr

We should also make a print table function to make it easier for when the user types in ‘list’. It’s a simple function that will just print everything. Of course, it will check if the index actually has anything to print or else it will ignore it.

Void print_table(Hashtable t)
	for (int i=0,i<table_size,i++)
		if(table->customers[i])
			Print everything

Next will be our main function that will take in our customers.tsv file and read it, and store all of the tab and line separated things into the hashtable. In this, we will also call our free functions at the end and scan for user input in an infinite while loop until the user input ‘quit’ is called. On top of quit, there are 5 other commands. Save will save the state of the hash table into the customers.tsv file, add will add another user to the hashtable based on scanning user input for email, name, shoe size and favorite food Lookup will print the details of one linked list in the hashtable depending on if it exists, delete will get rid of a linked list in the hash table, and list will just print the entire hashtable. 
Luckily, we already have functions for most of these. We can hardcode the input file to be customers.tsv.

Int main(int argc, char **argv) 
	Character ptr = null
	Declare buf string
	Open file customers.tsv
	Hashtable create with max size (MAX at beginning)
	While fgets not null
		Int i = 0
		Declare email, name food, as char* and set to null
		Shoesize = 0
		Ptr = take each tab separated thing
		Email = first ptr
		For every subsequent ptr,
			I++
			If i = 1, name = ptr
			If i = 2, shoesize = int(ptr)
			If i=3, food = ptr
		Add ptr to customers hashtable
	Fclose
	Infinite while loop
		Char str[20]
		Enter command and scan to str
		If string == quit
			Exit infinite while loop
		If string == save
			Open customers.tsv again but with “w” argument
			For each i in customers size,
				If customers->customers[i] exists,
					Char ptr equal to printstr(customers->customers[i])
					Fputs into file
					Free print
			Fclose
		If string == add
			Declare email, name, shoesize, food arrays
			Ask user input
			Add new customer with those parameters
		If string == lookup
			Declare email array
			Ask for user input
			Call lookup function and assign value to pointer
			If pointer is not null
				Print details of lookup
			If pointer is null
				Print user not found
		If string == delete
			Declare email array and ask for user input
			Call lookup function to see if its there
			If it is, call our delete function
			If its not, print user not found
		If string == list
			Print table
		Other wise print unknown command

	Free table at the end and return 0.
	

		

