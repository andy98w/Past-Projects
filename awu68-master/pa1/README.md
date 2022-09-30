This program was written to sort lines of a given input text file, and print the results of the test
onto a given output text file. The lines will be sorted using an array of strings and linked lists,
where each line of the file will be put into an array of strings. The indexes of the array of strings
(i.e. the x in string[x]) will be put onto a linked list depending on how strcmp(str1,str2), compares
them to the previous elements of the list. The list will be traversed using a cursor node. List.h contains
all functions used, while the main executable will be Lex.c, or ./Lex after running the make command
on the makefile. ListTest will test the list ADT written in List.c. 
