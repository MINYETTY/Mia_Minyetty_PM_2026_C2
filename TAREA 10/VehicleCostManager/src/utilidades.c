/*
 * ============================================================
 * Archivo: utilidades.c
 * Propósito:
 * Implementación de funciones para leer y validar datos.
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/utilidades.h"

void limpiarBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* Descarta caracteres restantes de la entrada. */
    }
}

void pausar(void)
{
    printf("\nPresione ENTER para continuar...");
    limpiarBuffer();
    getchar();
}

int leerEntero(const char *mensaje)
{
    int valor;

    while (1)
    {
        printf("%s", mensaje);

        if (scanf("%d", &valor) == 1)
        {
            limpiarBuffer();
            return valor;
        }

        printf("Entrada invalida. Debe introducir un numero entero.\n");
        limpiarBuffer();
    }
}

double leerDouble(const char *mensaje)
{
    double valor;

    while (1)
    {
        printf("%s", mensaje);

        if (scanf("%lf", &valor) == 1)
        {
            limpiarBuffer();
            return valor;
        }

        printf("Entrada invalida. Debe introducir un numero.\n");
        limpiarBuffer();
    }
}

int leerEnteroPositivo(const char *mensaje)
{
    int valor;

    do
    {
        valor = leerEntero(mensaje);

        if (valor <= 0)
        {
            printf("El valor debe ser mayor que cero.\n");
        }

    } while (valor <= 0);

    return valor;
}

double leerDoublePositivo(const char *mensaje)
{
    double valor;

    do
    {
        valor = leerDouble(mensaje);

        if (valor <= 0)
        {
            printf("El valor debe ser mayor que cero.\n");
        }

    } while (valor <= 0);

    return valor;
}

double leerDoubleNoNegativo(const char *mensaje)
{
    double valor;

    do
    {
        valor = leerDouble(mensaje);

        if (valor < 0)
        {
            printf("El valor no puede ser negativo.\n");
        }

    } while (valor < 0);

    return valor;
}

int leerEnteroRango(
    const char *mensaje,
    int minimo,
    int maximo
)
{
    int valor;

    do
    {
        valor = leerEntero(mensaje);

        if (valor < minimo || valor > maximo)
        {
            printf(
                "El valor debe estar entre %d y %d.\n",
                minimo,
                maximo
            );
        }

    } while (valor < minimo || valor > maximo);

    return valor;
}

void leerCadena(
    const char *mensaje,
    char *destino,
    int tamanio
)
{
    size_t longitud;

    while (1)
    {
        printf("%s", mensaje);

        if (fgets(destino, tamanio, stdin) == NULL)
        {
            destino[0] = '\0';
            continue;
        }

        longitud = strlen(destino);

        if (longitud > 0 && destino[longitud - 1] == '\n')
        {
            destino[longitud - 1] = '\0';
        }
        else
        {
            limpiarBuffer();
        }

        if (strlen(destino) == 0)
        {
            printf("Este campo no puede quedar vacio.\n");
        }
        else
        {
            return;
        }
    }
}
