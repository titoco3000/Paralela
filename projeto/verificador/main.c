#include <stdio.h>
#include <unistd.h>

int main(){
    FILE* ref_file = fopen("ref.txt", "r");
    FILE* out_file = fopen("out.txt", "r+");
    if (ref_file == NULL || out_file == NULL)
        return 1; //could not open file

    char a;
    char b;
    long unsigned int i;
    while(1){
        a = fgetc(out_file);
        b = fgetc(ref_file);
        if (b == EOF){
            printf("Pelo menos ");
            break;
        }
        if(a == EOF){
            printf("Inteiro correto!\n");
            break;
        }
        if(a!=b){
            printf("Erro em %lu (%c(%d)) != %c)\n",i,a,a,b);
            fprintf(out_file, " aqui ");
            //sleep(1);
            break;
        }
        i++;    
    }
    printf("%lu digitos corretos\n",i);
    fclose(ref_file);
    fclose(out_file);
}