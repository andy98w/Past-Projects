/******************************************************************************** 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#6 
* List.cpp 
* List ADT
********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}
List::List(){
	Node *front=new Node(-1);
	Node *back=new Node(-1);
	frontDummy=front;
	backDummy=back;
	frontDummy->next=backDummy;
	backDummy->prev=frontDummy;
	beforeCursor=frontDummy;
	afterCursor=backDummy;
	pos_cursor=0;
	num_elements=0;
}
List::List(const List& L){
	Node *front=new Node(-1);
	Node *back=new Node(-1);
	frontDummy=front;
	backDummy=back;
	frontDummy->next=backDummy;
	backDummy->prev=frontDummy;
    num_elements=0;
	Node *N=L.frontDummy->next;
	while(N->next!=nullptr){
		this->insertBefore(N->data);
		N=N->next;
	}
    beforeCursor=L.beforeCursor;
    afterCursor=L.afterCursor;
    pos_cursor=L.pos_cursor;
}
List::~List(){
	clear();
	Node *N = frontDummy;
	Node *M = backDummy;
	delete N;
	delete M;
}
int List::length() const{
	return(num_elements);
}
ListElement List::front() const{
	if(length()==0)
		throw std::length_error("List: front(): empty list");
	return(frontDummy->next->data);
}
ListElement List::back() const{
	if(length()==0)
		throw std::length_error("List: back(): empty list");
	return(backDummy->prev->data);

}
int List::position() const{
	return(pos_cursor);
}
ListElement List::peekNext() const{
	if(pos_cursor==num_elements)
		throw std::range_error("List: peekNext(): cursor at back");
	return(afterCursor->data);
}
ListElement List::peekPrev() const{
	if(pos_cursor==0)
		throw std::range_error("List: peekPrev(): cursor at front");
    return(beforeCursor->data);
}
void List::clear(){
	moveFront();
	while(afterCursor!=backDummy){
		eraseAfter();
	}
}
void List::moveFront(){
	pos_cursor=0;
	beforeCursor=frontDummy;
	afterCursor=frontDummy->next;
}
void List::moveBack(){
	pos_cursor=num_elements;
	beforeCursor=backDummy->prev;
	afterCursor=backDummy;
}
ListElement List::moveNext(){
	if(pos_cursor==num_elements)
		throw std::range_error("List: moveNext(): cursor at back");
	pos_cursor++;
	afterCursor=afterCursor->next;
	beforeCursor=beforeCursor->next;
	return(beforeCursor->data);
}
ListElement List::movePrev(){
	if(pos_cursor==0)
		throw std::range_error("List: movePrev(): cursor at front");
    pos_cursor--;
    afterCursor=afterCursor->prev;
	beforeCursor=beforeCursor->prev;
    return(afterCursor->data);
}
void List::insertAfter(ListElement x){
	Node *N=new Node(x);
	if(length()==0){
		N->prev=frontDummy;
		N->next=backDummy;
		backDummy->prev=N;
		frontDummy->next=N;
		num_elements++;
		moveFront();
	}
	else{
		N->next=afterCursor;
		N->prev=afterCursor->prev;
		afterCursor->prev=N;
		afterCursor=N;
		beforeCursor->next=N;
		num_elements++;
	}
}		
void List::insertBefore(ListElement x){
	Node *N=new Node(x);
	if(length()==0){
		N->prev=frontDummy;
		N->next=backDummy;
		backDummy->prev=N;
		frontDummy->next=N;
		num_elements++;
		moveBack();
	}
    else{
		N->prev=beforeCursor;
		N->next=beforeCursor->next;
		beforeCursor->next=N;
		beforeCursor=N;
		afterCursor->prev=N;
		pos_cursor++;
		num_elements++;
    }
}
void List::setAfter(ListElement x){
	if(pos_cursor==num_elements)
		throw std::range_error("List: setAfter(): cursor at back");
	eraseAfter();
	insertAfter(x);
}
void List::setBefore(ListElement x){
	if(pos_cursor==0)
		throw std::range_error("List: setBefore(): cursor at front");
	eraseBefore();
	insertBefore(x);
}
void List::eraseAfter(){
	if(pos_cursor==num_elements)
		throw std::range_error("List: eraseAfter(): cursor at back");
	Node *N=afterCursor;
    afterCursor->next->prev=afterCursor->prev;
	afterCursor->prev->next=afterCursor->next;
	num_elements--;
	afterCursor=afterCursor->next;
    delete N;
}
void List::eraseBefore(){
	if(pos_cursor==0)
		throw std::range_error("List: eraseBefore(): cursor at front");
    Node *N=beforeCursor;
    beforeCursor->prev->next=beforeCursor->next;
	beforeCursor->next->prev=beforeCursor->prev;
    num_elements--;
	pos_cursor--;
	beforeCursor=beforeCursor->prev;
    delete N; 
}
   // Other Functions ---------------------------------------------------------
int List::findNext(ListElement x){
    Node *M=afterCursor;
    for(int i=0;i<length();i++){
		if(position()==length()){
			return -1;
		}
		if(M->data==x){
			pos_cursor++;
			beforeCursor=beforeCursor->next;
			afterCursor=afterCursor->next;
			return pos_cursor;
		}
		pos_cursor++;
		beforeCursor=beforeCursor->next;
		afterCursor=afterCursor->next;
        M=M->next;
    }
	return -1;
}
int List::findPrev(ListElement x){
    Node *M=beforeCursor;
    for(int i=0;i<num_elements;i++){
		if(position()==0){
			return -1;
		}
        if(M->data==x){
			pos_cursor--;
			beforeCursor=beforeCursor->prev;
			afterCursor=afterCursor->prev;
            return pos_cursor;
        }
    	pos_cursor--;
		beforeCursor=beforeCursor->prev;
		afterCursor=afterCursor->prev;
        M=M->prev;
    }
	return -1;
}
void List::cleanup(){
	Node *N=frontDummy->next;
	Node *O=beforeCursor;
	moveFront();
	int counter=0;
	while(N!=backDummy){
		moveFront();
		for(int i=0;i<=counter;i++){
			moveNext();
		}
		if(findNext(N->data)!=-1){
			if(O->data==N->data&&O->next==afterCursor){
				O=O->prev;
			}
			eraseBefore();
			moveFront();
		}
		else{
			N=N->next;
			counter++;
		}
	}
	moveFront();
	Node *P = frontDummy;
	while(P!=O){
		P=P->next;
		moveNext();
	}
}
List List::concat(const List& L) const{
	List J;
	Node*N=this->frontDummy->next;
	Node *M = L.frontDummy->next;
	J.moveBack();
	while(N->next!=nullptr){
		J.insertBefore(N->data);
		N=N->next;
	}
	while(M->next!=nullptr){
		J.insertBefore(M->data);
		M=M->next;
	}
	J.moveFront();
	return J;
}	
std::string List::to_string() const{
	Node *N = nullptr;
	if(length()==0)
		return "()";
	std::string s = "(";
	for(N=frontDummy->next;N->next!=nullptr;N=N->next){
		s+=std::to_string(N->data)+ ", ";
	}
	s.erase(s.length()-1);
	s.erase(s.length()-1);
	s+=")";
	return s;
}	
bool List::equals(const List& R) const{
	bool eq = false;
	Node* N = nullptr;
	Node* M = nullptr;
	eq = ( this->length() == R.length() );
	N = this->frontDummy;
	M = R.frontDummy;
	while( eq && N!=nullptr){
		eq = (N->data==M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}
   // Overriden Operators -----------------------------------------------------
std::ostream& operator<<( std::ostream& stream, const List& L ){
	return stream << L.List::to_string();
}
bool operator==( const List& A, const List& B ){
   return A.List::equals(B);	
}
List& List::operator=( const List& L ){
   if( this != &L ){ 
      List temp = L;
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
    }
   return *this;
}
