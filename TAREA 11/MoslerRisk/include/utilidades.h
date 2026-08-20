#ifndef UTILIDADES_H
#define UTILIDADES_H

/* Lee un entero validado desde teclado, repitiendo hasta que sea valido. */
int leerEntero(const char *mensaje);

/* Lee un entero validado dentro de un rango [minimo, maximo]. */
int leerEnteroRango(const char *mensaje, int minimo, int maximo);

/* Lee una cadena de texto (sin salto de linea), hasta 'tamano'-1 caracteres.
 * Rechaza cadenas vacias y cadenas con comas (romperian el formato CSV). */
void leerCadena(const char *mensaje, char *destino, int tamano);

/* Limpia el buffer de entrada tras una linea mas larga que el destino. */
void limpiarBuffer(void);

/* Pausa la ejecucion hasta que el usuario presione ENTER. */
void pausar(void);

#endif
