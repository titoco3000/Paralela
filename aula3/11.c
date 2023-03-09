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

int main()
{
    srand(32120613);

    int m_size = 3;
    printf("digite o tamanho da matriz: %d\n", m_size);
    int** matriz = criar_matriz(m_size, m_size);
    int i;
    for (i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
        {
            matriz[i][j] = rand() % 10;
            printf(" %d", matriz[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < m_size; i++)
        matriz[1][i] += matriz[0][i];

    printf("\n");
    for (i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
            printf(" %d", matriz[i][j]);
        printf("\n");
    }

    for (i = 0; i < m_size; i++)
        matriz[1][i] *= matriz[0][i];

    printf("\n");
    for (i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
            printf(" %d", matriz[i][j]);
        printf("\n");
    }

    liberar_matriz(matriz, m_size);
}