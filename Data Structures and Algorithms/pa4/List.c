/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#4 
* List.c
* Main file for List ADT
*********************************************************************************/

#include<stdbool.h>
#include "List.h"
typedef struct NodeObj* Node;
typedef struct ListObj{
        Node front;
        Node back;
        int length;
        int index;
        Node cursor;
}ListObj;
typedef struct NodeObj{
        void *data;
        Node next;
        Node previous;
}NodeObj;
Node newNode(void *data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->previous = NULL;
	return N;
}
void freeNode(Node *pN){
	free(*pN);
	*pN=NULL;
}
List newList(){
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
}
bool isEmpty(List L){
        if(L==NULL){
                printf("List Error: calling isEmpty() on NULL List reference\n");
                exit(1);
        }
        return(L->length==0);
}
void freeList(List *pL){
	moveBack(*pL);
	while(index(*pL)!=-1){
		movePrev(*pL);
		deleteBack(*pL);
	}
	free(*pL);
	*pL=NULL;
}
int length(List L){
	return L->length;
}
int index(List L){
	Node N = L->front;
	for(int i=0;i<L->length;i++){
		if(N==L->cursor){
			return i;
		}
		N=N->next;
	}
	return -1;
}
void* front(List L){
	return L->front->data;
}
void* back(List L){
	return L->back->data;
}
void* get(List L){
	if (L == NULL){
		printf("error at get");
		return NULL;
	}
	if(L->cursor==NULL)
		return NULL;
	Node N = L->cursor;
	return N->data;
}
void clear(List L){
	while(L->front!=NULL){
		deleteBack(L);
	}
	L->length=0;
	L->cursor=NULL;
	L->front=L->back=NULL;
}
void set(List L, void* x){
	L->cursor->data=x;
}
void moveFront(List L){
	if (L == NULL) {
	  printf("Error in movefront\n");
	  return;
	}
	L->cursor = L->front;
}
void moveBack(List L){
	L->cursor = L->back;
}
void movePrev(List L){
	if(L->cursor==L->front)
		L->cursor=NULL;
	else
		L->cursor=L->cursor->previous;
}
void moveNext(List L){
	if(L->cursor==L->back)
		L->cursor=NULL;
	else
		L->cursor=L->cursor->next;
}
void prepend(List L,void* x){
	if(L->length==0){
		Node N=newNode(x);
		L->front=L->back=N;
		L->length++;
	}
	else{
		Node N=newNode(x);
		N->next=L->front;
		L->front->previous=N;
		L->front=N;
		L->length++;
	}
}
void append(List L, void* x){
	if(L->length==0){
		Node N=newNode(x);
		L->back=L->front=N;
		L->length++;
	}
	else{
		L->length++;
		Node N=newNode(x);
		N->previous = L->back;
		L->back->next=N;
		L->back=N;
	}
}
void insertBefore(List L, void* x){
	Node N = L->cursor;
	Node new = newNode(x);
	if(L->cursor==L->front){
		new->previous=NULL;
		new->next=N;
		N->previous=new;
		L->front=new;
	}
	else{
		new->previous=N->previous;
		N->previous->next=new;
		new->next=N;
        	N->previous=new;
	}
	L->length++;
}
void insertAfter(List L, void* x){
	Node N = L->cursor;
        Node new = newNode(x);
	if(L->cursor==L->back){
		new->next=NULL;
		new->previous=N;
		N->next=new;
		L->back=new;
	}
	else{
		N->next->previous=new;
        	new->next=N->next;
        	new->previous=N;
        	N->next=new;
	}	
	L->length++;
}
void deleteFront(List L){
	Node tmp=L->front;
	if(L->cursor==L->front)
		L->cursor=NULL;
	if(L->length>1)
		L->front = L->front->next;
	else
		L->front=L->back=NULL;
	L->length--;
	freeNode(&tmp);
}
void deleteBack(List L){
	Node tmp=L->back;
	if(L->cursor==L->back)
		L->cursor=NULL;
	if(L->length>1)
                L->back = L->back->previous;
        else
                L->front=L->back=NULL;
	L->length--;
        freeNode(&tmp);
}
void delete(List L){
	Node N = L->cursor;
	if(N==L->front){
		deleteFront(L);
	}
	else if(N==L->back){
		deleteBack(L);
	}
	else{
		N->previous->next = N->next;
		N->next->previous = N->previous;
		L->cursor=L->cursor->next;
		L->length--;
		freeNode(&N);
	}
}
