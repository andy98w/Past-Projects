/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#3 
* FindComponents.c
* Main File for Graph ADT
*********************************************************************************/

#include "Graph.h"
#define SIZE 10
int main(int argc, char **argv){
	if(argc!=3){
		fprintf(stderr, "usage: ./FindComponents <inputfile> <outputfile>");
		exit(1);
	}
	FILE *infile=fopen(argv[1],"r");
	char buf[SIZE];
	int line = 0;
	int n, i, j;
	Graph G;
	while((fgets(buf,SIZE,infile)!=NULL)){
		if(line==0){
			sscanf(buf,"%d ",&n);
			G=newGraph(n);
			line++;
		}
		else if(line>=1){
			sscanf(buf,"%d %d ", &i, &j);
			if(i==0&&j==0)
				break;
			addArc(G,i,j);
		}
	}
	FILE *out=fopen(argv[2],"w");
		fprintf(out,"%s\n","Adjacency list representation of G:");
	printGraph(out,G);
	List S = newList();
	for(i=1;i<=n;i++){
		append(S,i);
	}
	DFS(G,S);
   Graph H;
   H = transpose(G);
   freeGraph(&G);
   DFS(H,S);
   int count=0;
   for(int i=1;i<=n;i++){
	   if(getParent(H,i)==NIL)
		   count++;
   }
   fprintf(out,"\n");
   fprintf(out, "%s %d %s\n", "G contains", count, "strongly connected components:");
   moveBack(S);
   int count2=0;
   int count3=0;
   bool boo = true;
   while(get(S)!=-1){
	   boo = true;
	if(getParent(H,get(S))==0){
		count2++;
		fprintf(out, "%s%d: %d","Component ",count2,get(S));
		count3++;
		moveNext(S);
		while(get(S)!=-1){
			fprintf(out, " %d", get(S));
			moveNext(S);
			count3++;
		}
		for(int i=0;i<count3;i++)
			deleteBack(S);
		fprintf(out,"\n");
		moveBack(S);
		count3=0;
		boo = false;
	}
	if(boo){
		movePrev(S);
	}
   }
   fclose(infile);
   fclose(out);
   freeList(&S);
   freeGraph(&H);
}


