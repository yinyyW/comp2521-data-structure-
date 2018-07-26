// Graph.c ... implementation of Graph ADT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"

// type for small +ve int values
typedef unsigned char bool;


// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	bool **edges; // matrix of booleans
} GraphRep;

// validV ... check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// mkEdge ... create an Edge value
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
	assert(validV(g,v) && validV(g,w));
	Edge e; e.v = v; e.w = w;
	return e;
}

// newGraph ... create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	int i, j;
	bool **e = malloc(nV * sizeof(bool *));
	assert(e != NULL);
	for (i = 0; i < nV; i++) {
		e[i] = malloc(nV * sizeof(bool));
		assert(e[i] != NULL);
		for (j = 0; j < nV; j++)
			e[i][j] = 0;
	}
	Graph g = malloc(sizeof(GraphRep));
	assert(g != NULL);
	g->nV = nV;  g->nE = 0;  g->edges = e;
	return g;
}

// readGraph ... read graph contents from file
static void readError()
{
	fprintf(stderr,"Bad graph data file\n");
	exit(1);
}
Graph readGraph(FILE *in)
{
	Graph g;
	char line[100];
	// get #vertices and create graph
	int nV = 0;
	if (fgets(line,100,in) == NULL) readError();
	if (sscanf(line,"%d",&nV) != 1) readError();
	if (nV < 2) readError();
	g = newGraph(nV);
	// read edge data and add edges
	Vertex v, w;
	while (fgets(line,100,in) != NULL) {
		sscanf(line,"%d-%d",&v,&w);
		insertE(g, mkEdge(g,v,w));
	}
	return g;
}

// showGraph ... display a graph
void showGraph(Graph g)
{
	assert(g != NULL);
	printf("# vertices = %d, # edges = %d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d is connected to",v);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf(" %d",w);
			}
		}
		printf("\n");
	}
}

// insertE ... add a new edge
void  insertE(Graph g, Edge e)
{
	assert(g != NULL);
	assert(validV(g,e.v) && validV(g,e.w));
	if (g->edges[e.v][e.w]) return;
	g->edges[e.v][e.w] = 1;
	g->edges[e.w][e.v] = 1;
	g->nE++;
}

// removeE ... delete an edge
void  removeE(Graph g, Edge e)
{
	assert(g != NULL);
	assert(validV(g,e.v) && validV(g,e.w));
	if (!g->edges[e.v][e.w]) return;
	g->edges[e.v][e.w] = 0;
	g->edges[e.w][e.v] = 0;
	g->nE--;
}
/*
int *ComponentOf;
int cnt;
int unassign;

void dfs(Graph g, Vertex s) {
    ComponentOf[s] = cnt;
    unassign--;
    int i;
    for (i = 0; i < g->nV; i++) {
        if (g->edges[s][i] && ComponentOf[i] == -1) {
            dfs(g, i);
        }
    }
}

// nComponents ... number of connected components
int nComponents(Graph g)
{
    cnt = 0;
    ComponentOf = malloc(sizeof(int) * g->nV);
    int i;
    //all vertices are unassigned
    for(i = 0; i < g->nV; i++) {
        ComponentOf[i] = -1;
    }
    unassign = g->nV;
    while (unassign > 0) {
        //find an unassigned vertex
        int j;
        for (j = 0; j < g->nV; j++) {
            if (ComponentOf[j] == -1) break;
        }
        cnt++;
        //ComponentOf[j] = cnt;
        dfs(g, j);
    }
	return cnt; // remove this line
}*/






























int *componentof;
int assign;
int cnt;

void dfs(Graph g, Vertex s) {
    //assign curr vertex to componentof
    componentof[s] = cnt;
    assign++;
    int i;
    for (i = 0; i < g->nV; i++) {
        if (componentof[i] != -1) continue;
        if (g->edges[s][i]) {
            dfs(g, i);
        }
    }
}


int nComponents(Graph g) {
    //init global componentof
    cnt = 0;
    componentof = malloc(sizeof(int) * g->nV);
    int i;
    for (i=0; i<g->nV; i++) {
        componentof[i] = -1;
    }
    assign = 0;
    while (assign < g->nV) {
        //find an unassigned vertex
        int j;
        for (j = 0; j < g->nV;j++) {
            if (componentof[j] == -1) break;
        }
        cnt++;
        dfs(g, j);
    }
    free(componentof);
    return cnt;
}

