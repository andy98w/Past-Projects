/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#7
* Order.cpp
* Order executable program
*********************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;
#include"Dictionary.h"

int main (int argc, char *argv[]) { 
    int line_count;
   size_t begin, end, line_length;
   ifstream in;
   ofstream out;
   string line;
   string token;
   Dictionary D;
   string delim = " \t\\\"\',%<.>/?;:[{]}|`~!@#$^&*()-_=+0123456789";
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
   line_count = 0;
   while( getline(in, line) )  {
      line_count++;
      line_length = line.length();
      string tokenBuffer = "";
      begin = min(line.find_first_not_of(delim, 0), line_length);
      end = min(line.find_first_of(delim, begin), line_length);
      token = line.substr(begin, end-begin);
      while( token!="" ){ 
        tokenBuffer = token;
        std::for_each(tokenBuffer.begin(), tokenBuffer.end(), [](char & c){
            c = ::tolower(c);
        });
        if(D.contains(tokenBuffer)){
            D.setValue(tokenBuffer,D.getValue(tokenBuffer)+1);
        }
        else{
          D.setValue(tokenBuffer,1);
        }
         begin = min(line.find_first_not_of(delim, end+1), line_length);
         end = min(line.find_first_of(delim, begin), line_length);
         token = line.substr(begin, end-begin);
      }
   }
   out<<D<<endl;
   in.close();
   out.close();
   return(EXIT_SUCCESS);
}