#include <stdio.h> 
#include <stdlib.h>
#include <omp.h>
#include <math.h>

double f(double x){
    return exp(x);
}

int main(int argc, char * argv[]) {
    if(argc<5){
        printf("args insuficientes(inicio, fim, segmentos, threads\n");
        return 1;
    }
    double inicio = strtod(argv[1], NULL);
    double fim = strtod(argv[2],NULL);
    int n = atoi(argv[3]);
    int thread_count = atoi(argv[4]);

    double segm_size = (fim-inicio)/n;
    double approx = 0.0;

    #pragma omp parallel for num_threads(thread_count) reduction(+:approx)
    for(int i=0;i<n;i++){
        approx+=(f(inicio+segm_size*i)+f(inicio+segm_size*(i+1)))*0.5;
    }

    printf("approx: %f\n",approx);

    return 0;
} /* main */

void Hello(void) {
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads ();
    printf("Hello from thread %d of %d\n", my_rank, thread_count);
} /* Hello */
