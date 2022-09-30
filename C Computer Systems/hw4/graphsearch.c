#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "graphsearch.h"
#define MAX_GRAPH_SIZE 128

LLint *add_to_set(LLint *set, int val) {
  LLint *newfront = calloc(1, sizeof(LLint));
  newfront->val = val;
  newfront->next = set;

  return newfront;
}
bool set_contains(LLint *set, int val) {
  if (set == NULL) {
    return false;
  } else if (set->val == val) {
    return true;
  } else {
    return set_contains(set->next, val);
  }
}

LLPath *enqueue_path(LLPath *q, Path path) {
  LLPath *newpath = calloc(1, sizeof(LLPath));
  newpath->val = path;

  if (q == NULL) {
    return newpath;
  }
  LLPath *cur = q;
  while(cur->next != NULL) {
    cur = cur->next;
  }
  cur->next = newpath;
  return q;
}

bool dequeue_path(LLPath **q, Path *ret) {
  if (*q == NULL) {
    return false;
  }

  *ret = (*q)->val;
  
  LLPath *freethis = *q;
  *q = (*q)->next;
  free(freethis);
  return true;
}

LLint *enqueue(LLint *q, int val) {
  LLint *newnode = calloc(1, sizeof(LLint));
  newnode->val = val;

  if (q == NULL) {
    return newnode;
  }

  LLint *cur = q;
  while(cur->next != NULL) {
    cur = cur->next;
  }
  cur->next = newnode;
  return q;
}

bool dequeue(LLint **q, int *ret) {
  if (*q == NULL) {
    return false;
  }

  *ret = (*q)->val;
  
  LLint *freethis = *q;
  *q = (*q)->next;
  free(freethis);
  return true;
}

Graph *graph_create(int vertices) {
  Graph *g = (Graph *)malloc(sizeof(Graph));
  g->vertices = vertices;
  g->matrix = (int **)calloc(vertices, sizeof(int*));
  for (int i=0; i < vertices; i++) {
    g->matrix[i] = (int *)calloc(vertices, sizeof(int));
  }
  return g;
}

void graph_add_edge(Graph *g, int i, int j) {
  g->matrix[i][j] = 1;
}


bool graph_has_edge(Graph *g, int i, int j) {
  return g->matrix[i][j];
}

Path path_extend(Path path, int new_vertex) {
  Path out;
  out.steps = path.steps;

  for (int i=0; i < path.steps; i++) {
    out.vertices_visited[i] = path.vertices_visited[i];
  }
  out.vertices_visited[path.steps] = new_vertex;
  out.steps += 1;
  return out;
}

void print_path(Path path) {
  if (path.steps == 0) {
    printf("(empty path)");
  }
  for (int i=0; i < path.steps; i++) {
    printf("%s%d",(i == 0) ? "" : " -> ",path.vertices_visited[i]);
  }
  puts("");
}
struct Stack {
    int top;
    int* array;
};
struct Stack* createStack(){
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->array = (int*)malloc(100* sizeof(int));
    return stack;
}

int isEmpty(struct Stack* stack){
    if(stack->top == -1)
      return 1;
    else
      return 0;
}
void push(struct Stack* stack, int item){
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack){
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}
Path graph_find_path_bfs(Graph *g, int i, int j) {
    struct Stack *to_visit = createStack();
    push(to_visit, i);
    LLint *visited = NULL;
    Path ret;
    ret.steps = 0;
    ret = path_extend(ret, i);
    while(isEmpty(to_visit)==0) {
        int current = pop(to_visit);
        if (current == j) {
            ret = path_extend(ret, current);
	    struct Stack *delete = to_visit;
	    int *delete_arr = to_visit->array;
	    free(delete_arr);
	    free(delete);
	    LLint *remove;
	    while (visited!=NULL){
		    remove = visited;
		    visited = visited->next;
		    free(remove);
	    }
            return ret;
            }
        visited = add_to_set(visited, current);
        for(int neighbor = 0; neighbor < g->vertices; neighbor++) {
            if (graph_has_edge(g, current, neighbor) && !set_contains(visited, neighbor)) {
                if(ret.vertices_visited[ret.steps-1]!=current){
                    ret = path_extend(ret, current);
                }
                push(to_visit, neighbor);
            }
        }
    }
    struct Stack *delete = to_visit;
    int *delete_arr = to_visit->array;
    free(delete_arr);
    free(delete);
    LLint *remove;
    while(visited!=NULL){
	    remove = visited;
	    visited = visited->next;
	    free(remove);
    }
    Path empty = {0, {0}};
    return empty;
}

Path graph_find_path_dfs(Graph *g, int i, int j) {
    LLint *visited = NULL;
    LLint *to_visit = NULL;
    to_visit = enqueue(to_visit, i);
    Path ret;
    ret.steps = 0;
    ret = path_extend(ret, i);
    while(to_visit != NULL) {
        int current;
        dequeue(&to_visit, &current);
        if (current == j) {
            ret = path_extend(ret, current);
	    LLint *remove;
	    while(visited!=NULL){
		    remove = visited;
		    visited = visited->next;
		    free(remove);
	    }
	    LLint *delete_list2 = to_visit;
	    free(delete_list2);
            return ret;
            }
        visited = add_to_set(visited, current);
        for(int neighbor = 0; neighbor < g->vertices; neighbor++) {
            if (graph_has_edge(g, current, neighbor) && !set_contains(visited, neighbor)) {
                to_visit = enqueue(to_visit, neighbor);
                if(ret.vertices_visited[ret.steps-1]!=current){
                    ret = path_extend(ret, current);
                }
            }
        }
    }
    LLint *remove;
    while(visited!=NULL){
	    remove = visited;
	    visited = visited->next;
	    free(remove);
    }
    LLint *delete_list2 = to_visit;
    free(delete_list2);
    Path empty = {0, {0}};
    return empty;
}

