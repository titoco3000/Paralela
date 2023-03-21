# include <stdio.h>

int main()
{
   unsigned long long i, num, j;
   printf ("Enter the number: ");
   scanf ("%llu", &num);
   j = num;

   for (i=1; j > 1; j = j -1) {
         i=i*j;
   }

   printf("The factorial of %llu is %llu\n",num,i);
}
