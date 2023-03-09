#include <stdio.h>

int indexof(char* str, char c) {
    for (int i = 0; str[i] != 0; i++)
        if (str[i] == c)
            return i;
    return -1;

}

int main()
{
    char* str = "Abracadabra";
    printf("index of %c in %s: %d\n", 'c', str, indexof(str, 'c'));
}