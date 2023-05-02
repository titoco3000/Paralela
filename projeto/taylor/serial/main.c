#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void calcular_e_taylor_serial_float(int precisao, char *buf) {
  long double sum = 0.0;
  long double fat = 1.0;
  for (int i = 0; i < precisao; i++) {
    sum += 1.0 / fat;
    fat *= (i + 1.0);
  }
  sprintf(buf, "%.100LF", sum);
}
void calcular_e_taylor_serial_int(int precisao, char *buf) {
  unsigned long long UM =
      (unsigned long long)100000000 * (unsigned long long)10000000000;
  unsigned long long sum = 0;
  unsigned long long fat = 1;
  for (int i = 1; i < precisao; i++) {
    sum += UM / fat;
    fat *= i;
  }
  printf("%llu\n", sum);
}

int main(void) {
  char *buf = malloc(sizeof(char) * 1000);
  // calcular_e_taylor_serial_float(100000, buf);
  calcular_e_taylor_serial_int(10, buf);
  puts(buf);
  free(buf);
  return 0;
}
