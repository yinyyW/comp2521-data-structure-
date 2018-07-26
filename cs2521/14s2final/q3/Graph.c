// Graph.c ... implementation of Graph ADT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"

// type for small +ve int values
typedef unsigned char bool;

// graph representation (adjacency matrix)
typedef struct _graph_rep {
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
         if (g->edges[v][w]) printf(" %d",w);
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

// wellConnected ... list of vertices
// - ordered on #connections, most connected first
/*
Connects *wellConnected(Graph g, int *nconns)
{
    assert(g != NULL && nconns != NULL);
    *nconns = 0;
    int total = 0;
    //alloct memory for array
    Connects *wellC = malloc(sizeof(Connects) * g->nV);
    int i;
    for (i = 0; i < g->nV; i++) {
        wellC[i].vertx = i;
        wellC[i].nconn = 0;
    }
    //find all well-connected vertices
    int j;
    for (j = 0; j < g->nV; j++) {
        //check if current vertex is well-connected
        int cnt = 0;
        int k;
        for (k = 0; k < g->nV; k++) {
            if (g->edges[j][k]) {
                cnt++;
            }
        }
        if (cnt >= 2) {
            wellC[j].nconn = cnt;
            total++;
        }
    }
    //sort: bubble sort
    int m, n, nswaps;
    for (m = 0; m < g->nV; m++) {
        nswaps = 0;
        for (n = (g->nV)-1; n > m; n--) {
            //descending order
            if (wellC[n].nconn >  wellC[n-1].nconn) {
                //swapN(wellC[n], wellC[n-1);
                Connects temp = wellC[n];
                wellC[n] = wellC[n-1];
                wellC[n-1] = temp;
                nswaps++;
                //printf("vertex%d(%d) = %d, vertex%d(%d) = %d\n", wellC[n].vertx,n, wellC[n].nconn, wellC[n-1].vertx,n-1, wellC[n-1].nconn);
            }
            //ascending order
            if (wellC[n].nconn == wellC[n-1].nconn && wellC[n].vertx < wellC[n-1].vertx) {
                //swapN(wellC[n], wellC[n-1]);
                Connects temp = wellC[n];
                wellC[n] = wellC[n-1];
                wellC[n-1] = temp;
            }
        }
        if (nswaps == 0) break;
    }
    //printf("vertex%d(%d) = %d\n", wellC[3].vertx, 3, wellC[3].nconn);
    *nconns = total;
    return wellC;
}
*/

Connects *wellConnected(Graph g, int *nconns) {
    int numConns = 0;
    Connects *well = malloc(sizeof(Connects) * g->nV);
    //init well
    int m;
    for (m=0; m < g->nV; m++) {
        well[m].nconn = 0;
        well[m].vertx = m;
    }
    //traverse all vertices and find all well-conn vertices
    int i;
    for (i = 0; i < g->nV; i++) {
        int cnt = 0;
        //cnt edges
        int j;
        for (j = 0; j < g->nV; j++) {
            if (g->edges[i][j]) {
                cnt++;
            }
        }
        //if it is well-connected
        if (cnt >=2 ){
            well[i].nconn = cnt;
            //well[j].vertx = j;
            numConns++;
            //printf("vertex:%d, nconn: %d\n",well[i].vertx, well[i].nconn);
        }
    }
    //sort well[]
    for (i = 0; i < g->nV; i++) {
        int j;
        int nswaps;
        for (j = (g->nV)-1; j > i; j--) {
            if (well[j].nconn > well[j-1].nconn) {
                //swap
                Connects temp = well[j];
                well[j] = well[j-1];
                well[j-1] = temp;
                nswaps++;
            }
            if ((well[j].nconn == well[j-1].nconn) && (well[j].vertx < well[j-1].vertx)) {
                //swap
                Connects temp = well[j];
                well[j] = well[j-1];
                well[j-1] = temp;
                nswaps++;
            }
        }
        if (nswaps == 0) break;
    }
    *nconns = numConns;
    return well;
}
