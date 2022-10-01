/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#3
* Graph.c 
* Graph ADT 
*********************************************************************************/

#include "Graph.h"

Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->neighbors=(List*)calloc((n+1),sizeof(List*));
	G->color=malloc((n+1)*sizeof(char));
	G->parent=malloc((n+1)*sizeof(int));
	G->discover=malloc((n+1)*sizeof(int));
	G->finish=malloc((n+1)*sizeof(int));
	G->order=n;
	G->size=0;
	for(int i=1;i<=n;i++){
		G->neighbors[i]=newList();
		G->color[i]='w';
		G->parent[i]=NIL;
		G->discover[i]=UNDEF;
		G->finish[i]=UNDEF;
	}
	return G;
}
void freeGraph(Graph* pG){
	for(int i = 1; i<=getOrder(*pG);i++){
		freeList(&(*pG)->neighbors[i]);
	}
        free((*pG)->color);
	free((*pG)->parent);
	free((*pG)->discover);
	free((*pG)->neighbors);
	free((*pG)->finish);	
	free(*pG);
}
int getOrder(Graph G){
	return G->order;
}
int getSize(Graph G){
	return G->size;
}
int getParent(Graph G, int u){
	return G->parent[u];
}
int getDiscover(Graph G, int u){
	return G->discover[u];
}
int getFinish(Graph G, int u){
	return G->finish[u];
}
void addEdge(Graph G, int u, int v){
	addArc(G,u,v);
	addArc(G,v,u);
	G->size--;
}
void addArc(Graph G, int u, int v){
	if(length(G->neighbors[u])==0)
		append(G->neighbors[u],v);
	else{
		bool boo=false;
		moveFront(G->neighbors[u]);
		while(v>=get(G->neighbors[u])){
			if(get(G->neighbors[u])==v)
				return;
			moveNext(G->neighbors[u]);
			if(index(G->neighbors[u])==-1){
				boo=true;
				break;
			}
        	}
		if(boo)
			append(G->neighbors[u],v);
		else
        		insertBefore(G->neighbors[u],v);
	}
	G->size++;
}
int Visit(Graph G,int x, int time, List S){
	time++;
        G->discover[x]=time;
        G->color[x]='g';
        moveFront(G->neighbors[x]);
        int y = get(G->neighbors[x]); 
        while(y!=-1){
                moveNext(G->neighbors[x]);
                if(G->color[y]=='w'){
                        G->parent[y]=x;
                        time = Visit(G,y,time, S);
                }
                y=get(G->neighbors[x]);
        }
        G->color[x]='b';
	time++;
        G->finish[x]=time;
	prepend(S,x);
        return time;
}
void DFS(Graph G, List S){
	for(int i=1;i<=G->order;i++){
		G->color[i]='w';
		G->parent[i]=NIL;
	}
	List T=newList();
	int n = length(S);
	int time = 0;
	if(length(S)!=G->order){
		puts("Length of S not equal to n!");
		return;
	}
	moveFront(S);
	int x = get(S);
	while(x!=-1){
		moveNext(S);
		deleteFront(S);
		if(G->color[x]=='w'){
			time = Visit(G,x,time,T);
			n++;
		}
		x = get(S);
	}
	moveFront(T);
	int z = get(T);
	while(z!=-1){
		moveNext(T);
		append(S,z);
		z=get(T);
	}
	freeList(&T);
}
Graph transpose(Graph G){
	Graph out = newGraph(G->order);
	for(int i =1;i<=G->order;i++){
		moveFront(G->neighbors[i]);
		int x = get(G->neighbors[i]);
		while(x!=-1){
			moveNext(G->neighbors[i]);
			append(out->neighbors[x],i);
			x = get(G->neighbors[i]);
			out->size++;
		}
	}
	return out;
}
Graph copyGraph(Graph G){
	Graph out = newGraph(G->order);
	for(int i = 1; i<=G->order;i++){
		out->neighbors[i]=copyList(G->neighbors[i]);
	}
	return out;
}		
void printGraph(FILE* out, Graph G){
	for(int i=1;i<=G->order;i++){
		fprintf(out, "%d: ", i);
                printList(out,G->neighbors[i]);
        }
}

