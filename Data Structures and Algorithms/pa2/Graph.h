/********************************************************************************* 
* Andrew Wu, awu68 
* 2022 Spring CSE101 PA#2 
* Graph.h
* Header File for Graph ADT
*********************************************************************************/
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "List.h"
#define INF 500000
#define NIL -1
typedef struct GraphObj{
        List *neighbors;
        char *color;
        int *parent;
        int *distance;
        int order;
        int size;
        int label;
}GraphObj;
typedef struct GraphObj* Graph;
/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
