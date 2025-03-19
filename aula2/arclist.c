#include "arclist.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  /* Precisa passar um arquivo de entrada para o programa na linha de comando. Exemplo: ./arclist.out < simplegraph.txt . */
  int n, x, y;
  Graph alist;
  if (scanf("%d\n", &n) == 1) {
    alist = initGraph();
    while (scanf("%d %d\n", &x, &y) != EOF) {
      insertArc(alist, x, y);
    }
  }

  printGraph(alist);
  printf("Remove 2 -- 3\n");
  removeArc(alist, 2, 3);
  printGraph(alist);
  destroyGraph(alist);
  return 0;
}