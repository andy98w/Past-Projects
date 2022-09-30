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
      begin = min(line.find_first_not_of(" ", 0), line_length);
      end = min(line.find_first_of(" ", begin), line_length);
      token = line.substr(begin, end-begin);
      while( token!="" ){ 
        tokenBuffer += token;
         begin = min(line.find_first_not_of(" ", end+1), line_length);
         end = min(line.find_first_of(" ", begin), line_length);
         token = line.substr(begin, end-begin);
      }
      D.setValue(tokenBuffer,line_count);
   }
   out<<D<<endl;
   out<<D.pre_string()<<endl;
   in.close();
   out.close();
   return(EXIT_SUCCESS);
}