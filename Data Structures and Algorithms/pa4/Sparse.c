/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#4 
* Sparse.c
* Executable File for pa4
*********************************************************************************/

#include "Matrix.h"
#define SIZE 500
int main(int argc, char **argv){
	if(argc!=3){
		fprintf(stderr, "usage: ./Sparse <inputfile> <outputfile>");
		exit(1);
	}
	FILE *infile=fopen(argv[1],"r");
	char buf[SIZE];
	int line = 0;
	int n, a, b;
	double x;
	Matrix A;
	Matrix B;
	int i,j;
	while((fgets(buf,SIZE,infile)!=NULL)){
		if(buf[0]=='\n'){
			line++;
		}
		else if(line==0){
			sscanf(buf,"%d %d %d",&n,&a,&b);
			A=newMatrix(n);
			B=newMatrix(n);
		}
		else if(line==1){
			sscanf(buf,"%d %d %lf", &i, &j, &x);
			changeEntry(A,i,j,x);
		}
		else if(line==2){
			sscanf(buf,"%d %d %lf", &i, &j, &x);
                        changeEntry(B,i,j,x);
		}
	}
	FILE *out=fopen(argv[2],"w");
	fprintf(out,"%s %d %s\n","A has ",NNZ(A)," non-zero entries:");
	printMatrix(out,A);
	fprintf(out,"\n");
	fprintf(out,"%s %d %s\n","B has ",NNZ(B)," non-zero entries:");
	printMatrix(out,B);
	fprintf(out,"\n");
	Matrix C = scalarMult(1.5,A);
	fprintf(out,"%s","(1.5)*A =\n");
        printMatrix(out,C);
	fprintf(out,"\n");
	Matrix D = sum(A,B);
        fprintf(out,"%s","A+B =\n");
        printMatrix(out,D);
        fprintf(out,"\n");
	Matrix E = sum(A,A);
        fprintf(out,"%s","A+A =\n");
        printMatrix(out,E);
        fprintf(out,"\n");
        Matrix F = diff(B,A);
        fprintf(out,"%s","B-A =\n");
        printMatrix(out,F);
        fprintf(out,"\n");
        Matrix G = diff(A,A);
        fprintf(out,"%s","A-A =\n");
        printMatrix(out,G);
        fprintf(out,"\n");
        Matrix H = transpose(A);
        fprintf(out,"%s","Transpose(A) = \n");
        printMatrix(out,H);
        fprintf(out,"\n");
        Matrix I = product(A,B);
        fprintf(out,"%s","A*B =\n");
        printMatrix(out,I);
        fprintf(out,"\n");
        Matrix J = product(B,B);
        fprintf(out,"%s","B*B =\n");
        printMatrix(out,J);
        fprintf(out,"\n");
	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&C);
	freeMatrix(&D);
	freeMatrix(&E);
	freeMatrix(&F);
	freeMatrix(&G);
	freeMatrix(&H);
	freeMatrix(&I);
	freeMatrix(&J);
   fclose(infile);
   fclose(out);
   return 0;
}

