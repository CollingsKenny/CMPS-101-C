// Kenneth Collings
// Keacolli
// PA4
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"



//Private Graph Object
typedef struct GraphObj{
	int order;	// # of vertices
	int size;	// # of edges
	int source;	// label of the vertex that was most recently used as source for the BFS

	List * neighbors;
	int * colors;
	int * parents;
	int * distance;
} GraphObj;


/***	Constructors-Destructors ***/
Graph newGraph(int n) {
	Graph G;
	G = malloc(sizeof(GraphObj));
	G->order = n;
	G->size = 0;
	G->source = NIL;

	G->neighbors = (List*) malloc((n+1) * sizeof(List));
	G->colors = (int*) malloc((n+1) * sizeof(int));
	G->parents = (int*) malloc((n+1) * sizeof(int));
	G->distance = (int*) malloc((n+1) * sizeof(int));

	//init neighbors
	for(int i = 1; i <= n; i++) {
		G->neighbors[i] = newList();
	}
	return G;
}
void freeGraph(Graph * pG) {
    if(pG!=NULL && *pG!=NULL) {
       Graph G = *pG;
    	for(int i = 1; i <= getOrder(*pG); i++) {
    	  freeList(&(G->neighbors[i]));
       }
       free(G->neighbors);
       free(G->colors);
       free(G->parents);
       free(G->distance);


       free(*pG);
       *pG = NULL;
    }
}


/***	Access functions ***/
int getOrder(Graph G) { //number of vertices
	return G->order;
}
int getSize(Graph G) { //number of edges
	return G->size;
}
int getSource(Graph G) {
	return G->source;
}
int getParent(Graph G, int u) {
	if(!(1 <= u && u <= getOrder(G))) {
		printf("Graph Error: getParent() called with u out of bounds\n");
		exit(1);
	}
	if(getSource(G) == NIL)
		return NIL;
	return G->parents[u];
}
int getDist(Graph G, int u) {
	if(!(1 <= u && u <= getOrder(G))) {
		printf("Graph Error: getDist() called with u out of bounds\n");
		exit(1);
	}
	if(getSource(G) == NIL)
		return INF;
	return G->distance[u];
}
void getPath(List L, Graph G, int u) {
	if(!(1 <= u && u <= getOrder(G))) {
		printf("Graph Error: getPath() called with u out of bounds\n");
		exit(1);
	}
	if(getSource(G) == NIL) {
		printf("Graph Error: getPath() called with null source\n");
		exit(1);
	}

	if( u == G->source) {
		append(L, u);
	}
	else if( getParent(G, u) == NIL) {
		append(L, NIL);
	}
	else {
		getPath(L, G, getParent(G, u));
		append(L, u);
	}
}
void makeNull(Graph G) {
	for(int i = 1; i <= getOrder(G); i++) {
		clear(G->neighbors[i]);
	}
}

void addArcHelper(Graph G, int u, int v) {
	List l = G->neighbors[u];

	if(length(l) == 0) {	//if list is empty, place arc
		append(l,v);
	}
	else {
		moveFront(l);
		while(v > get(l) && index(l) >= 0) { 	//while cursor is less than v, and cursor is still in bounds
			moveNext(l);
		}
		if(index(l) < 0)	//if the cursor is out of bounds
			append(l, v);		// place the arc as the last in the list
		else
			insertBefore(l,v);
	}
}
void addEdge(Graph G, int u, int v) {
	if(!(1 <= u && u <= getOrder(G))) {
			printf("Graph Error: addEdge() called with u out of bounds\n");
			exit(1);
	}
	if(!(1 <= u && u <= getOrder(G))) {
			printf("Graph Error: addEdge() called with v out of bounds\n");
			exit(1);
	}
	addArcHelper(G, u, v);
	addArcHelper(G, v, u);
	G->size++;
}
void addArc(Graph G, int u, int v) {
	if(!(1 <= u && u <= getOrder(G))) {
			printf("Graph Error: addArc() called with u out of bounds\n");
			exit(1);
	}
	if(!(1 <= u && u <= getOrder(G))) {
			printf("Graph Error: addArc() called with v out of bounds\n");
			exit(1);
	}
	addArcHelper(G, u, v);
	G->size++;
}
void BFS(Graph G, int s) {
	G->source = s;
	for(int i = 1; i <= getOrder(G); i++) {
		if(i != s) {
			G->colors[i] = 0;
			G->distance[i] = INF;
			G->parents[i] = NIL;
		}
	}
	G->colors[s] = 1;
	G->distance[s] = 0;
	G->parents[s] = NIL;
	List Q = newList();
	append(Q, s);
	while(length(Q) > 0) {
		int u = front(Q); 		// u = DEQUEUE(Q)
		deleteFront(Q);

		List L = G->neighbors[u];
		moveFront(L);
		while(index(L) >= 0) {
			int v = get(L);
			if(G->colors[v] == 0) {
				G->colors[v] = 1;
				G->distance[v] = G->distance[u] + 1;
				G->parents[v] = u;
				append(Q, v);		// ENQUEUE
			}
			moveNext(L);
		}
		G->colors[u] = 2;
	}
	freeList(&Q);
}


/*** Other operations ***/
void printGraph(FILE* out, Graph G) {
	for(int i = 1; i <= getOrder(G); i++) {
		fprintf(out, "%i: ", i);
		printList(out, G->neighbors[i]);
		fprintf(out, "\n");
	}
}
