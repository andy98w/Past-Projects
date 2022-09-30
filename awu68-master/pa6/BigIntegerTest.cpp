/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#6
* BigIntegerTest.cpp
* BigInteger Test Program
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

   string j = "9128734667004545435364356754";
   string i = "987856847567269582786592698562";

   BigInteger A = BigInteger(j);
   BigInteger B = BigInteger(i);
   cout << endl;
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << endl;
   cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
   cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
   cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
   cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
   cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl;
   BigInteger C = A+B;
   BigInteger D = A-B;
   BigInteger E = A*A;
   BigInteger F = B*B;
   BigInteger G = A*B;
   BigInteger H = E*F;
   BigInteger I = E*E;
   cout << "I = " << I << endl;
   cout << "C = " << C << endl;
   cout << "D = " << D << endl;
   cout << "E = " << E << endl;
   cout << "F = " << F << endl;
   cout << "G = " << G << endl;
   cout << "H = " << H << endl;
   cout << "I = " << I << endl << endl;

   cout<<I.sign()<<endl;
   I.negate();
   cout<<I.sign()<<endl;
   I.makeZero();
   cout<<I.sign()<<endl;
   cout<<I<<endl;
   cout << endl;

   A += B;
   B -= C;
   C *= D;
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << endl;

   cout << A*B*C*D*F*G*H << endl << endl;

   cout << endl;

   return EXIT_SUCCESS;
}
