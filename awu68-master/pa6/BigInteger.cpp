/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#6
* BigInteger.cpp
* BigInteger program
*********************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include <cmath>
#include <iomanip>
using namespace std;
#include"BigInteger.h"
const int power = 9;
const long base = pow(10,power);
void shiftList(List& L, int p){
    L.moveFront();
    for(int i = 0;i<p;i++){
        L.insertBefore(0);
    }
}
void sumList(List &S,List A,List B, int sgn) {
    int diff = A.length()-B.length();
    if(diff>0){
        shiftList(B,diff);
    }
    if(diff<0){
        shiftList(A,(-1)*diff);
    }
    shiftList(S,A.length());
    A.moveBack();
    B.moveBack();
    S.moveBack();
    for(int i =0;i<A.length();i++){
        S.setBefore(A.movePrev()+sgn*B.movePrev());
        S.movePrev();
    }
}
void negateList(List &L){
    List J;
    L.moveBack();
    for(int i = 0; i<L.length();i++){
        J.insertAfter(L.movePrev()*(-1));
    }
    L = J;
}
int normalizeList(List& L){
    int ret = 1;
    long long tmp = 0;
    int carry = 0;
    L.moveBack();
    List J;
    for(int i = 0;i<L.length();i++){
        if(i==L.length()&&carry!=0){
            shiftList(L,1);
        }
        tmp = L.movePrev();
        if(carry!=0){
            tmp+=carry;
            carry=0;
        }
        if(tmp<0&&i<L.length()-1){
            tmp=base+tmp;
            carry--;
        }
        while(tmp>=base){
            carry = floor(tmp/base);
            tmp = tmp%base;
        }
        J.insertAfter(tmp);
    }
    L = J;
    L.moveFront();
    while(L.peekNext()==0&&L.length()!=1){
        L.eraseAfter();
    }
    L.moveFront();
    if(L.length()==1&&L.peekNext()==0)
        return 0;
    L.moveFront();
    if(L.peekNext()<0){
        ret = -1;
        int bye = L.peekNext();
        L.eraseAfter();
        L.insertAfter(bye*(-1));
    }
    return ret;
}
void scalarMultList(List& L, ListElement m){
    L.moveBack();
    List J;
    for(int i =0;i<L.length();i++){
        J.insertAfter(m*L.movePrev());
    }
    L = J;
}
// Class Constructors & Destructors ----------------------------------------
BigInteger::BigInteger(){
    List digits;
    signum = 0;
}
BigInteger::BigInteger(std::string s){
    if(s==""){
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    if(s[0]=='-'){
        signum = -1;
        s.erase(0,1);
    }
    else if(s[0]=='+'){
        signum = 1;
        s.erase(0,1);
    }
    else{
        signum = 1;
    }
    int mod = s.length()%power;
    if(mod!=0){
        for(int i = 0;i<power-mod;i++){
            s.insert(0,1,'0');
        }
    }
    for(size_t i = s.length(); i>0;i-=power){
        int tmp=0;
        std::string a = s.substr(i-power,power);
        for(char const &ch : a){
            if(std::isdigit(ch)==0){
                 throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
             }
        }
        for(int j = 0;j<power;j++){
            tmp+=((int)a[j]-48)*pow(10,power-j-1);
        }
        digits.insertAfter(tmp);
    }
}
BigInteger::BigInteger(const BigInteger& N){
    List L = N.digits;
    digits = L;
    signum = N.signum;
}
   // Access functions --------------------------------------------------------
int BigInteger::sign() const{
    return signum;
}
int BigInteger::compare(const BigInteger& N) const{
       bool flip = false;
       if(signum>N.sign()){
           return 1;
       }
       else if(signum<N.sign()){
           return -1;
       }
       else if(signum==N.sign()){
           if(signum==0){
               return 0;
           }
           if(signum==-1){
               flip = true;
           }
           List A = digits;
           List B = N.digits;
           A.moveFront();
           B.moveFront();
            if(A.length()<B.length()){
                   if(flip)
                        return 1;
                    return -1;
            }
            else if(B.length()<A.length()){
                    if(flip)
                        return -1;
                    return 1;
           }
           for(int i = 1; i<A.length();i++){
               if(A.peekNext()>B.peekNext()){
                   if(flip){
                       return -1;
                   }
                   return 1;
               }
               if(B.peekNext()>A.peekNext()){
                   if(flip){
                       return 1;
                   }
                   return -1;
               }
               A.moveNext();
               B.moveNext();
           }
       }
    return 0;
}
   // Manipulation procedures -------------------------------------------------
void BigInteger::makeZero(){
       signum = 0;
       digits.clear();
   }
void BigInteger::negate(){
       if(signum==0){
           return;
       }
       else{
           signum = (-1)*signum;
       }
   }
   // BigInteger Arithmetic operations ----------------------------------------
BigInteger BigInteger::add(const BigInteger& N) const{
       BigInteger A;
       A.signum = 1;
       if(signum==1&&N.sign()==-1){
           sumList(A.digits,digits,N.digits,-1);
       }
       else if(signum==-1&&N.sign()==1){
           sumList(A.digits,N.digits,digits,-1);
       }
       else if(signum==0){
           A.digits = N.digits;
           A.signum = N.signum;
           return A;
       }
       else if(N.sign()==0){
           A.digits = digits;
           A.signum = signum;
           return A;
       }
       else if(N.sign()==-1){
           sumList(A.digits,digits,N.digits,1);
           A.signum = -1;
        }
        else{
            sumList(A.digits,digits,N.digits,1);
        }
        A.signum *= normalizeList(A.digits);
        return A;
}
BigInteger BigInteger::sub(const BigInteger& N) const{
        BigInteger A;
       A.signum = 1;
       if(signum==1&&N.sign()==-1){
           sumList(A.digits,digits,N.digits,1);
       }
       else if(signum==-1&&N.sign()==1){
           sumList(A.digits,N.digits,digits,1);
           A.signum = -1;
       }
       else if(signum==0){
           A.digits = N.digits;
           A.signum = N.signum;
           return A;
       }
       else if(N.sign()==0){
           A.digits = digits;
           A.signum = signum;
           return A;
       }
       else if(N.sign()==-1){
           sumList(A.digits,digits,N.digits,-1);
           A.signum = -1;
        }
        else{
            if(this->compare(N)<0){
                sumList(A.digits,N.digits,digits,-1);
                A.signum = -1;
            }
            else{
                sumList(A.digits,digits,N.digits,-1);
            }
        }
        A.digits.moveFront();
        A.signum *= normalizeList(A.digits);
        return A;
} 
BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger A;
    if(signum==0||N.signum==0){
        A.signum = 0;
        A.digits.insertAfter(0);
        return A;
    }
    List L,J;
    L = digits;
    J = N.digits;
    shiftList(L,J.length()-L.length());
    if(L.length()>J.length()){
        L = N.digits;
        J = digits;
    }
    List M;
    List K = L;
    shiftList(M,L.length()+J.length());
    L.moveBack();
    J.moveBack();
    List tmp;
    for(int i = 0;i<J.length();i++){
            tmp.clear();
            shiftList(tmp,L.length()+J.length());
            scalarMultList(L,J.movePrev());
            L.moveBack();
            for(int j = 0; j<i;j++){
                tmp.insertAfter(0);
            }
            for(int i =0;i<L.length();i++){
                tmp.insertAfter(L.movePrev());
             }
             normalizeList(tmp);
             normalizeList(M);
             sumList(M,tmp,M,1);
             L = K;
    }
    normalizeList(M);
    if(signum==N.signum){
        A.signum=1;
    }
    else{
        A.signum=-1;
    }
    A.digits=M;
    return A;
}
   // Other Functions ---------------------------------------------------------
std::string BigInteger::to_string(){
    List L = digits;
    std::string s="";
    std::string t="";
    if(signum == 0){
        return "0";
    }
    L.moveFront();
    int first = 0;
	for(int i = 0; i<L.length();i++){
        t=std::to_string(L.moveNext());
        if(t.length()!=power&&first!=0){
            while(t.length()!=power){
                t.insert(0,"0");
            }
        }
        first++;
		s+=t;
	}
    while(s[0]=='0'){
        s.erase(0,1);
    }
    if(signum == -1){
        s.insert(0,1,'-');
    }
	return s;
}
   // Overriden Operators -----------------------------------------------------
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();
}
bool operator==( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B)==0){
        return true;
    }
    return false;
}
bool operator<( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B)<0){
        return true;
    }
    return false;
}
bool operator<=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B)<1){
        return true;
    }
    return false;
}
 bool operator>( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B)>0){
        return true;
    }
    return false;
 } 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B)>-1){
        return true;
    }
    return false;
}
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}
 BigInteger operator-( const BigInteger& A, const BigInteger& B ){
     return A.sub(B);
 }
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return A;
}
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A;
}


