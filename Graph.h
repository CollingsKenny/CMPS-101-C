// Kenneth Collings
// Keacolli
// PA5
#include "List.h"

#ifndef GRAPH_H_
#define GRAPH_H_
#define INF		-1
#define NIL		0
#define UNDEF	-1

// Exported type --------------------------------------------------------------
typedef struct GraphObj* Graph;


/* Constructors-Destructors */
Graph newGraph(int n);
void freeGraph(Graph* pG);

/* Access functions */
int getOrder(Graph G);
int getSize(Graph G);

int getSource(Graph G);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

int getParent(Graph G, int u);		/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u);	/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u);		/* Pre: 1<=u<=n=getOrder(G) */

/* Manipulation procedures */
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);

void BFS(Graph G, int s);

void DFS(Graph G, List S);			/* Pre: length(S)==getOrder(G) */

/* Other Functions */
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);


#endif /* GRAPH_H_ */
