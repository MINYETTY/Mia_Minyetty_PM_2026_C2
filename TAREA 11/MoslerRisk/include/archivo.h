#ifndef ARCHIVO_H
#define ARCHIVO_H

#include "riesgo.h"

/* Devuelve 1 si el archivo existe y se puede abrir para lectura, 0 si no. */
int archivoExiste(const char *ruta);

/* Crea un archivo CSV nuevo (vacio) para 'nombreEmpresa' dentro de data/.
 * Deja sistema->archivoActual y sistema->archivoAbierto configurados.
 * Devuelve 1 si tuvo exito, 0 si el archivo ya existia o hubo error. */
int crearArchivo(Sistema *sistema, const char *nombreEmpresa);

/* Abre (sin crear) un archivo CSV existente y carga sus riesgos.
 * Devuelve 1 si tuvo exito, 0 si el archivo no existe o hubo error. */
int abrirArchivo(Sistema *sistema, const char *nombreEmpresa);

/* Guarda el contenido actual de sistema->riesgos en sistema->archivoActual,
 * sobreescribiendo el archivo. Devuelve 1 si tuvo exito, 0 si hubo error. */
int guardarRiesgos(const Sistema *sistema);

#endif
