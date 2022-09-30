/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#2 
* FindPath.c
* Main File for Graph ADT
*********************************************************************************/

#include "Graph.h"
#define SIZE 10
int main(int argc, char **argv){
	if(argc!=3){
		fprintf(stderr, "usage: ./FindPath <inputfile> <outputfile>");
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
			addEdge(G,i,j);
		}
	}
	FILE *out=fopen(argv[2],"w");
	printGraph(out,G);
	while(fgets(buf,SIZE,infile)!=NULL){
		int i,j;
		sscanf(buf,"%d %d", &i, &j);
		if(i==0&&j==0)
                	break;
		BFS(G,i);
		List L = newList();
		getPath(L,G,j);
		fputs("\n",out);
		if(front(L)==-1){
			fprintf(out,"%s%d%s%d%s\n","The distance from ",i," to ",j," is infinity");
			fprintf(out,"%s%d%s%d%s","No ",i,"-",j," path exists");
			fputs("\n",out);
		}
		else{
			fprintf(out,"%s%d%s%d%s%d\n","The distance from ",i," to ",j," is ",length(L)-1);
			fprintf(out,"%s%d%s%d%s","A shortest ",i,"-",j," path is: " );
			printList(out,L);
		}
		freeList(&L);
	}
	fclose(infile);
	fclose(out);
	freeGraph(&G);
}

