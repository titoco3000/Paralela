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

void multiplicar_linha(int** multiplicando, int largura, int linha, int multiplicador) {
    for (int i = 0; i < largura; i++)
        multiplicando[linha][i] *= multiplicador;
}
void multiplicar_coluna(int** multiplicando, int altura, int coluna, int multiplicador) {
    for (int i = 0; i < altura; i++)
        multiplicando[i][coluna] *= multiplicador;
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
    printf("linha 0 *2, coluna 1 *5\n");
    multiplicar_linha(matriz, m_size, 0, 2);
    multiplicar_coluna(matriz, m_size, 1, 5);
    for (int i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
        {
            printf(" %d", matriz[i][j]);
        }
        printf("\n");
    }

    liberar_matriz(matriz, m_size);
}