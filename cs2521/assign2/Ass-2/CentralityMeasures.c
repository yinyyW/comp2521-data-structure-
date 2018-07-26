// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "Graph.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

static int numPaths(PredNode **pred, int j, PredNode *next);
static int numPassi(PredNode **pred, int j, PredNode *next, int i);

NodeValues outDegreeCentrality(Graph g){
	NodeValues out;
    out.values = malloc(sizeof(double) * numVerticies(g));
    out.noNodes = numVerticies(g) - 1;
	int i;
	for (i = 0; i < numVerticies(g); i++) {
	    AdjList outdegree = outIncident(g, i);
	    AdjList curr = outdegree;
	    double cnt = 0.0;
	    while (curr != NULL) {
	        cnt = cnt + 1.0;
	        curr = curr->next;
	    }
	    out.values[i] = cnt;
	}
	return out;
}

NodeValues inDegreeCentrality(Graph g){
	NodeValues in;
	in.noNodes = numVerticies(g) - 1;
	in.values = malloc(sizeof(double) * numVerticies(g));
	int i;
	for (i = 0; i < numVerticies(g); i++) {
	    AdjList indegree = inIncident(g, i);
	    AdjList curr = indegree;
	    double cnt = 0.0;
	    while (curr != NULL){
	        cnt = cnt + 1.0;
	        curr = curr->next;
	    }
	    in.values[i] = cnt;
	}
	return in;
}

NodeValues degreeCentrality(Graph g) {
	int i;
	NodeValues outd = outDegreeCentrality(g);
	NodeValues ind = inDegreeCentrality(g);
	NodeValues new;
	new.values = malloc(sizeof(double) * numVerticies(g));
	new.noNodes = numVerticies(g) - 1;
	for (i = 0; i < numVerticies(g); i++) {
	    new.values[i] = outd.values[i] + ind.values[i];
	}
	return new;
}

NodeValues closenessCentrality(Graph g){
    NodeValues new;
    new.noNodes = numVerticies(g) - 1;
    new.values = malloc(sizeof(double) * numVerticies(g));
    int i;
    for (i = 0; i < numVerticies(g); i++) {
        //count # of vertices that i can reach
        double cnt = 1.0;
        int m;
        ShortestPaths newpath = dijkstra(g, i);
        for (m = 0; m < numVerticies(g); m++) {
            if (newpath.pred[m] != NULL) {
                cnt = cnt + 1.0;
            }
        }
        //calculate sum of all paths
        double dist = 0.0;
        int j;
        double sum = 0.0;
        for (j = 0; j < numVerticies(g); j++) {
            dist = (double)(newpath.dist[j]);
            sum = sum + dist;
        }
        //get final res
        double numNodes = (double)(new.noNodes);
        double left = (cnt - 1.0)/numNodes;
        double right = (cnt - 1.0)/sum;
        new.values[i] = left * right;
    }
            
     return new;
}

NodeValues betweennessCentrality(Graph g){
	NodeValues new;
	new.noNodes = numVerticies(g) - 1;
	new.values = malloc(sizeof(double) * numVerticies(g));
	int i;
	for (i = 0; i < numVerticies(g); i++) {
	    double sum = 0.0;
	    int j;
	    int k;
	    for (j = 0; j < numVerticies(g); j++) {
	        if (j == i) continue;
	        ShortestPaths new = dijkstra(g, j);
	        for (k = 0; k < numVerticies(g); k++) {
	            if (k == i) continue;
	            //get # shortestpaths from j to k
	            int numOfPaths = numPaths(new.pred, j, new.pred[k]);
                int passi = numPassi(new.pred, j, new.pred[k], i);
                double depend = numOfPaths/passi;
                sum = sum + depend;
	        }
	    }
	    new.values[i] = sum;
	}
	return new;
}

NodeValues betweennessCentralityNormalised(Graph g){
    NodeValues b = betweennessCentrality(g);
    NodeValues normal;
    normal.values = malloc(sizeof(double) * numVerticies(g));
    int n = numVerticies(g);
    int denominator = (n-1) * (n-2);
    int i;
    for (i = 0; i < n; i++)  {
        normal.values[i] = (1/denominator) * (b.values[i]);
    }
    return normal;
}

void showNodeValues(NodeValues values){
    int i;
    for (i = 0; i <= values.noNodes; i++) {
        printf("%d: %.6lf\n", i, values.values[i]);
    }
}

void freeNodeValues(NodeValues values){
    free(values.values);
}

static int numPaths(PredNode **pred, int j, PredNode *next) {
    PredNode *curr = next;
    if (curr == NULL) return 0;
    if (curr->v == j) {
        return 1 + numPaths(pred, j, curr->next);
    }
    return numPaths(pred, j, pred[curr->v]) + numPaths(pred,j, curr->next);
}

static int numPassi(PredNode **pred, int j, PredNode *next, int i) {
    PredNode *curr = next;
    if (next == NULL) {
        return 0;
    } else if (curr->v == j) {
        return numPassi(pred, j, curr->next, i);
    } else if (curr->v == i) {
        return 1 + numPassi(pred, j, curr->next, i);
    } else {
        return numPassi(pred, j, pred[curr->v], i) + numPassi(pred, j, curr->next, i);
    }
}
