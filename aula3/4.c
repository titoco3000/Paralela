#include <stdio.h>

// Counting sort
void sort_str(char* str) {
    int count[255];
    int i;
    for (i = 0; i < 255; i++)
        count[i] = 0;
    for (i = 0; str[i] != 0; i++)
        count[str[i]]++;
    int s = 0;
    for (i = 0; i < 255; i++)
        while (count[i] > 0) {
            str[s] = i;
            count[i]--;
            s++;
        }
}

int main() {
    char pessoa_a[] = "Fernando";
    char pessoa_b[] = "Alejandro";
    sort_str(pessoa_a);
    sort_str(pessoa_b);
    puts(pessoa_a);
    puts(pessoa_b);
}
