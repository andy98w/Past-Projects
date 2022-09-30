/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#7
* DictionaryTest.cpp
* Dictionary test program
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

   string s;
   Dictionary A;
   Dictionary B;
   A.setValue("a", 1);
    A.setValue("b", 5);
    A.setValue("e", 10);
    A.setValue("h", 15);
    A.setValue("f", 20);
    A.setValue("i", 100);
   std::string ideal = "a : 1\nb : 5\ne : 10\nf : 20\nh : 15\ni : 100\n";
   cout<<"A size="<<A.size()<<endl<<A<<endl;
   cout<<"ideal"<<endl<<ideal<<endl;
   string n = A.to_string();
   cout<<"n = A.to_string()"<<endl<<n<<endl;
   cout<<"n==ideal?"<<(n==ideal?"true":"false")<<endl;
   cout<<A.pre_string()<<endl;
   B = A;
   cout<<"B size="<<B.size()<<endl<<B<<endl;
   A.remove("a");
   A.remove("h");
   cout<<A.contains("h")<<endl;
   cout<<A.getValue("i")<<endl;
   cout<<A<<endl;
   B.setValue("i", 200);
   int x;
   for(B.begin(); B.hasCurrent(); B.next()){
      s = B.currentKey();
      x = B.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl << endl;
   for(A.end(); A.hasCurrent(); A.prev()){
      s = A.currentKey();
      x = A.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl<<"A==B is " << (A==B?"true":"false") << endl;
   A.clear();
   cout<<endl<<A.size()<<endl;
   B.clear();
   cout << endl<<"A==B is " << (A==B?"true":"false") << endl;
   cout << A << endl;
   return( EXIT_SUCCESS );
}