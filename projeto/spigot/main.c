/*
https://youtu.be/nleB7uPtQxQ
https://adamcrussell.livejournal.com/6924.html
https://github.com/zachratliff22/EulerSpigot

*/

#include <stdio.h>

#define DIGITOS 100000

void spigot(int* a, int sa, char* buffer, int* bufoc) {

    //multiplica todo o vetor por 10
    for (int i = 0; i < sa; i++)
        a[i] *= 10;

    int q;
    int r;

    //do ultimo ao primeiro elemento do vetor (dir à esq)
    for (int i = sa - 1; i > 0; i--)
    {
        q = a[i] / (i + 2);
        r = a[i] % (i + 2);
        a[i - 1] += q; // item à esq = quociente
        a[i] = r; // atual = resto
    }

    q = a[0] / 2;
    r = a[0] % 2;
    a[0] = r;

    buffer[(*bufoc)++] = 48 + q;
}

int main() {
    int numDigits = DIGITOS;
    int valueArr[DIGITOS];

    //preenche o vetor com 1s
    for (int i = 0; i < numDigits; i++)
        valueArr[i] = 1;

    char buffer[DIGITOS + 3] = "2.";
    int bufoc = 2;
    buffer[numDigits + 2] = 0;

    for (int digit = 0; digit < numDigits; digit++)
        spigot(valueArr, numDigits, buffer, &bufoc);

    puts(buffer);
}
