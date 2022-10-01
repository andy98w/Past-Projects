/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#6
* Arithmetic.cpp
* Executable program
*********************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include <cmath>
#include <iomanip>
using namespace std;
#include"BigInteger.h"
#define MAX_LEN 300

int main (int argc, char *argv[]) { 
    int line_count;
   size_t begin, end, line_length;
   ifstream in;
   ofstream out;
   string line;
   string token;
   BigInteger A, B;
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }
   // read each line of input file, then count and print tokens 
   line_count = 0;
   while( getline(in, line) )  {
      line_count++;
      line_length = line.length();
      string tokenBuffer = "";
      begin = min(line.find_first_not_of(" ", 0), line_length);
      end = min(line.find_first_of(" ", begin), line_length);
      token = line.substr(begin, end-begin);
      while( token!="" ){ 
        tokenBuffer += token;
         begin = min(line.find_first_not_of(" ", end+1), line_length);
         end = min(line.find_first_of(" ", begin), line_length);
         token = line.substr(begin, end-begin);
      }
      if(line_count==1)
        A= BigInteger(tokenBuffer);
      if(line_count==3)
        B = BigInteger(tokenBuffer);
   }    
   BigInteger C=BigInteger("2");
    BigInteger D=BigInteger("3");
    BigInteger E=BigInteger("9");
    BigInteger F=BigInteger("16");
   out << A << "\n" << endl;
    out << B << "\n" << endl;
    out<<A+B<<"\n" << endl;
    out<<A-B<<"\n" << endl;
    out<<A-A<<"\n" << endl;
    out<<(A*D)-(B*C)<<"\n" << endl;
    out<<A*B<<"\n" << endl;
    out<<A*A<<"\n" << endl;
    out<<B*B<<"\n" << endl;
    out<<(E*A*A*A*A)+(F*B*B*B*B*B);
   in.close();
   out.close();
   return(EXIT_SUCCESS);
}
