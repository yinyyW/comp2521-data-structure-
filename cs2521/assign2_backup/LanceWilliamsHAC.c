#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define INFI 0x70000000

static void updateArray(Dendrogram *Den, int index);
static double Dist(double **dist, int i, int j, int k, int method);
static void updateMatrix(double **dist, int i, int length);
static void updateMatrixArray(double *list, int index);

Dendrogram LanceWilliamsHAC(Graph g, int method) {
    //init dist[][] to 
    double *dist;
    dist = malloc(sizeof(double) * numVerticies(g) * numVerticies(g));
    int i;
    for (i = 0; i < numVerticies(g); i++) {
        int j;
        for (j = 0; j < numVerticies(g); j++) {
            dist[i][j] = (double)INFI;
        }
    }
    //assign all dist in g to dist[][]
    int m;
    for (m = 0; m < numVerticies(g); m++) {
        dist[m][m] = 0;
        AdjList curr = outIncident(g, m);
        int n = 0;
        while (curr != NULL) {
            double temp = (double)(curr->weight);
            dist[m][curr->w] = 1.0/temp;
            curr = curr->next;
            n++;
        }
    }
    //choose a smaller one for dist[][]
    int c;
    for (c = 0; c < numVerticies(g); c++) {
        int d;
        for (d = 0; d < numVerticies(g); d++) {
            if (dist[c][d] < dist[d][c]) {
                dist[d][c] = dist[c][d];
            } else {
                dist[c][d] = dist[d][c];
            }
        }
    }
    
    //init Dendrogram array
    Dendrogram *Den = malloc(sizeof(struct DNode) * numVerticies(g));
    int k;
    for (k = 0; k < numVerticies(g); k++) {
        Den[k]->vertex = k;
        Den[k]->left = NULL;
        Den[k]->right = NULL;
    }
    int n;
    int len = numVerticies(g);
    for(n = 1; n < numVerticies(g); n++) {
        //find closest clusters
        int row;
        double min = (double)INFI;
        int start;
        int end;
        for (row = 0; row < numVerticies(g); row++) {
            int col;
            for (col = 0; col < numVerticies(g); col++) {
                if (dist[row][col] < min) {
                    min = dist[row][col];
                    start = row;
                    end = col;
                }
            }
        }
        //merge two clusters(update dentrogram)
        Dendrogram new = malloc(sizeof(struct DNode));
        if start < end {
            new->vertex = start;
            new->left = Den[start];
            new->right = Den[end];
            //update Dentrogram array
            Den[start] = new;
            updateArray(Den, start);
        } else {
            new->vertex = end;
            new->left = Den[end];
            new->right = Den[right];
            //update Dentrogram array
            Den[end] = new;
            updateArray(Den, end);
        }
        //decreament length of the array and matrix
        len--
        //update dist[][]
        if (start > end)
            updateMatrix(dist, start, len);
        else
            updateMatrix(dist, end, len);
        int a;
        //if end has been removed
        if (start < end) {
            for (a = 0; a < len; a++) {
                if (a == start) dist[start][a] == (double)INFI;
                double res = Dist(dist, start, end, a, method);
                dist[start][a] = res;
                dist[a][start] = res;
            }
        } else {
            for (a = 0; a < len; a++) {
                if (a == end) dist[end][a] == (double)INFI;
                double res = Dist(dist, end, start, a, method);
                dist[end][a] = res;
                dist[a][end] = res;
            }
        }
    }
    return Den[0];
}

static void updateMatrix(double **dist, int i, int length);
    int j;
    for (j = 0; j < length; j++) {
        updateMatrixArray(dist[i], i);
    }
    updateMatrixRow(dist, i);
}


//deleting an element from the matrixarray
static void updateMatrixArray(double *dist, int index)



// deleting a row from the matrix
static void updateMatrixRow(double **dist, int i)

//calculate new distance for the new cluster
//method should be = 1 or = 2
//method = 1 single link
//method = 2 complete link
static double Dist(double **dist, int i, int j, int k, int method)
