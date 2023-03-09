#include <stdio.h>
#include <stdlib.h>

struct pessoa {
    int idade;
    float peso, altura;
};

int main()
{
    srand(32120613);
    struct pessoa pessoas[3];
    for (int i = 0; i < 3; i++)
    {
        //simula o input
        pessoas[i].idade = rand() % 100;
        pessoas[i].peso = (float)(rand() % 100);
        pessoas[i].altura = (float)(rand() % 100) / 50.0;

        printf("Pessoa %d\n", i + 1);
        printf("    idade: %d\n", pessoas[i].idade);
        printf("    peso: %.1f\n", pessoas[i].peso);
        printf("    altura: %.2f\n\n", pessoas[i].altura);
    }


    return 0;
}