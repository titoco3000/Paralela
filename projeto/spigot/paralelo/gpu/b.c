/*
https://youtu.be/nleB7uPtQxQ
https://adamcrussell.livejournal.com/6924.html
https://github.com/zachratliff22/EulerSpigot

*/

#include <stdio.h>
#include <stdlib.h>

unsigned int *vetor;
unsigned int n_digits = 100;
unsigned int n_paralelo = 10;

void print_vec(unsigned int* v){
    for (int i = 0; i < n_digits; i++)
    {
        printf("%d ",v[i]);
    }
    puts("");
}

//a fazer em todos exceto primeiro
void pentear(int i){
    vetor[i - 1]= vetor[i - 1]*10 + vetor[i] / (i + 2);
    vetor[i] %= (i + 2);
}

int extrair(){
    int q = vetor[0] / 2;
    int r = vetor[0] % 2;
    vetor[0] = r;
    return q;
}

void spigot_inicial() {
    for (int i = 0; i < n_paralelo-1; i++)
    {
        vetor[n_digits-1]*=10;
        for (int j = n_digits-1; j > n_digits-((n_paralelo - i)*2)+1; j--)
        {
            pentear(j);
        }
    }
}

void spigot_principal(){
    vetor[n_digits-1]*=10;
    print_vec(vetor);
    for (int offset = 0; offset <= n_digits - 2*n_paralelo; offset++)
    {
        for (int i = 0; i < n_paralelo; i++)
        {
            pentear(n_digits -1 -(i*2)-offset);
        }
    }
    print_vec(vetor);
}

void spigot_final(){
    for (int i = 0; i < n_paralelo; i++)
    {
        for (int j = i*2; j > 0; j--)
        {
            pentear(j);
        }
        
        printf("%d extraido de 0\n",extrair());
    }
}

int main() {
    vetor = malloc(sizeof(int)*n_digits);

    //preenche o vetor com 1s
    for (int i = 0; i < n_digits; i++)
        vetor[i] = 1;


    spigot_inicial();
    printf("\nspigot principal\n");
    spigot_principal();
    printf("\nspigot final\n");
    spigot_final();
    free(vetor);
}

//7 1 8 2 8 1 8 28459045235360287
//7 1 8 2 8 1 5 2 5 5 7