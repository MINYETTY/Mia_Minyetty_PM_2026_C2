#include <stdio.h>

/* Archivos y caracteres.
El programa lee caracteres de un archivo.*/

void main(void)
{
    char p1;
    FILE *ar;
    if ((ar = fopen("c:\\temp\\arc.txt", "r")) != NULL)
    {
        while (!feof(ar))
        {
            p1 = fgetc(ar);
            putchar(p1);
        }
        fclose(ar);
    }
    else
       printf("No se puede abrir el archivo");
}