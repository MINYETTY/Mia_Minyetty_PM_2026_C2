#include <stdio.h>

void main(void)
{
    char pl;
    char c[20];
    //pedir una letra
    printf("\nIngresa una letra del alfabeto:");
    pl = getchar ();

    //determinar si es mayuscula o minuscula
    if(pl >= 65 && pl <= 90)
    {
        printf("\n%c es minuscula y %c es mayuscula", pl,(pl+32));
    }

    if (pl >= 97 && pl <= 122)
    {
        printf ("\n%c es minuscula y %c es mayuscula", pl,(pl-32));
    }
}
