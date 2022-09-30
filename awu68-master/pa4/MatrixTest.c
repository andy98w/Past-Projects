/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#4
* MatrixTest.c
* Test File for Matrix ADT
*********************************************************************************/
#include"Matrix.h"
     
int main(){
   int n=100;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, E, F, G, H, I, J;
   changeEntry(A, 100,1,10); 
   changeEntry(A, 1,1,20);
   changeEntry(A, 1,1,5);
   printMatrix(stdout,A);
   changeEntry(A, 1,2,40); 
   changeEntry(A, 1,3,60);
   changeEntry(A, 2,1,80);
   changeEntry(A, 2,2,100);
   changeEntry(A, 2,3,50); 
   changeEntry(A, 3,1,30);
   changeEntry(A, 3,2,111); 
   changeEntry(A, 3,3,40);
   changeEntry(B, 1,1,60); 
   changeEntry(B, 1,2,99);
   changeEntry(B, 1,3,100); 
   changeEntry(B, 2,1,100);
   changeEntry(B, 2,2,800); 
   changeEntry(B, 2,3,100);
   changeEntry(B, 3,1,995); 
   changeEntry(B, 3,2,129);
   changeEntry(B, 3,3,219);
   C = scalarMult(0.1, A);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");
   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");
   E = sum(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");
   F = diff(A, B);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");
   G = transpose(A);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");
   H = transpose(B);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");
   I = product(A, B);
   printf("%d\n", NNZ(I));
   printMatrix(stdout, I);
   printf("\n");
   J = copy(A);
   printf("%d\n", NNZ(J));
   printMatrix(stdout, J);
   printf("\n");
   int i = equals(J,A);
   printf("%d\n",i);
   printf("%d\n",size(J));
   makeZero(B);
   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
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
   return 0;
}
