/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#7
* Dictionary.cpp
* Dictionary program
*********************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include <cmath>
#include <iomanip>
using namespace std;
#include "Dictionary.h"

// Private Constructor --------------------------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v){
   key = k;
   val = v;
}
   // Helper Functions (Optional) ---------------------------------------------
void Dictionary::inOrderString(std::string& s, Node* R) const{
   if(R!=nil){
      inOrderString(s, R->left);
      s.append(R->key);
      s.append(" : ");
      s.append(std::to_string(R->val));
      s.append("\n");
      inOrderString(s, R->right);
   }
}
void Dictionary::preOrderString(std::string& s, Node* R) const{
   if(R!=nil){
      s.append(R->key);
      s.append("\n");
      preOrderString(s, R->left);
      preOrderString(s, R->right);
   }
}
void Dictionary::preOrderCopy(Node* R, Node* N){
   if(R==N){
      return;
   }
   if(R!=nil){
      setValue(R->key,R->val);
      preOrderCopy(R->left, N);
      preOrderCopy(R->right, N);
   }
}
void Dictionary::postOrderDelete(Node* R){
   if(R!=nil){
      postOrderDelete(R->left);
      postOrderDelete(R->right);
      delete R;
      num_pairs--;
   }
   R = nil;
}
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
   if(R==nil||k==R->key){
      return R;
   }
   else if(k<R->key){
      return search(R->left,k);
   }
   else if(k>R->key){
      return search(R->right,k);
   }
   else{
      return nil;
   }
}
Dictionary::Node* Dictionary::findMin(Node* R) const{
   while(R->left!=nil){
      R = R->left;
   }
   return R;
}
Dictionary::Node* Dictionary::findMax(Node* R) const{
   while(R->right!=nil){
      R= R->right;
   }
   return R;
}
Dictionary::Node* Dictionary::findNext(Node* N)const{
   if(N->right!=nil){
      return(findMin(N->right));
   }
   Node *R = N->parent;
   while(R!=nil&&N==R->right){
      N = R;
      R = R->parent;
   }
   return R;
}
Dictionary::Node* Dictionary::findPrev(Node* N)const{
   if(N->left!=nil){
      return(findMax(N->left));
   }
   Node *R = N->parent;
   while(R!=nil&&N==R->left){
      N = R;
      R = R->parent;
   }
   return R;
}
void Dictionary::Transplant(Node *u, Node* v){
   if(u->parent == nil){
      root = v;
   }
   else if(u==u->parent->left){
      u->parent->left=v;
   }
   else{
      u->parent->right = v;
   }
   if(v!=nil){
      v->parent = u->parent;
   }
}
   // Class Constructors & Destructors ----------------------------------------
Dictionary::Dictionary(){
   num_pairs=0;
   nil = new Node("0", 0);
   nil->parent = nil;
   nil->left = nil;
   nil->right = nil;
   root = nil;
   current = nil;
}
Dictionary::Dictionary(const Dictionary& D){
   nil = new Node("0", 0);
   nil->parent = nil;
   nil->left = nil;
   nil->right = nil;
   root = nil;
   current = nil;
   num_pairs=0;
   preOrderCopy(D.root,D.nil);
}
Dictionary::~Dictionary(){
   if(root!=nil){
      postOrderDelete(root);
   }
   delete nil;
}
   // Access functions --------------------------------------------------------
int Dictionary::size() const{
   return num_pairs;
}
bool Dictionary::contains(keyType k) const{
   Node *N = search(root,k);
   if(N == nil){
      return false;
   }
   return true;
}
valType& Dictionary::getValue(keyType k) const{
   Node *N;
   N = search(root,k);
   if(N==nil){
      throw std::logic_error("Dictionary: getValue(): key \"" + k +"\" does not exist");
   }
   return N->val;
}
bool Dictionary::hasCurrent() const{
   if(current==nil){
      return false;
   }
   return true;
}
keyType Dictionary::currentKey() const{
   if(current==nil){
      throw std::logic_error("Dictionary: currentKey(): current undefined");
   }
   return current->key;
}
valType& Dictionary::currentVal() const{
   if(current==nil){
      throw std::logic_error("Dictionary: currentVal(): current undefined");
   }
   return current->val;
}
   // Manipulation procedures -------------------------------------------------
void Dictionary::clear(){
   if(root!=nil){
      postOrderDelete(root);
   }
   current = nil;
   root = nil;
}
void Dictionary::setValue(keyType k, valType v){
      Node *y = nil;
      Node *x = root;
      while(x!=nil){
         y = x;
         if(k==x->key){
            x->val = v;
            return;
         }
         else if(k<x->key){
            x = x->left;
         }
         else{
            x = x->right;
         }
      }
      Node *N = new Node(k,v);
      N->left = nil;
      N->right = nil;
      N->parent = y;
      if(y==nil){
         root = N;
      }
      else if(N->key<y->key){
         y->left = N;
      }
      else{
         y->right = N;
      }
      num_pairs++;
}
void Dictionary::remove(keyType k){
   if(current->key == k){
      current = nil;
   }
   Node *N = search(root,k);
   if(N==nil){
      throw std::logic_error("Dictionary: remove(): key \"" + k +"\" does not exist");
   }
   if(N->left==nil){
      Transplant(N,N->right);
   }
   else if(N->right==nil){
      Transplant(N,N->left);
   }
   else{
      Node *y=findMin(N->right);
      if(y->parent!=N){
         Transplant(y,y->right);
         y->right = N->right;
         y->right->parent = y;
      }
      Transplant(N,y);
      y->left = N->left;
      y->left->parent = y;
   }
   delete N;
   num_pairs--;
}
void Dictionary::begin(){
   if(root!=nil){
      current = findMin(root);
   }
}
void Dictionary::end(){
   if(root!=nil){
      current = findMax(root);
   }
}
void Dictionary::next(){
   if(current==nil){
      throw std::logic_error("Dictionary: next(): current not defined");
   }
   if(current!=findMax(root)){
      current = findNext(current);
   }
   else{
      current = nil;
   }
}
void Dictionary::prev(){
   if(current==nil){
      throw std::logic_error("Dictionary: prev(): current not defined");
   }
   if(current!=findMin(root)){
      current = findPrev(current);
   }
   else{
      current = nil;
   }
}
   // Other Functions ---------------------------------------------------------
std::string Dictionary::to_string() const{
   std::string s ="";
   inOrderString(s,root);
   return s;
}
std::string Dictionary::pre_string() const{
   std::string s ="";
   preOrderString(s,root);
   return s;
}
bool Dictionary::equals(const Dictionary& D) const{
   std::string s = "";
   std::string t= "";
   inOrderString(s,root);
   D.inOrderString(t,D.root);
   if(s!=t){
      return false;
   }
   return true;
}
   // Overloaded Operators ----------------------------------------------------
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
   return stream << D.Dictionary::to_string();
}
bool operator==( const Dictionary& A, const Dictionary& B ){
   return A.equals(B);
}
Dictionary& Dictionary::operator=( const Dictionary& D ){
   if( this != &D ){ 
      Dictionary temp = D;
      std::swap(root, temp.root);
      std::swap(current, temp.current);
      std::swap(nil, temp.nil);
      std::swap(num_pairs, temp.num_pairs);
    }
   return *this;
}