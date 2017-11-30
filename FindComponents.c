// Kenneth Collings
// Keacolli
// PA5


#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include <string.h>
#include "List.h"

#define MAX_LEN 1000


//based off of fileIO example
//https://classes.soe.ucsc.edu/cmps101/Fall17/Examples/C/FileIO/FileIO.c
int main(int argc, char * argv[]){
    FILE *in, *out;
    char line[MAX_LEN];
    char *token;

    int n = 0;
    Graph G, H;
    List S;

    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in == NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if( out == NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }


//Read Input File and assemble a graph object G
    //set n
    if(fgets(line, MAX_LEN, in) != NULL) {
    	n = atoi(line);
    }
    G = newGraph(n);
    //set edges
    while(fgets(line, MAX_LEN, in) != NULL) {
    	int u, v;

    	token = strtok(line, " ");

    	u = atoi(token);
    	token = strtok(NULL, " ");
    	v = atoi(token);
    	if( u == 0 && v == 0)
    		break;
    	addArc(G, u, v);
    }
//Print the adjacency list of G to output
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

//Run DFS on G, and G' by decreasing finish times
    H = transpose(G);
    S = newList();
    int connected = 0;
    for(int i = 1; i <= getOrder(G); i++) append(S, i);

    DFS(G, S);
    DFS(H, S);

    printGraph(stdout, H);
    printList(stdout, S);
    List P = newList();


    for(int i = 1; i <= getOrder(H); i++) {
       	if(getParent(H, i) == NIL) {
       		connected++;
       	}
    }
    fprintf(out, "\nG contains %i strongly connected components:", connected);

    moveBack(S);
    for(int i = 1; i <= connected; i++) {
    	fprintf(out, "\nComponent %i: ", i);

    	while (getParent(H, get(S)) != NIL) {
    		prepend(P, get(S));
    		movePrev(S);
    	}
		prepend(P, get(S));
		movePrev(S);

		printList(out, P);
		clear(P);
    }

//close files and free the memory
    fclose(in);
    fclose(out);

    freeGraph(&G);
    freeGraph(&H);
    freeList(&S);
    freeList(&P);

    return(0);
}
