#include <stdio.h>

int main(){
    FILE* ref_file = fopen("ref.txt", "r");
    FILE* out_file = fopen("out.txt", "r");
    if (ref_file == NULL || out_file == NULL)
        return 0; //could not open file

    char a;
    char b;
    long unsigned int i;
    for (i = 0; (a = fgetc(out_file)) != EOF; i++){
        if ((b = fgetc(ref_file)) == EOF){
            printf("Pelo menos ");
            break;
        }
        if(a!=b){
            printf("%c != %c\n",a,b);
            break;
        }
    }
    printf("%lu digitos corretos\n",i);
}