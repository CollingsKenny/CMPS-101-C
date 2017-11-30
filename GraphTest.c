// Kenneth Collings
// keacolli
// PA5
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


	List S = newList();
	for(int i = 1; i <= getOrder(G); i++) append(S, i);
	DFS(G, S);

	for(int i = 1; i <= getOrder(G); i++){
	      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
	   }

	G = Transpose(G, S);
	printGraph(stdout, G);
	printf("\n");
	for(int i = 1; i <= getOrder(G); i++){
	      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
	   }


	makeNull(G);
	printf("\n");
	printGraph(stdout, G);

	return 0;
}
