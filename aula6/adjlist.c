#include "adjlist.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  /* Precisa passar um arquivo de entrada para o programa na linha de comando. Exemplo: ./adjlist.out < simplegraph.txt . */
  Graph G;
  int n, i, x, y, weight;
  if (scanf("%d\n", &n) == 1) {
    G = initGraph(n);
    while (scanf("%d %d %d\n", &x, &y, &weight) != EOF) {
      insertEdge(G, x, y, weight);
    }
  }

  //removeEdge(G, 2, 3);
  printGraph(G);

  //startDFS(G, 0);
  //startBFS(G, 0);
  
  //checkEulerPath(G);
  //checkHamiltonPath(G, 0, 0);

  //topologicalSortDAG(G);

  dijkstra(G, 0);
  floydAllPath(G);

  destroyGraph(G);
  return 0;
}