#include <stdio.h>
#include <string.h>
#include "../include/utilidades.h"

void limpiarBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descarta caracteres sobrantes */
    }
}

int leerEntero(const char *mensaje) {
    char linea[64];
    int valor;
    int valido;

    do {
        printf("%s", mensaje);
        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            continue;
        }
        valido = (sscanf(linea, "%d", &valor) == 1);
        if (!valido) {
            printf("Entrada invalida, intenta de nuevo.\n");
        }
    } while (!valido);

    return valor;
}

int leerEnteroRango(const char *mensaje, int minimo, int maximo) {
    int valor;

    do {
        valor = leerEntero(mensaje);
        if (valor < minimo || valor > maximo) {
            printf("Debe estar entre %d y %d.\n", minimo, maximo);
        }
    } while (valor < minimo || valor > maximo);

    return valor;
}

void leerCadena(const char *mensaje, char *destino, int tamano) {
    int valido = 0;

    do {
        printf("%s", mensaje);
        if (fgets(destino, tamano, stdin) == NULL) {
            destino[0] = '\0';
            continue;
        }

        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        } else {
            limpiarBuffer();
        }

        if (strlen(destino) == 0) {
            printf("No puede estar vacio.\n");
            continue;
        }
        if (strchr(destino, ',') != NULL) {
            printf("No puede contener comas (se usan para separar el CSV).\n");
            continue;
        }
        valido = 1;
    } while (!valido);
}

void pausar(void) {
    printf("Presiona ENTER para continuar...");
    getchar();
}
