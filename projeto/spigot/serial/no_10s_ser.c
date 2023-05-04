/*
https://youtu.be/nleB7uPtQxQ
https://adamcrussell.livejournal.com/6924.html
https://github.com/zachratliff22/EulerSpigot

*/

#include <stdio.h>
#include <stdlib.h>

//#define PRINT_STEP_BY_STEP

#ifdef PRINT_STEP_BY_STEP
void print_equation(int* a, int sa){
    
    printf("1/%d * (%d ",2,a[0]);
    for (int i = 1; i < sa; i++)
    {
        printf(" + 1/%d * (%d",i+1,a[i]);
    }
    for (int i = 1; i < sa; i++)
        printf(")");
    puts("");
}
#endif

void spigot(int* a, int sa, char* buffer, int* bufoc) {
#ifdef PRINT_STEP_BY_STEP
    print_equation(a,sa);
#endif
    int q;
    int r;

    a[sa-1]*=10;

    //do ultimo ao primeiro elemento do vetor (dir à esq)
    for (int i = sa - 1; i > 0; i--)
    {
#ifdef PRINT_STEP_BY_STEP
        printf("realiza carry no index %d\n",i);
#endif
        //+2 proque a fração que cada posição representa começa a partir do 2. O index 0
        //representa 1/2, index 1 1/3, etc
        q = a[i] / (i + 2);
        r = a[i] % (i + 2);
        a[i - 1]*=10;
        a[i - 1] += q; // item à esq = quociente
        a[i] = r; // atual = resto
#ifdef PRINT_STEP_BY_STEP
        print_equation(a,sa);
#endif
    }
#ifdef PRINT_STEP_BY_STEP
    puts("realiza carry no 1º elemento");
#endif
    q = a[0] / 2;
    r = a[0] % 2;
    a[0] = r;
#ifdef PRINT_STEP_BY_STEP
    print_equation(a,sa);
    printf("\ndigito = %d\n\n",q);
#endif
    buffer[(*bufoc)++] = 48 + q;
}

int main() {
    int numDigits = 1000;
    int *valueArr = malloc(sizeof(int)*numDigits);

    //preenche o vetor com 1s
    for (int i = 0; i < numDigits; i++)
        valueArr[i] = 1;

    char *buffer =malloc(sizeof(char)*numDigits+3);
    buffer[0] = '2';
    buffer[1] = '.';
    int bufoc = 2;
    buffer[numDigits + 2] = 0;

    for (int digit = 0; digit < numDigits; digit++)
        spigot(valueArr, numDigits, buffer, &bufoc);

    FILE *fp = fopen("gerado.txt", "w+");
    if (fp != NULL)
    {
        fputs(buffer, fp);
        fclose(fp);
    }
#ifdef PRINT_STEP_BY_STEP
    puts(buffer);
#endif
    free(buffer);
    free(valueArr);
}
