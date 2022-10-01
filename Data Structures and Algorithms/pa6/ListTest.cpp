/******************************************************************************** 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#6 
* ListTest.cpp 
* Test Client for List ADT
********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
   List A, B;
   for(int i=1; i<=20; i++){
      A.insertAfter(i);
      cout << "A = " << A << endl;
      B.insertBefore(i);
      cout << "B = " << B << endl;
   }
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   A.moveBack();
   B.moveBack();
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   for(int i=1; i<=10; i++){
      cout << A.movePrev() << " ";
      cout << B.movePrev() << " ";
   }
   cout << endl << "A.position() = " << A.position() << endl;
   cout << endl << "B.position() = " << B.position() << endl;
   cout << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   List C = A;
   cout << "A==C is " << (A==C?"true":"false") << endl;
   cout << C << endl;
   cout << endl;
   B.moveFront();
   cout << B.findNext(5) << endl;
   cout << B << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   B.moveBack();
   cout << B.position() << endl;
   cout << B.findPrev(2) << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   B.moveFront();
   for(int i =0;i<20;i++){
      B.insertAfter(i);
   }
   cout << B << endl;
   B.cleanup();
   cout << B << endl;
   B.setAfter(5);
   cout << B << endl;
   B.moveNext();
   B.setBefore(5);
   A.moveFront();
   A.cleanup();
   cout << "A = " << A << endl;
   cout << A.position() << endl;
   cout << endl;
   List E = A;
   cout << "E==A is " << (E==A?"true":"false") << endl;
   std::cout<<E<<std::endl;
   cout << endl;
   List F = A.concat(B);
   cout << "F = " << F << endl;
   cout << "length: " << F.length() << endl;
   cout << "front: " << F.front() << endl;
   cout << "back: " << F.back() << endl;
   cout << "position: " << F.position() << endl;
   F.moveNext();
   for( int i=1; i<=10; i++){
      cout << "peekNext: " << F.peekNext() << endl;
      cout << "peekPrev: " << F.peekPrev() << endl;
      F.moveNext();
   }
   cout << "F = " << F << endl;
   cout << endl;
   return( EXIT_SUCCESS );
}
