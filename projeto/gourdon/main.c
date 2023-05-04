#include <stdio.h>

#define PRECISAO 1000000
int main(){
    int N=PRECISAO,n=N,a[PRECISAO+9],x;
    while(--n){
        a[n]=1+1/n;
    }
    FILE* out_file = fopen("out.txt", "w");
    for(;N>9;putc(x,out_file))
        for(n=N--;--n;a[n]=x%n,x=10*a[n-1]+x/n);

    return 0;
}