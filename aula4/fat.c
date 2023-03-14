/*
para compilar, precisa incluir explicitamente a biblioteca math:
gcc -o fat.bin fat.c -lm
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  unsigned int num;
  int i;
  int j;

  printf("Digite um numero: ");
  scanf("%d", &num);

  if (num > 65) {
    fprintf(stderr, "Fatorial grande demais para ser calculado\n");
    return 1;
  }

  unsigned long long *temps =
      (unsigned long long *)malloc(sizeof(unsigned long long) * num);
  for (i = 0; i < num; i++) {
    temps[i] = i + 1;
  }

  int canal[2];
  pipe(canal);

  for (int r = 0; r < log(num) / log(2); r++) {
    int intervalo = (int)pow(2, r);

    for (i = num - 1 - intervalo; i >= 0; i -= intervalo * 2) {
      pid_t pid = fork();
      if (pid == -1) {
        fprintf(stderr, "Fork falhou");
        return 1;
      }
      if (pid == 0) {
        temps[i + intervalo] *= temps[i];
        write(canal[1], &temps[i + intervalo], sizeof(unsigned long long));
        return 0;
      }
    }
    for (i = num - 1 - intervalo; i >= 0; i -= intervalo * 2)
      wait(NULL);
    for (i = num - 1 - intervalo; i >= 0; i -= intervalo * 2)
      read(canal[0], &temps[i + intervalo], sizeof(unsigned long long));
  }

  printf("fat(%d) = %llu\n", num,temps[num - 1]);
  return 0;
}
