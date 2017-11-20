// Kenneth Collings
// keacolli
// PA4
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){
	Graph G = newGraph(5);
	List D = newList();

	addEdge(G, 1, 2);
	addEdge(G, 1, 3);
	addEdge(G, 2, 4);
	addEdge(G, 2, 5);
	addEdge(G, 3, 4);
	addEdge(G, 4, 4);

	printf("%i %i", getOrder(G), getSize(G));

	BFS(G, 4);

	getPath(D, G, 2);

	printList(stdout, D);
	BFS(G, 1);

	getPath(D, G, 4);
	printf("\n\n");
	printList(stdout, D);
	printf("\n\n\n");
	printGraph(stdout, G);


	makeNull(G);
	printf("\n");
	printGraph(stdout, G);

}
