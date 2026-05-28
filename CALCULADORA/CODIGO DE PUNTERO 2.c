#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    int a = 10;
    int b = 5;
    int *pi;//declaracion de puntero
    int *pi2;
    pi = (int *)malloc(sizeof(int));
    pi2 = (int *)malloc(sizeof(int));
    *pi = 300;
    *pi2 = 100;
    printf("\nValor de a: %i\n",a);
    printf("\nValor de b: %i\n",b);
    printf("\nValor en pi: %i\n",*pi);
    printf("\nSuma de a + b + *pi: %i",a+b+*pi);
    printf("\nSuma de *pi + *pi2: %i",*pi2+*pi);
    while(1)
    {
       pi = (int *)malloc(sizeof(int));
    }
    free(pi);
    free(pi2);
    return 0;
    pi = &b;
    printf("\nValor de b: %i\n",b);
    printf("\nValor de b con puntero: %i\n",*pi);
    *pi = 50;
    printf("\nValor de b: %i\n",b);
    printf("\nValor de b con puntero: %i\n",*pi);
    printf("\nValor de a: %i\n",a);
    pi = &a;
    *pi = 20;
    printf("\nValor de a: %i\n",a);
 
 
    return 0;
    printf("\n-------------\n");
    *pi = 100;
    printf("\nValor dea: %i\n",a);
    printf("\nValor dea con puntero: %i\n",*pi);
 
    printf("\n-------------\n");
    a = 200;
    printf("\nValor dea: %i\n",a);
    printf("\nValor dea con puntero: %i\n",*pi);
 
    return 0;
}