#include <stdio.h>
#include <stdlib.h>

int** criar_matriz(int altura, int largura)
{
    int** matriz = (int**)malloc(sizeof(int*) * altura);
    for (int i = 0; i < altura; i++)
        matriz[i] = (int*)malloc(sizeof(int) * largura);
    return matriz;
}
void liberar_matriz(int** matriz, int altura)
{
    for (int i = 0; i < altura; i++)
        free(matriz[i]);
    free(matriz);
}
void modular(int** matriz, int altura, int largura) {
    for (int i = 0; i < altura; i++)
        for (int j = 0; j < largura; j++)
        {
            if (matriz[i][j] < 0)
                matriz[i][j] *= -1;
        }
}

int main()
{
    srand(32120613);

    int m_size = 3;
    printf("digite o tamanho da matriz: %d\n", m_size);
    int** matriz = criar_matriz(m_size, m_size);
    for (int i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
        {
            matriz[i][j] = rand() % 20 - 10;
            printf(" %d", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\nmodulo:\n");
    modular(matriz, m_size, m_size);
    for (int i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
            printf(" %d", matriz[i][j]);
        printf("\n");
    }

    liberar_matriz(matriz, m_size);
}