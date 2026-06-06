#include <stdio.h>
/* Multiplo.
El programa, al recibir como datos dos numeros enteros, determina si el segundo es multiplo del primero. */
int multiple(int, int);

void main(void)
{

    int NU1, NU2, RES;
    printf("\nIngresa los dos numeros: ");
    scanf("%d %d", &NU1, &NU2);
    RES = multiple(NU1, NU2);
    if (RES)
        printf("\nEl segundo numero es multiplo del primero");
    else        printf("\nEl segundo numero no es multiplo del primero");
}

int multiple(int N1, int N2)
{

    int RES;
    if ((N2 % N1) == 0)
        RES = 1;
    else      
        RES = 0;
    return (RES);
}