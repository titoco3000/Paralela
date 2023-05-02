/*
Para 1000 iterações:

real    0m4.565s
user    0m0.656s
sys     0m0.000s
*/
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

void calcular_e_taylor_gmp(unsigned long precisao) {
    mpz_t sum;
    mpz_t fat_inverso;
    mpz_init_set_ui(sum,10);
    mpz_pow_ui(sum,sum,10000000);

    mpz_init_set(fat_inverso,sum);

    for (unsigned long i = 1; i < precisao; i++) {
        printf("%lu/%lu\n",i,precisao);
        mpz_tdiv_q_ui(fat_inverso, fat_inverso,i);
        mpz_add(sum,sum,fat_inverso);
    }

    FILE* file = fopen("gerado.txt", "w+");

    mpz_out_str(file,10,sum);
    mpz_clear(sum);
    mpz_clear(fat_inverso);
}

int main(){
    calcular_e_taylor_gmp(1000);
    return 0;
}