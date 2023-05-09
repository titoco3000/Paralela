#include <stdio.h>

#define PRECISAO 100000
//ultimos 9 são imprecisos
#define EXTRA 0

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

int main(){
    FILE *fp = fopen("out.txt", "w+");
    if (fp != NULL)
    {
        int a[PRECISAO];
        int x;

        int n=PRECISAO;
#ifdef PRINT_STEP_BY_STEP
    for (int i = 0; i < PRECISAO; i++)
        a[i] = 1;
    print_equation(a,PRECISAO);
#endif
        
        while(--n){
            a[n]=x%n;
            x=10+x/n;
#ifdef PRINT_STEP_BY_STEP
            printf("10*1+%d/%d\n",x,n);
            print_equation(a,PRECISAO);
#endif
        }
        fprintf(fp,"2.7");
        
#ifdef PRINT_STEP_BY_STEP
            printf("inicio feito\n");
#endif
        for (int i = PRECISAO; i; i--)
        {
            n=PRECISAO;
            while(--n){
                a[n]=x%n;
                x=10*a[n-1]+x/n;
#ifdef PRINT_STEP_BY_STEP
                printf("10*%d+%d/%d\n",a[n-1],x,n);
                print_equation(a,PRECISAO);
#endif
            }
            fprintf(fp,"%d",x);
        }
    }

    return 0;
}
