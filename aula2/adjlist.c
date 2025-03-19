#include "adjlist.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  /* Precisa passar um arquivo de entrada para o programa na linha de comando. Exemplo: ./adjlist.out < simplegraph.txt . */
  Graph G;
  int n, i, x, y;
  if (scanf("%d\n", &n) == 1) {
    G = initGraph(n);
    while (scanf("%d %d\n", &x, &y) != EOF) {
      insertEdge(G, x, y);
    }
  }

  printGraph(G);

  removeEdge(G, 2, 3);

  printGraph(G);
  destroyGraph(G);
  return 0;
}