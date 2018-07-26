#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"

//Graph ADT
typedef struct GraphRep {
	int nVertex;
	int nEdges;
	AdjList *edges;
} GraphRep;

Graph newGraph(int noNodes) {
	Graph new = malloc(sizeof(struct GraphRep));
	assert(new != NULL);
	new->nVertex = noNodes;
	new->nEdges = 0;
	new->edges = malloc((new->nVertex) * sizeof(struct _adjListNode));
	int i;
	for (i = 0; i < new->nVertex; i++) {
		new->edges[i] = NULL;
	}
	return new;
}

void  insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
	assert(g != NULL);
	//check it is already in graph
	/*AdjList curr = g->edges[src];
	if (curr != NULL) {
	    for (curr = g->edges[src]; curr != NULL; curr = curr->next) {
		    if (curr->w == dest && curr->weight == weight) {
		    	return;
		    }
	    }
	}*/
	//insert edge into graph
	AdjList new = malloc(sizeof(struct _adjListNode));
	new->w = dest;
	new->weight = weight;
	new->next = g->edges[src];
	g->edges[src] = new;
	g->nEdges++;
}

void  removeEdge(Graph g, Vertex src, Vertex dest) {
	assert(g != NULL);
	AdjList curr;
	AdjList find = NULL;
	//if the first edge is to be removed
	if (g->edges[src]->w == dest) {
		find = g->edges[src];
		g->edges[src] = g->edges[src]->next;
		g->nEdges--;
		free(find);
		return;
	}
	//find edge
	for (curr = g->edges[src]; curr->next != NULL; curr = curr->next) {
		if (curr->next->w == dest) {
			find = curr->next;
			break;
		}
	}
	//if not_found
	if (find == NULL) {
		return;
	}
	//remove edge if find != null
	if (find != NULL) {
		curr->next = curr->next->next;
		free(find);
		g->nEdges--;
		return;
	}
}

bool  adjacent(Graph g, Vertex src, Vertex dest) {
	assert(g != NULL);
	AdjList curr;
	for (curr = g->edges[src]; curr != NULL; curr = curr->next) {
		if (curr->w == dest) {
			return true;
		}
	}
	return false;
}

int  numVerticies(Graph g) {
	assert(g != NULL);
	return g->nVertex;
}

AdjList outIncident(Graph g, Vertex v) {
	assert(g != NULL);
	return g->edges[v];
}

AdjList inIncident(Graph g, Vertex v) {
	assert(g != NULL);
	AdjList newList = NULL;
	int i;
	for (i = 0; i < g->nVertex; i++) {
		//skip if v = i
		if (i == v) continue;
		//for other vertices
		AdjList curr = g->edges[i];
		while (curr != NULL) {
			if (curr->w == v) {
				AdjList new = malloc(sizeof(struct _adjListNode));
				new->w = i;
				new->weight = curr->weight;
				new->next = newList;
				newList = new;
				break;
			}
			curr = curr->next;
		}
	}
	return newList;
}

void  showGraph(Graph g) {
	assert(g != NULL);
	printf("Vertices in graph = %d, Edges in graph = %d\n", g->nVertex, g->nEdges);
	int i;
	for (i = 0; i < g->nVertex; i++) {
		AdjList curr = g->edges[i];
		printf("Vertices connected to %d:  ", i);
		while (curr != NULL) {
			printf("%d with weight %d   ", curr->w, curr->weight);
			curr = curr->next;
		}
		printf("\n");
	}
}

void  freeGraph(Graph g) {
	int i;
	AdjList curr;
	AdjList next;
	assert(g != NULL);
	assert(g->edges != NULL);
	for (i = 0; i < g->nVertex; i++) {
		curr = g->edges[i];
		while (curr != NULL) {
			next = curr->next;
			free(curr);
			curr = next;
		}
	}
	free(g);
}
