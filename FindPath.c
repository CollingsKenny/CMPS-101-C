// Kenneth Collings
// Keacolli
// PA4


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
    Graph G;
    List P;

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


//Part 1
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
    	addEdge(G, u, v);
    }
    printGraph(out, G);
//Part 2
    P = newList();
    while(fgets(line, MAX_LEN, in) != NULL) {
    	int s, d;
    	token = strtok(line, " ");

    	s = atoi(token);
    	token = strtok(NULL, " ");
    	d = atoi(token);
    	if( s == 0 && d == 0)
    		break;
    	clear(P);
    	BFS(G, s);
    	int disU = getDist(G,d);
    	getPath(P, G, d);
    	fprintf(out, "\n\n");
    	fprintf(out, "The distance from %i to %i is ", s, d);
    	if(disU == INF) {
    		fprintf(out, "infinity\n");
    		fprintf(out, "No %i-%i path exists", s, d);
    	}
    	else {
    		fprintf(out, "%i", disU);
    		fprintf(out, "\nA shortest %i-%i path is: ", s, d);
    		printList(out, P);
    	}
    }

    //close files and free the memory
    fclose(in);
    fclose(out);

    freeGraph(&G);
    freeList(&P);


    return(0);
}
