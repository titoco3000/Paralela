/*
https://youtu.be/nleB7uPtQxQ
https://adamcrussell.livejournal.com/6924.html
https://github.com/zachratliff22/EulerSpigot

preenchimento de 1s serial (10bi):0.55s
preenchimento de 1s paralelo (10bi):0.40s
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int* vetor;
char *buffer;

int num_digits = 100000;
int bufoc = 0;
int voltas = 0;

char preenchido[] = {0,0};

void *worker(void *arg){
    int thread_id = *((int*)arg);

    int q;
    int r;

    //preenchimento por 1s
    int numeros_por_bloco = num_digits/2;
    for (int i = numeros_por_bloco*thread_id; i < numeros_por_bloco*(1+thread_id); i++){
        vetor[i] = 1;
    }
    preenchido[thread_id] = 1;

    //aguarda o outro preencher
    while (!preenchido[!thread_id])
        sched_yield();

    while (voltas < num_digits-1)
    {
        while (preenchido[0] == thread_id)
            sched_yield();
        
        //printf("Thread %d começando 1ª parte\n",thread_id);
        vetor[num_digits-1]*=10;
        int i;
        for (i = num_digits-1; i > num_digits/2; i--)
        {
            //usleep(rand()%10000+1000);
            q = vetor[i] / (i + 2);
            r = vetor[i] % (i + 2);
            vetor[i - 1]*=10;
            vetor[i - 1] += q; // item à esq = quociente
            vetor[i] = r; // atual = resto
        }
        //printf("Thread %d finalizou 1ª parte\n",thread_id);
        
        //inverte estado
        preenchido[0] = thread_id;

        while (preenchido[1] == thread_id)
            sched_yield();
        
        //printf("Thread %d começando 2ª parte\n",thread_id);
        for (; i > 0; i--)
        {
            //usleep(rand()%10000+100);
            q = vetor[i] / (i + 2);
            r = vetor[i] % (i + 2);
            vetor[i - 1]*=10;
            vetor[i - 1] += q; // item à esq = quociente
            vetor[i] = r; // atual = resto
        }
        q = vetor[0] / 2;
        r = vetor[0] % 2;
        vetor[0] = r;
        buffer[bufoc++] = 48 + q;


        //printf("Thread %d finalizou 2ª parte\n",thread_id);
        
        //inverte estado
        preenchido[1] = thread_id;
        
        voltas++;
    }

    //printf("Thread %d finalizou\n",thread_id);
    
}

int main() {
    vetor = (int *)malloc(sizeof(int)*num_digits);   
    buffer = (char *)malloc(sizeof(char)*num_digits+3);
    
    pthread_t threads[2];
    int threads_args[] = {0,1};
    
    buffer[bufoc++] = '2';
    buffer[bufoc++] = '.';
    buffer[num_digits + 2] = 0;


    //puts("Indo criar threads");
    if (pthread_create(&threads[0], NULL, worker, &threads_args[0]) > 0 ||
        pthread_create(&threads[1], NULL, worker, &threads_args[1]) > 0)
        perror("Falha ao criar thread");

    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);

    FILE *fp = fopen("gerado.txt", "w+");
    if (fp != NULL)
    {
        fputs(buffer, fp);
        fclose(fp);
    }

    free(buffer);
    free(vetor);
}
