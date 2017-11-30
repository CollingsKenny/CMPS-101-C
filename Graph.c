// Kenneth Collings
// Keacolli
// PA5
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"



//Private Graph Object
typedef struct GraphObj{
	int order;	// # of vertices
	int size;	// # of edges

	List * neighbors;
	int * colors;
	int * parents;

	//BFS
	int source;
	int * distance;

	//DFS
	int * finish;
	int * discover;
} GraphObj;


/***	Constructors-Destructors ***/
Graph newGraph(int n) {
	Graph G;
	G = malloc(sizeof(GraphObj));
	G->order = n;
	G->size = 0;

	G->neighbors = (List*) malloc((n+1) * sizeof(List));
	G->colors = (int*) malloc((n+1) * sizeof(int));
	G->parents = (int*) malloc((n+1) * sizeof(int));
	//BFS
	G->source = NIL;
	G->distance = (int*) malloc((n+1) * sizeof(int));
	//DFS
	G->discover = (int*) malloc((n+1) * sizeof(int));
	G->finish = (int*) malloc((n+1) * sizeof(int));

	//init neighbors
	for(int i = 1; i <= n; i++) {
		G->neighbors[i] = newList();
		G->parents[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;

	}
	return G;
}
void freeGraph(Graph * pG) {
    if(pG!=NULL && *pG!=NULL) {
       Graph G = *pG;
    	for(int i = 1; i <= getOrder(*pG); i++) {
    	  freeList(&(G->neighbors[i]));
       }
       free(G->distance);

       free(G->neighbors);
       free(G->colors);
       free(G->parents);
       free(G->discover);
       free(G->finish);

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

	if(u == G->source) {
		append(L, u);
	}
	else if(getParent(G, u) == NIL) {
		append(L, NIL);
	}
	else {
		getPath(L, G, getParent(G, u));
		append(L, u);
	}
}

int getDiscover(Graph G, int u) {
	if(!(1 <= u && u <= getOrder(G))) {
		printf("Graph Error: getDiscover() called with u out of bounds\n");
		exit(1);
	}

	return G->discover[u];
}
void makeNull(Graph G) {
	for(int i = 1; i <= getOrder(G); i++) {
		clear(G->neighbors[i]);
	}
}
int getFinish(Graph G, int u) {
	if(!(1 <= u && u <= getOrder(G))) {
		printf("Graph Error: getDiscover() called with u out of bounds\n");
		exit(1);
	}

	return G->finish[u];
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
void DFSVisit(Graph G, int u, int * time, List S) {
	G->discover[u] = ++(*time);
	G->colors[u] = 1;
	List l = G->neighbors[u];
	moveFront(l);
	while(index(l) >= 0) {
		int v = get(l);
		if(G->colors[v] == 0) {
			G->parents[v] = u;
			DFSVisit(G, v, time, S);
		}
		moveNext(l);
	}
	G->colors[u] = 2;
	G->finish[u] = ++(*time);
	insertAfter(S, u);

}
void DFS(Graph G, List S) {
	if (length(S) != getOrder(G)) {
		printf("Graph Error: DFS() called with invalid list s\n");
		exit(1);
	}
	int time = 0;
	for(int i = 1; i <= getOrder(G); i++) {
		G->colors[i] = 0;
		G->parents[i] = NIL;
	}
	append(S, UNDEF);
	moveBack(S);
	for(int i = 1; i <= getOrder(G); i++) {
		int u = front(S);
		deleteFront(S);
		if(G->colors[u] == 0) {
			DFSVisit(G, u, &time, S);
		}
	}
	deleteFront(S);
}
/*** Other operations ***/
Graph transpose(Graph G) {
	Graph H = newGraph(getOrder(G));
	for(int u = 1; u <= getOrder(G); u++) {
		List l = G->neighbors[u];
		moveFront(l);
		while(index(l) >= 0) {
			int v = get(l);
			addArc(H, v, u);
			moveNext(l);
		}
	}
	return H;
}

Graph copyGraph(Graph G) {
	Graph H = newGraph(getOrder(G));
	for(int u = 1; u <= getOrder(G); u++) {
		List l = G->neighbors[u];
		moveFront(l);
		while(index(l) >= 0) {
			int v = get(l);
			addArc(H, u, v);
			moveNext(l);
		}
	}
	return H;
}
void printGraph(FILE* out, Graph G) {
	for(int i = 1; i <= getOrder(G); i++) {
		fprintf(out, "%i: ", i);
		printList(out, G->neighbors[i]);
		fprintf(out, "\n");
	}
}
