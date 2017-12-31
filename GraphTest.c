// Kenneth Collings
// keacolli
// PA5
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){

	Graph G = newGraph(5);
	Graph H;

	addArc(G, 1, 2);
	addArc(G, 1, 3);
	addArc(G, 2, 4);
	addArc(G, 2, 5);
	addArc(G, 3, 4);
	addArc(G, 4, 4);

	printf("%i %i", getOrder(G), getSize(G));




	List S = newList();
	for(int i = 1; i <= getOrder(G); i++) append(S, i);
	DFS(G, S);

	for(int i = 1; i <= getOrder(G); i++){
	      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
	   }

	H = transpose(G);
	printGraph(stdout, H);
	DFS(H, S);
	printf("\n");
	for(int i = 1; i <= getOrder(G); i++){
	      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(H, i), getFinish(H, i), getParent(H, i));
	   }


	makeNull(G);
	printf("\n");
	printGraph(stdout, G);
	freeGraph(&G);
	freeGraph(&H);
	freeList(&S);

	return 0;
}
