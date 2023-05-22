/*
https://youtu.be/nleB7uPtQxQ
https://adamcrussell.livejournal.com/6924.html
https://github.com/zachratliff22/EulerSpigot

*/

#include <stdio.h>
#include <stdlib.h>

unsigned int *vetor;
unsigned int n_digits = 8;
unsigned int n_paralelo = 2;

void print_vec(unsigned int* v){
    for (int i = 0; i < n_digits; i++)
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

void spigot_inicial() {
    for (int j = n_digits-n_paralelo*2; j < n_digits; j++)
    {
        //vetor[n_digits-1]*=10;
        for (int i = n_digits - 1; i >= j; i--)
        {
           printf("%d\n",i);
           pentear(i);
        }      
    }
    puts("");
}

void spigot_principal(){
    for (int j = 0; j < n_digits-n_paralelo-1; j++)
    {
        for (int i = 0; i < n_paralelo; i++)
        {
            int index = n_digits - (j+(i*2)) -1;
            printf("i: %d\n",index);
            pentear(index);
        }
        puts("");
    }
    
}

int main() {
    vetor = malloc(sizeof(int)*n_digits);

    //preenche o vetor com 1s
    for (int i = 0; i < n_digits; i++)
        vetor[i] = 1;

    printf("d:2.\n");

    for (int i = n_digits-1; i > 0; i--)
    {
        vetor[n_digits-1]*=10;
        printf("pentenando %d à %d\n",i,n_digits);
        for(int j = i;j<n_digits;j++){
            //printf("%d\n",j);
            pentear(j);
        }
        //puts("");
    }
    int q = vetor[0] / 2;
    int r = vetor[0] % 2;
    vetor[0] = r;
    printf("d: %d\n",q);

    for (int k = 0; k < n_digits; k++)
    {
        vetor[n_digits-1]*=10;
        //printf("pentenando %d à %d\n",1,n_digits);
        for (int i = 1; i < n_digits; i+=1)
        {
            pentear(i);
        }
        int q = vetor[0] / 2;
        int r = vetor[0] % 2;
        vetor[0] = r;
        printf("d: %d\n",q);

    }
    
    

    free(vetor);
}

//7 1 8 2 8 1 8 28459045235360287
//7 1 8 2 8 1 5 2 5 5 7