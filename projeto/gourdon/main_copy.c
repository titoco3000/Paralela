#include <stdio.h>

#define PRECISAO 100000
int main(){
    int N=PRECISAO,n=N,a[PRECISAO+9],x;
    while(--n){
        a[n]=1+1/n;
    }
    for(;N>9;printf("%d",x))
        for(n=N--;--n;a[n]=x%n,x=10*a[n-1]+x/n);

    return 0;
}