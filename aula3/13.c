#include <stdio.h>

void remove_at_index(char str[100], int index) {
    for (int i = index; i < 99; i++)
        str[i] = str[i + 1];
    str[99] = 0;

}

int main()
{
    char str[100] = "Abracadabra";
    remove_at_index(str, 5);
    puts(str);
}