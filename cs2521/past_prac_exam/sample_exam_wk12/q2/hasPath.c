
/* hasPath.c 
   Written by Ashesh Mahidadia, October 2017
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"



/* 
    You will submit only this one file.

    Implement the function "hasPath" below. Read the exam paper for 
    detailed specification and description of your task.  

    - You can add helper functions in this file, if required.  

    - DO NOT modify code in the file BSTree.h . 
    - DO NOT add "main" function in this file. 
*/


int *visited;  // array of visited

/*static int dfs(Graph g, Vertex src, Vertex dest) {
    int i;
    for (i =0; i < g->nV; i++) {
        if (i == src) continue;
        if (g->edges[src][i] == 1 && visited[i] == -1) {
            if (i == dest) return 1;
            visited[i] = src;
            if (dfs(g, i, dest) == 1) {
                return 1;
            }
        }
    }
    return 0;
}*/
static void visit(Graph g, Vertex src) {
    //visited[src] = 1;
    int i;
    for (i = 0; i < g->nV; i++) {
        if (i == src) continue;
        if (visited[i] == -1 && g->edges[src][i] == 1) {
            visited[i] = 1;
            visit(g, i);
        }
    }
}


int hasPath(Graph g, Vertex src, Vertex dest)
{

	// Implement this function, 
	// also change the return value below!
	/*method 1
    visited = malloc(sizeof(int) * g->nV);
    int i;
    for (i = 0; i < g->nV; i++) visited[i] = -1;

    if (dfs(g, src, dest) == 1) {
        free(visited);
        return 1;
    }*/
    visited = malloc(g->nV * sizeof(int));
    int i;
    for (i = 0; i < g->nV; i++) {
        visited[i] = -1;
    }
    visited[src] = 1;
    visit(g, src);
    /*int j;
    printf("#V = %d\n", g->nV);
    for (j = 0; j< g->nV; j++) printf("%d\n", visited[j]); */
    if (visited[dest] != -1) {
        free(visited);
        return 1;
    }

    free(visited);
    return 0;
}


