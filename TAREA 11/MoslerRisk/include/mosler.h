#ifndef MOSLER_H
#define MOSLER_H

#include "riesgo.h"

/* Calculos individuales del Metodo Mosler.
 * Reciben un Riesgo ya cargado con F,S,P,E,A,V y devuelven el valor
 * correspondiente. No modifican el Riesgo ni conocen archivos/memoria. */
int calcularImportancia(const Riesgo *riesgo);      /* I = F x S */
int calcularDanos(const Riesgo *riesgo);             /* D = P x E */
int calcularCaracter(const Riesgo *riesgo);          /* C = I + D */
int calcularProbabilidad(const Riesgo *riesgo);      /* Pb = A x V */
int calcularRiesgoEstimado(const Riesgo *riesgo);    /* ER = C x Pb */

/* Devuelve una clasificacion segun la tabla estandar del metodo Mosler:
 * 2-250 Muy bajo, 251-500 Bajo, 501-750 Medio, 751-1000 Alto,
 * 1001-1250 Muy alto. */
const char *clasificarRiesgo(int riesgoEstimado);

/* Calcula todos los valores de una vez, para no repetir calculos al
 * mostrar un riesgo detallado. */
void calcularMosler(const Riesgo *riesgo, int *importancia, int *danos,
                     int *caracter, int *probabilidad, int *riesgoEstimado);

#endif
