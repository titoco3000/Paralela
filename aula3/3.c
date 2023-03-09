// 3)
#include <stdio.h>

int main()
{
    int num = 9;
    printf("Numero pedido: %d\n\n", num);
    for (int i = 0;i < num;i++) {
        int j;
        for (j = 0;j < i;j++) {
            printf("  ");
        }
        for (;j < num - i;j++) {
            printf(" %d", j + 1);
        }
        printf("\n");
    }
}