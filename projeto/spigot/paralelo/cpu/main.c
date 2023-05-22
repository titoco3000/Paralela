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

unsigned int* vetor;
FILE *fp;

unsigned int num_digits = 20001;
unsigned int voltas = 0;

char preenchido[] = {0,0};

void *worker(void *arg){
    unsigned int thread_id = *((unsigned int*)arg);

    unsigned int q;
    unsigned int r;

    //preenchimento por 1s
    unsigned int numeros_por_bloco = num_digits/2;
    for (unsigned int i = numeros_por_bloco*thread_id; i < numeros_por_bloco*(1+thread_id); i++){
        vetor[i] = 1;
    }
    preenchido[thread_id] = 1;

    //aguarda o outro preencher
    while (!preenchido[!thread_id])
        sched_yield();

    while (voltas < num_digits)
    {
        while (preenchido[0] == thread_id)
            sched_yield();
        
        //printf("Thread %d começando 1ª parte\n",thread_id);
        vetor[num_digits-1]*=10;
        unsigned int i;
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
        fputc(48 + q,fp);


        //printf("Thread %d finalizou 2ª parte\n",thread_id);
        
        //inverte estado
        preenchido[1] = thread_id;
        printf("%d\n",voltas);
        
        voltas++;
    }
    //printf("Thread %d finalizou\n",thread_id);
}

unsigned int main() {
    fp = fopen("out.txt", "w+");
    if (fp != NULL)
    {
        vetor = (unsigned int *)malloc(sizeof(unsigned int)*num_digits);   
        pthread_t threads[2];
        unsigned int threads_args[] = {0,1};
        
        fputc('2',fp);
        fputc('.',fp);

        //puts("Indo criar threads");
        if (pthread_create(&threads[0], NULL, worker, &threads_args[0]) > 0 ||
            pthread_create(&threads[1], NULL, worker, &threads_args[1]) > 0)
            perror("Falha ao criar thread");

        pthread_join(threads[0],NULL);
        pthread_join(threads[1],NULL);
        free(vetor);
    }
    fclose(fp);
}
