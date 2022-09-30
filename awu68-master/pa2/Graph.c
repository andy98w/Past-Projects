/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#2 
* Graph.c 
* Graph ADT 
*********************************************************************************/

#include "Graph.h"

Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->neighbors=(List*)calloc((n+1),sizeof(List*));
	G->color=malloc((n+1)*sizeof(char));
	G->parent=malloc((n+1)*sizeof(int));
	G->distance=malloc((n+1)*sizeof(int));
	G->order=n;
	G->size=0;
	for(int i=1;i<=n;i++){
		G->neighbors[i]=newList();
		G->color[i]='w';
		G->parent[i]=NIL;
		G->distance[i]=INF;
	}
	G->label=0;
	return G;
}
void freeGraph(Graph* pG){
	for(int i = 1; i<=getOrder(*pG);i++){
		freeList(&(*pG)->neighbors[i]);
	}
        free((*pG)->color);
	free((*pG)->parent);
	free((*pG)->distance);
	free((*pG)->neighbors);	
	free(*pG);
}
int getOrder(Graph G){
	return G->order;
}
int getSize(Graph G){
	return G->size;
}
int getSource(Graph G){
	if(G->label!=0)
		return G->label;
	else
		return NIL;
}
int getParent(Graph G, int u){
	if(getSource(G)!=NIL)
		return G->parent[u];
	else
		return NIL;
}
int getDist(Graph G, int u){
	if(getSource(G)!=NIL)
		return G->distance[u];
	else
		return INF;
}
void getPath(List L, Graph G, int u){
	if(u==G->label){
		append(L,u);
		return;
	}
	else if(G->parent[u]==NIL){
		append(L,NIL);
		return;
	}
	else{
		getPath(L,G,G->parent[u]);
		append(L,u);
	}
}
void makeNull(Graph G){
        for(int i=1;i<=G->order;i++){
		freeList(&(G->neighbors[i]));
                G->neighbors[i]=newList();
                G->color[i]='w';
                G->parent[i]=NIL;
                G->distance[i]=INF;
        }
	G->order=0;
	G->size=0;
        G->label=0;
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
void BFS(Graph G, int s){
	for(int i=1;i<=G->order;i++){
		G->color[i]='w';
		G->distance[i]=INF;
		G->parent[i]=NIL;
	}
	G->color[s]='g';
	G->distance[s]=0;
	G->parent[s]=NIL;
	List Q=newList();
	append(Q,s);
	while(!isEmpty(Q)){
		int x = front(Q);
		deleteFront(Q);
		moveFront(G->neighbors[x]);
		int y=get(G->neighbors[x]);
		while(y!=-1){
			moveNext(G->neighbors[x]);
			if(G->color[y]=='w'){
				G->color[y]='g';
				G->distance[y]=G->distance[x]+1;
				G->parent[y]=x;
				append(Q,y);
			}
			y=get(G->neighbors[x]);
		}
		G->color[x]='b';
	}
	G->label=s;
	freeList(&Q);
}
void printGraph(FILE* out, Graph G){
	for(int i=1;i<=G->order;i++){
		fprintf(out, "%d: ", i);
                printList(out,G->neighbors[i]);
        }
}
