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
	//alloct memory for new NodeValues
    out.values = malloc(sizeof(double) * numVerticies(g));
    out.noNodes = numVerticies(g) - 1;
	int i;
	//calculate values for node's values[]
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
	//alloct memory for new NodeValues
	in.noNodes = numVerticies(g) - 1;
	in.values = malloc(sizeof(double) * numVerticies(g));
	int i;
	//calculate values for node's values[]
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
	//alloct memory for new NodeValues
	new.values = malloc(sizeof(double) * numVerticies(g));
	new.noNodes = numVerticies(g) - 1;
	//calculate values for node's values[]
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
        if (sum == 0) {
            new.values[i] = 0.0;
            continue;
        }
        //multiply left and right to get values[i]
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
	        //skip if j == i
	        if (j == i) continue;
	        ShortestPaths new = dijkstra(g, j);
	        for (k = 0; k < numVerticies(g); k++) {
	            //skip if i==j==k
	            if (k == i || k == j) continue;
	            //get # shortestpaths from j to k
	            int numOfPaths = numPaths(new.pred, j, new.pred[k]);
                int passi = numPassi(new.pred, j, new.pred[k], i);
                if (numOfPaths == 0 || passi == 0) continue;
                //convert num and passi to double
                double up = (double)passi;
                double down = (double)numOfPaths;
                double depend = up/down;
                sum = sum + depend;
                //if (i == 47) printf("sum = %lf\n", sum);
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
    normal.noNodes = numVerticies(g) - 1;
    int n = numVerticies(g);
    //calculate denominator as int
    int denominator = (n-1) * (n-2);
    //convert int to double
    double de = (double)(denominator);
    //normalise all betweeness and place them into node.values[]
    int i;
    for (i = 0; i < n; i++)  {
        double left = 1/de;
        double right = (double)(b.values[i]);
        normal.values[i] = left * right;
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
    //if no path available
    if (curr == NULL) return 0;
    //if find one path and continue to next pred node
    if (curr->v == j) {
        return 1 + numPaths(pred, j, curr->next);
    }
    //normal case(path not found and continue to find recursively)
    return numPaths(pred, j, pred[curr->v]) + numPaths(pred,j, curr->next);
}

static int numPassi(PredNode **pred, int j, PredNode *next, int i) {
    PredNode *curr = next;
    if (next == NULL) {
        //if no path available
        return 0;
    } else if (curr->v == j) {
        //find the end of the path and no one pass vertex i
        return numPassi(pred, j, curr->next, i);
    } else if (curr->v == i) {
        //find a path that pass vertex i
        return 1 + numPassi(pred, j, curr->next, i);
    } else {
        //path not found and continue to find recursively
        return numPassi(pred, j, pred[curr->v], i) + numPassi(pred, j, curr->next, i);
    }
}
