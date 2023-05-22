/*
https://youtu.be/nleB7uPtQxQ
https://adamcrussell.livejournal.com/6924.html
https://github.com/zachratliff22/EulerSpigot

*/

#include <stdio.h>
#include <stdlib.h>

unsigned int *vetor;
unsigned int num_digits = 12;

void print_vec(unsigned int* v){
    for (int i = 0; i < num_digits; i++)
    {
        printf("%d ",v[i]);
    }
    puts("");
}

//a fazer em todos exceto primeiro
void pentear(int i){
    int q = vetor[i] / (i + 2);
    int r = vetor[i] % (i + 2);
    vetor[i - 1]*=10;
    vetor[i - 1] += q; // item à esq = quociente
    vetor[i] = r; // atual = resto
}

void spigot() {
    int q;
    int r;

    vetor[num_digits-1]*=10;

    //print_vec(vetor);
    //do ultimo ao primeiro elemento do vetor (dir à esq)
    for (int i = num_digits - 1; i > 0; i--)
    {
        pentear(i);
    }
    q = vetor[0] / 2;
    r = vetor[0] % 2;
    vetor[0] = r;
    printf("%d",q);
}

int main() {
    int numDigits = 12;
    vetor = malloc(sizeof(int)*numDigits);

    //preenche o vetor com 1s
    for (int i = 0; i < numDigits; i++)
        vetor[i] = 1;

    printf("2.");

    for (int digit = 0; digit < numDigits; digit++)
        spigot(vetor);

    free(vetor);
}
