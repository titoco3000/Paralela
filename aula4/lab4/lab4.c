#include "Matriz.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex_camadas_vagas;
int camadas_vagas;

Matriz A;
int *B;
int *C;

void *Multiplicador() {
  while (1) {
    // verifica se ainda existem camadas vagas
    pthread_mutex_lock(&mutex_camadas_vagas);
    if (camadas_vagas > 0) {
      // se sim, reserva uma para si
      int nivel = --camadas_vagas;
      pthread_mutex_unlock(&mutex_camadas_vagas);
      C[nivel] = 0;
      for (int i = 0; i < A.altura; i++)
        C[nivel] += *AcessarMatriz(&A, i, nivel) * B[i];
    } else {
      // se não, finaliza
      pthread_mutex_unlock(&mutex_camadas_vagas);
      break;
    }
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    puts("Argumentos insuficientes. Uso: lab4  <tamanho do vetor> <threads "
         "usados (por padrão 1)>");
    return 1;
  }

  int tamanho_problema = atoi(argv[1]);
  int qtd_threads = argc > 2 ? atoi(argv[2]) : 1;

  // aloca memória
  A = CriarMatriz(tamanho_problema, tamanho_problema);
  B = malloc(sizeof(int) * A.altura);
  C = malloc(sizeof(int) * A.altura);

  // preenche matriz e vetor
  for (int i = 0; i < A.altura; i++) {
    for (int j = 0; j < A.largura; j++) {
      *AcessarMatriz(&A, i, j) = i * A.altura + j;
    }
    B[i] = i;
  }

  pthread_mutex_init(&mutex_camadas_vagas, NULL);
  camadas_vagas = tamanho_problema;
  printf("Multiplicando matrz quadrada por vetor com %d elementos usando %d workers",tamanho_problema,qtd_threads);
  pthread_t *thread_pool = (pthread_t *)malloc(sizeof(pthread_t) * qtd_threads);
  int i;
  for (i = 0; i < qtd_threads; i++) {
    if (pthread_create(&thread_pool[i], NULL, Multiplicador, NULL) > 0) {
      perror("Falha ao criar thread");
    }
  }
  for (i = 0; i < qtd_threads; i++)
    pthread_join(thread_pool[i], NULL);

  if (argc > 3) {
    for (i = 0; i < A.altura; i++) {
      printf("%d\n", C[i]);
    }
  }

  // libera memoria alocada
  LiberarMatriz(A);
  free(B);
  free(C);
  free(thread_pool);

  return 0;
}
