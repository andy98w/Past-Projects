/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#2 
* GraphTest.c
* Testing for Graph ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   List  L = newList(); 
   List J = newList();
   List K = newList();
   List M = newList();
   Graph G = newGraph(20);
   for(int i=1; i<19; i++){
      addEdge(G, i, i+2);
      if( i<=10  ) addEdge(G, i, i+7);
   }
   addEdge(G, 2, 4);
   addEdge(G, 4, 6);
   addEdge(G, 6, 9);
   addArc(G, 6, 8);
   addArc(G, 1, 20);
   printGraph(stdout, G);
   BFS(G,1);
   getPath(L, G, 20);
   printList(stdout,L);
   BFS(G,20);
   getPath(J, G, 19);
   printList(stdout,J);
   BFS(G, 16);
   getPath(K,G,17);
   printList(stdout,K);
   BFS(G,17);
   getPath(M,G,19);
   printList(stdout,M);
   printf("%d\n",getOrder(G));
   printf("%d\n",getSize(G));
   printf("%d\n",getSource(G));
   printf("%d\n",getOrder(G));
   printf("%d\n",getDist(G,19));
   printf("%d\n",getSource(G));
   makeNull(G);
   printf("%d\n",getOrder(G));
   printf("%d\n",getSize(G));
   printf("%d\n",getSource(G));
   printf("%d\n",getOrder(G));
   printf("%d\n",getDist(G,19));
   printf("%d\n",getSource(G));
   printGraph(stdout,G);
   return(0);
}
