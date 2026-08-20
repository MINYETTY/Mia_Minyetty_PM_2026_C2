#ifndef MEMORIA_H
#define MEMORIA_H

#include "riesgo.h"

/* Agrega 'nuevo' al arreglo dinamico de sistema->riesgos con realloc
 * (crece exactamente un espacio) y actualiza sistema->cantidad.
 * Si realloc falla, el arreglo original NO se pierde ni se corrompe. */
void agregarRiesgo(Sistema *sistema, Riesgo nuevo);

/* Elimina el riesgo en la posicion 'indice': recorre los siguientes un
 * lugar hacia atras y reduce el arreglo con realloc. */
void eliminarRiesgoArreglo(Sistema *sistema, int indice);

/* Libera toda la memoria del arreglo y deja el Sistema limpio
 * (cantidad en 0, puntero en NULL). */
void liberarRiesgos(Sistema *sistema);

#endif
