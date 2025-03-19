#include <stdio.h>

int main(void) {
    int n, x, y;
    printf("Número de vértices: ");
    scanf("%d", &n);
    printf("Digite os pares de arcos relacionados aos %d vértices. Digite -1 para terminar. \n", n);
    while (scanf("%d %d", &x, &y)) {
        if(x == -1 || y ==-1) {
            break;
        }
        printf("Arco: %d %d\n", x, y);
    }
    printf("fim.");
    return 0;
}
