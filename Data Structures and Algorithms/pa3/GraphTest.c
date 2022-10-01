/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#3 
* GraphTest.c
* Testing for Graph ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   List  L = newList(); 
   Graph G = newGraph(5);
   addArc(G, 1, 2);
   addArc(G, 2, 3);
   addArc(G, 3, 1);
   addArc(G, 3, 4);
   addArc(G, 4, 5);
   addArc(G, 5, 4);
   addArc(G, 3, 3);
   printGraph(stdout, G);
   for(int i =1;i<=5;i++)
	   append(L,i);
   DFS(G,L);
   printList(stdout,L);
   Graph H = transpose(G);
   freeGraph(&G);
   DFS(H,L);
   printList(stdout,L);
      fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(int i=1; i<=5; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(H, i), getFinish(H, i), getParent(H, i));
   }
   printf("%d\n",getOrder(H));
   printf("%d\n",getSize(H));
   fprintf(stdout,"\n");
   moveBack(L);
   int count2=0;
   int count3=0;
   bool boo = true;
   while(get(L)!=-1){
           boo = true;
        if(getParent(H,get(L))==0){
                count2++;
                fprintf(stdout, "%s%d: %d","Component ",count2,get(L));
                count3++;
                moveNext(L);
                while(get(L)!=-1){
                        fprintf(stdout, " %d", get(L));
                        moveNext(L);
                        count3++;
                }
                for(int i=0;i<count3;i++)
                        deleteBack(L);
                fprintf(stdout,"\n");
                moveBack(L);
                count3=0;
                boo = false;
        }
        if(boo){
                movePrev(L);
        }
   }

   freeList(&L);
   freeGraph(&H);

   return(0);
}

