#ifndef UTILIDADES_H
#define UTILIDADES_H

/*
 * ============================================================
 * Archivo: utilidades.h
 * Propósito:
 * Entrada segura y funciones generales.
 * ============================================================
 */

void limpiarBuffer(void);
void pausar(void);

int leerEntero(const char *mensaje);
double leerDouble(const char *mensaje);

int leerEnteroPositivo(const char *mensaje);
double leerDoublePositivo(const char *mensaje);
double leerDoubleNoNegativo(const char *mensaje);

int leerEnteroRango(
    const char *mensaje,
    int minimo,
    int maximo
);

void leerCadena(
    const char *mensaje,
    char *destino,
    int tamanio
);

#endif
