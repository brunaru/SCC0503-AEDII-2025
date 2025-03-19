#include <stdio.h>

/* Precisa passar um arquivo de entrada para o programa na linha de comando. Exemplo: ./leitura.out < simplegraph.txt . */

int main(void) {
  int n, x, y;
  if(scanf("%d\n", &n) == 1) {
    printf("Vértices: %d\n", n);
    while (scanf("%d %2d\n", &x, &y) != EOF) {
      printf("Arco: %d %d\n", x, y);
    }
  }
  printf("fim.");
  return 0;
}
