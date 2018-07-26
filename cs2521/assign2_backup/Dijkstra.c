#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "PQ.h"
#include "Dijkstra.h"
#include "Graph.h"

#define INFI 0x70000000

static ItemPQ createItem(int key, int value);
static void updatePred(PredNode **list, int v, int w);
static void addPred(PredNode **list, int v, int w); 

ShortestPaths dijkstra(Graph g, Vertex src) {
	//init ShortestPaths
	ShortestPaths new;
	new.dist = malloc(sizeof(int) * (numVerticies(g)));
	assert((new.dist) != NULL);
	new.pred = malloc(sizeof(struct PredNode) * (numVerticies(g)));
	assert((new.pred) != NULL);
	new.src = src;
	new.noNodes = numVerticies(g);
	//init dist and priority queue
	PQ q = newPQ();
	int i;
	for (i = 0; i < new.noNodes; i++) {
		new.dist[i] = INFI;
		new.pred[i] = NULL;
		ItemPQ newItem = createItem(i, new.dist[i]);
		addPQ(q, newItem);
	}
	new.dist[src] = 0;
	new.pred[src] = NULL;

	ItemPQ update = createItem(src, new.dist[src]);
	updatePQ(q, update);
	while (!PQEmpty(q)) {
		ItemPQ sItem = dequeuePQ(q);
		Vertex s = sItem.key;
		AdjList out = outIncident(g, s);
		AdjList curr = out;
		while (curr != NULL) {
			int len = curr->weight;
			if ((new.dist[s] + len) < (new.dist[curr->w])) {
				//update dist
				new.dist[curr->w] = (new.dist[s]) + len;
				//update queue
				ItemPQ newDist = createItem(curr->w, new.dist[curr->w]);
				updatePQ(q, newDist);
				//update pred
				updatePred(new.pred, s, curr->w);
            } else if ((new.dist[s] + len) == (new.dist[curr->w])) {
                addPred(new.pred, s, curr->w);
            }
			curr = curr->next;
		}
	}
	freePQ(q);
	//for all vertex that is not reachable, make dist of them to 0
	int m;
	for (m = 0; m < numVerticies(g); m++) {
	    if (new.pred[m] == NULL) {
	        new.dist[m] = 0;
	    }
	}
	return new;
}

void  showShortestPaths(ShortestPaths s) {
	int i = 0;
	printf("Node %d\n",s.src);
	printf("  Distance\n");
	for (i = 0; i < s.noNodes; i++) {
		if(i == s.src)
	    	printf("    %d : X\n",i);
		else
			printf("    %d : %d\n",i,s.dist[i]);
	}
	printf("  Preds\n");
	for (i = 0; i < s.noNodes; i++) {
		printf("    %d : ",i);
		PredNode* curr = s.pred[i];
		while(curr!=NULL) {
			printf("[%d]->",curr->v);
			curr = curr->next;
		}
		printf("NULL\n");
	}
}

void  freeShortestPaths(ShortestPaths s) {
	int i;
	//free distance
	free(s.dist);
	//free pred
	for (i = 0; i < s.noNodes; i++) {
		if (s.pred[i] == NULL) continue;
		PredNode *curr = s.pred[i];
		while (curr != NULL) {
			PredNode *temp = curr->next;
			free(curr);
			curr = temp;
		}
	}
	free(s.pred);
}

static ItemPQ createItem(int key, int value) {
	ItemPQ new;
	new.key = key;
	new.value = value;
	return new;
}

static void updatePred(PredNode **list, int v, int w) {
	//create new node
	PredNode *new = malloc(sizeof(PredNode));
	assert(new != NULL);
	new->v = v;
	new->next = NULL;
	list[w] = new;
}

static void addPred(PredNode **list, int v, int w) {
    //create new node
    PredNode *new = malloc(sizeof(PredNode));
    assert(new != NULL);
    new->v = v;
    new->next = NULL;
    PredNode *curr = list[w];
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new;
}

