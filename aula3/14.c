#include <stdio.h>

void add_at_index(char str[100], int index, char c) {
    for (int i = 98; i > index; i--)
        str[i] = str[i - 1];
    str[index] = c;

}

int main()
{
    char str[100] = "Abracadabra";
    add_at_index(str, 5, 'X');
    puts(str);
}