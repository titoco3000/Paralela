#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

//max de threads por bloco da gpu
#define MAX_THREADS 1024
//precisa ser impar
#define N_DIGITS 3000001

//extremamente ineficiente (mas é só pra debug, não usa na exec normal)
void printVec(int* vetor){
    int n;
    printf("[ ");
    for (int i = 0; i < N_DIGITS; i++)
    {
        cudaMemcpy(&n, &vetor[i], sizeof(int), cudaMemcpyDeviceToHost);
        printf("%d ",n);
    }
    puts("]");
}

__global__ void preencher_item(int *vetor, int offset){
    vetor[blockIdx.x*MAX_THREADS+threadIdx.x+offset] = 1;
}

void preencher(int *vetor){
    int blocos_completos = N_DIGITS/MAX_THREADS;
    int resto = N_DIGITS%MAX_THREADS;
    if(blocos_completos>0)
        preencher_item<<<blocos_completos,MAX_THREADS>>>(vetor, 0);
    if(resto>0)
        preencher_item<<<1,resto>>>(vetor, N_DIGITS-resto);
}

/*
Penteia os elementos do vetor no device.
Args:
- o offset a partir da qual vai pentear (contando do ultimo item até o primeiro + 1)
- o vetor no device
- o vetor de passagens (se tiver definido)
*/
__global__ void pentear(int offset,int *vetor_device) {
    //calcula indice a partir da threadID
    int i = N_DIGITS-((blockIdx.x*MAX_THREADS+threadIdx.x)*2 + offset+1);
    //carrega valor para proxima casa
    vetor_device[i - 1] = vetor_device[i - 1]*10 + vetor_device[i] / (i + 2);
    //deixa o resto no lugar
    vetor_device[i] %= (i + 2);
    //vetor_device[i]++;
}

/*
Penteia alguma qtd de casas a partir de um offset, contando a partir do ultimo.
As casas são alternadas: nunca penteia duas casas adjecentes
*/
void pentear_parte(int tamanho, int offset, int *vetor ){
    int blocos_completos = tamanho/MAX_THREADS;
    int resto = tamanho%MAX_THREADS;

    //printf("\ni: %d\tr: %d\toff: %d\n",blocos_completos,resto,offset);
    if(blocos_completos>0){
        pentear<<<blocos_completos,MAX_THREADS>>>(offset, vetor);
        //printVec(vetor);
    }
    if(resto>0){
        pentear<<<1,resto>>>( (tamanho-resto)*2+offset, vetor);
        //printVec(vetor);
    }
    
    // int feitos = 0;
    // int n = MAX_THREADS<tamanho-feitos?MAX_THREADS:tamanho-feitos;
    // pentear<<<1,n>>>(feitos+offset,vetor);
    // feitos+=n;
    // while (feitos<tamanho)
    // {
    //     n = MAX_THREADS<tamanho-feitos?MAX_THREADS:tamanho-feitos;
    //     pentear<<<1,n>>>((feitos*2)+offset,vetor);
    //     feitos+=n;
    // }
}

/*
Obtem o proximo digito a partir de um vetor totalmente penteado e armazena no arquivo
*/
void extrair(FILE* arquivo, int *vetor){
    int n;
    //obtem o valor da primeira casa do vetor do device
    cudaMemcpy(&n, vetor, sizeof(int), cudaMemcpyDeviceToHost);
    //determina quociente, que é o digito
    int q = n / 2;
    //determina resto, que vai substituir nessa casa
    int r = n % 2;
    n = r;
    //salva digito no arquivo
    fputc(q+'0',arquivo);
    
    //Se quiser imprimir na tela, basta descomentar essa linha
    //putchar(q+'0');
    
    //copia resto para vetor do device
    cudaMemcpy(vetor,&n,sizeof(int), cudaMemcpyHostToDevice);
}

/*
Prepara o vetor a cada inicio de passagem do pente
*/
void preparar_primeiro(int *vetor){
    int n;
    //obtem valor da ultima casa
    cudaMemcpy(&n, &vetor[N_DIGITS-1], sizeof(int), cudaMemcpyDeviceToHost);
    //multiplica por 10 (como nao tem item anterior q faça isso)
    n*=10;
    //copia informacao para device
    cudaMemcpy(&vetor[N_DIGITS-1],&n,sizeof(int), cudaMemcpyHostToDevice);
}

int main(){
    //abre arquivo de registro
    FILE *arquivo = fopen("out.txt","w+");
    if(arquivo){
        int *vetor;
        // Aloca memoria no device
        cudaError_t malloc_result = cudaMalloc((void**)&vetor, sizeof(int) * N_DIGITS);
        
        // Se teve sucesso
        if (malloc_result == cudaSuccess)
        {
            fprintf(arquivo,"2.");
        
            // Preenche de 1s
            preencher(vetor);

            /*
            Penteia da ultima casa do vetor a penultima, depois da ultima a antepenultima, etc.
            até chegar numa seguinte a primeira
            */
            for (int i = 0; i < N_DIGITS/2; i++)
            {
                preparar_primeiro(vetor);
                //sao duas chamadas com offsets diferentes para pentear alternado, sem conflito
                pentear_parte(i+1,0,vetor);
                pentear_parte(i+1,1,vetor);
            }
            puts("Comecei a gerar digitos");
            //extrai primeiro digito menor digito depois da virgula de 'e' (deve ser 7)
            extrair(arquivo,vetor);    
            for (int _ = 0; _ <= N_DIGITS/2; _++)
            {
                preparar_primeiro(vetor);
                //sao duas chamadas com offsets diferentes para pentear alternado, sem conflito
                pentear_parte(N_DIGITS/2,0,vetor);
                pentear_parte(N_DIGITS/2,1,vetor);
                extrair(arquivo, vetor);
            }

            /*
            Penteia da ultima casa do vetor a segunda, depois da penultima a segunda, etc.
            até não ter nenhuma para pentear
            */
            for (int i = 0; i < N_DIGITS/2; i++)
            {
                //O offset que controla esse inicio
                pentear_parte(N_DIGITS/2-i-1, (i+1)*2,vetor);
                pentear_parte(N_DIGITS/2-i-1, (i+1)*2+1,vetor);
                extrair(arquivo, vetor);
            }
            // Libera memoria do device
            cudaFree(vetor);
        }
        else{
            fprintf(stderr,"%s\n",cudaGetErrorString(malloc_result));
        }       
    }
}