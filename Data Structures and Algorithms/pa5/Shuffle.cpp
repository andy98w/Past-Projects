/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#5
* Shuffle.cpp
* Shuffle program
*********************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include <cmath>
#include <iomanip>
using namespace std;
#include"List.h"

void shuffle(List &D){
    List E, F;
    int tmp=D.length();
    int n =floor(D.length()/2);
    D.moveFront();
    E.moveBack();
    F.moveBack();
    for(int i = 0;i<n;i++){
        E.insertBefore(D.moveNext());
    }
    for(int i=n;i<D.length();i++){
        F.insertBefore(D.moveNext());
    }
    D.clear();
    D.moveBack();
    E.moveFront();
    F.moveFront();
    for(int i=0;i<n;i++){
        D.insertBefore(F.moveNext());
        D.insertBefore(E.moveNext());
    }
    if(tmp%2!=0){
        D.insertBefore(F.moveNext());
    }
}
int main (int argc, char *argv[]) { 
    int n;
    if( argc != 2 ){
        cerr << "Usage: " << argv[0] << " <number of cards>" << endl;
        return(EXIT_FAILURE);
    }
    cout<<"deck size       shuffle count"<<endl;
    cout<<"------------------------------"<<endl;
    n = atoi(argv[1]);
    for(int i =0;i<n;i++){
        List L, K;
        for(int j=0;j<=i;j++){
            L.insertBefore(j);
            K.insertBefore(j);
        }
        shuffle(L);
        int count = 1;
        while(!(L==K)){
            shuffle(L);
            count++;
        }
        cout<<L.length()<<setw(16)<<count<<endl;
        
    }
    return 0;
}
