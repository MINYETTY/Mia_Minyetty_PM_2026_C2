#include <stdio.h>

int main(void)
{
    FILE *ar;
    char frase[255];
    char c;

    // 1. Escribir en el archivo
    ar = fopen("datos.txt", "w");
    if (ar == NULL) {
        printf("Error al crear el archivo.\n");
        return 1;
    }

    printf("Escribe tu frase: ");
    fgets(frase, sizeof(frase), stdin);
    fprintf(ar, "%s", frase);
    fclose(ar);

    // 2. Leer del archivo
    ar = fopen("datos.txt", "r");
    if (ar != NULL) {
        printf("\nContenido del archivo:\n");
        // Leemos carácter a carácter correctamente
        while ((c = fgetc(ar)) != EOF) {
            putchar(c);
        }
        fclose(ar);
    }

    return 0;
}