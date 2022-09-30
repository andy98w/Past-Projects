//Andrew Wu
//ID#1833341
//pa1

#include<stdbool.h>
#include "List.h"
typedef struct NodeObj* Node;
typedef struct NodeObj{
        int data;
        Node next;
        Node previous;
}NodeObj;
typedef struct ListObj{
        Node front;
        Node back;
        int length;
        int index;
        Node cursor;
}ListObj;
Node newNode(int data){
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
int front(List L){
	return L->front->data;
}
int back(List L){
	return L->back->data;
}
int get(List L){
	Node N = L->cursor;
	return N->data;
}
bool equals(List A, List B){
	Node N, M;
	bool eq;
	eq = (A->length == B->length);
	N=A->front;
	M=B->front;
	while(eq&&N!=NULL){
		eq=(N->data==M->data);
		N=N->next;
		M=M->next;
	}
	return eq;
}
void clear(List L){
	while(L->front!=NULL){
		deleteBack(L);
	}
	L->length=0;
	L->cursor=NULL;
	L->front=L->back=NULL;
}
void set(List L, int x){
	L->cursor->data=x;
}
void moveFront(List L){
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
void prepend(List L, int x){
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
void append(List L, int x){
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
void insertBefore(List L, int x){
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
void insertAfter(List L, int x){
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
void printList(FILE* out, List L){
	Node N=L->front;
	while(N!=NULL){
		char *print=malloc(sizeof(char*));
		char *space = " ";
		sprintf(print,"%d",N->data);
		strncat(print,space,1);
		fputs(print,out);
		N=N->next;
		free(print);
	}
	fputs("\n",out);
}
List copyList(List L){
	Node N=L->front;
	List new = newList();
	while(N!=NULL){
		append(new,N->data);
		N=N->next;
	}
	return new;
}

