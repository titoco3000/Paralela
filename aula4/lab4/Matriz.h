#include <stdlib.h>

typedef struct Matriz {
  int *valores;
  int largura;
  int altura;
} Matriz;

Matriz CriarMatriz(int largura, int altura) {
  Matriz m = {(int *)calloc(altura * largura, sizeof(int *)), largura, altura};
  return m;
}

void LiberarMatriz(Matriz m) { free(m.valores); }

int *AcessarMatriz(Matriz *matriz, int x, int y) {
  return &matriz->valores[y * matriz->largura + x];
}
