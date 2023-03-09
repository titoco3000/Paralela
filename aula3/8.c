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

int** criar_transposta(int** matriz, int altura, int largura) {
    int** t = criar_matriz(largura, altura);
    for (int i = 0; i < largura; i++)
        for (int j = 0; j < altura; j++)
            t[i][j] = matriz[j][i];
    return t;
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
            matriz[i][j] = rand() % 10;
            printf(" %d", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\ntransposta:\n");
    int** transposta = criar_transposta(matriz, m_size, m_size);
    for (int i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
            printf(" %d", transposta[i][j]);
        printf("\n");
    }

    liberar_matriz(matriz, m_size);
    liberar_matriz(transposta, m_size);
}