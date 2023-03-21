/*
Crie um código-fonte que utilize fork() e shmget() entre 2 processos (pai e
filho). Seu código deve garantir que:

o processo pai e o processo filho compartilhem uma variável simples (por
exemplo, inteiro - valor 1)

o processo pai imprime o valor inicial dessa variável; em seguida, cria o
processo filho e espera-o

o processo filho acessa esta variável, realiza uma operação (por exemplo, adição
- valor 2, totalizando 3), modificando o valor; em seguida, o processo filho
termina

o processo pai realiza uma outra operação (por exemplo, multiplicação - valor 4,
totalizando 12), modificando novamente o valor, e imprime novamente a variável

Essa lógica de execução deve ser garantida no seu código-fonte em C.
*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  // ftok para gerar chave unica
  key_t key = ftok("shmfile", 'A');

  // shmget retorna id da memoria criada
  int shmid = shmget(key, sizeof(int), 0644 | IPC_CREAT);

  // shmat associa processo a essa memoria
  int *valor = (int *)shmat(shmid, (void *)0, 0);

  *valor = 1;

  printf("Valor escrito na memoria: %d\n", *valor);

  printf("Criando processo filho\n");
  pid_t pid = fork();
  if (pid < 0) {
    printf("Falha ao criar processo\n");
  } else if (pid == 0) { // processo filho
    *valor += 2;
    printf("Filho somando 2: %d\n", *valor);
  } else { // processo pai
    wait(NULL);
    *valor *= 4;
    printf("Pai multiplicando por 4: %d\n", *valor);
  }
  // desassocia da memoria compartilhada
  shmdt((void *)valor);
  return 0;
}
