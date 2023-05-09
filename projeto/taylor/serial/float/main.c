#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
void calcular_e_taylor_serial_float(int precisao, char *buf) {
  long double sum = 0.0;
  long double fat = 1.0;
  for (int i = 0; i < precisao; i++) {
    sum += 1.0 / fat;
    fat *= (i + 1.0);
  }
  sprintf(buf, "%.100LF", sum);
}


int main(void) {
  char *buf = malloc(sizeof(char) * 1000);
  // calcular_e_taylor_serial_float(100000, buf);
  calcular_e_taylor_serial_int(10, buf);
  puts(buf);
  free(buf);
  return 0;
}
