#ifndef GRAPH
	#define GRAPH
	#include "Graph.h"
#endif
#include "GraphVis.h"
#include "Dijkstra.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

int main(){
	// some very simple code to show you
	// how to use graph vis

  Graph g = newGraph(3);
  insertEdge(g,0,1,1);
  insertEdge(g,1,2,2);
  insertEdge(g,2,0,1);

  showGraph(g);

	// draws the graph
  graphVis(g, DEFAULT);
  
    int i;
  for(i=0; i<numVerticies(g); i++) {
    ShortestPaths paths = dijkstra(g,i);
    showShortestPaths(paths);
    freeShortestPaths(paths);
  }
	return EXIT_SUCCESS;
}
