#include <stdio.h>
/* Cubo-2.
El programa calcula el cubo de los 10 primeros numeros naturales con la ayuda de una funcion. */
int cubo(void);
int I;

void main(void)
{
    int CUB;
    for (I = 1; I <= 10; I++)
    {
        CUB = cubo();
        printf("\nEl cubo de %d es: %d", I, CUB);
    }
}

int cubo(void)
{
    int I = 2;
    return (I*I*I);
}