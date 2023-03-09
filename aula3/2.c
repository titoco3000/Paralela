#include <stdio.h>

int main()
{
    srand(32120613);
    float n1 = (float)(rand() % 11);
    float n2 = (float)(rand() % 11);
    float n3 = (float)(rand() % 11);
    float me = (float)(rand() % 11);
    float ma = (n1 + n2 * 2.0 + n3 * 3 + me) / 7.0;
    printf("MA = (N1 + N2*2 + N3*3 + ME)/7\n");
    printf("MA = (%f + %f*2 + %f*3 + %f)/7 = %f\n", n1, n2, n3, me, ma);
    char conceito;
    if (ma >= 9.0)
        conceito = 'A';
    else if (ma >= 7.5)
        conceito = 'B';
    else if (ma >= 6.0)
        conceito = 'C';
    else if (ma >= 4.0)
        conceito = 'D';
    else
        conceito = 'E';
    printf("Conceito: %c\n", conceito);
}