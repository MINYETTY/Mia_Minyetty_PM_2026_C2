#ifndef RIESGO_H
#define RIESGO_H

/*
 * riesgo.h
 * -----------------------------------------------------------------------
 * Define la estructura de un riesgo individual (Riesgo), la estructura
 * que agrupa todos los riesgos en memoria junto con el estado del archivo
 * abierto (Sistema), y las funciones para crear, modificar, eliminar,
 * buscar y mostrar riesgos.
 */

#define TAM_NOMBRE       50
#define TAM_DESCRIPCION  150
#define TAM_CATEGORIA    30
#define TAM_RUTA         100

/* Un riesgo individual de la empresa.
 * I, D, C, Pb, ER y la clasificacion NO se almacenan aqui: se calculan
 * bajo demanda con mosler.h para que nunca queden desactualizados
 * respecto a F,S,P,E,A,V. */
typedef struct {
    int  id;
    char nombre[TAM_NOMBRE];
    char descripcion[TAM_DESCRIPCION];
    char categoria[TAM_CATEGORIA];

    int funcion;
    int sustitucion;
    int profundidad;
    int extension;
    int agresion;
    int vulnerabilidad;
} Riesgo;

/* Agrupa todos los riesgos actualmente en memoria y el estado del
 * archivo con el que se esta trabajando. */
typedef struct {
    Riesgo *riesgos;
    int     cantidad;
    char    archivoActual[TAM_RUTA];
    int     archivoAbierto;
} Sistema;

/* Pide por teclado todos los datos de un riesgo nuevo (el id se asigna
 * automaticamente) y lo agrega al sistema. */
void crearRiesgo(Sistema *sistema);

/* Pide un id, busca el riesgo y permite modificar sus valores. */
void modificarRiesgo(Sistema *sistema);

/* Pide un id y elimina ese riesgo del sistema (usa memoria.h). */
void eliminarRiesgo(Sistema *sistema);

/* Devuelve el indice del riesgo con ese id, o -1 si no existe. */
int buscarRiesgoPorId(const Sistema *sistema, int id);

/* Imprime un resumen de una linea de un riesgo. */
void mostrarRiesgo(const Riesgo *riesgo);

/* Imprime todos los datos de un riesgo, incluyendo el calculo Mosler. */
void mostrarRiesgoDetallado(const Riesgo *riesgo);

/* Imprime todos los riesgos del sistema. */
void mostrarRiesgos(const Sistema *sistema);

/* Ordena los riesgos del sistema de mayor a menor gravedad (ER). */
void ordenarPorGravedad(Sistema *sistema);

/* Busca riesgos cuyo nombre contenga 'texto' y los muestra. */
void buscarPorNombre(const Sistema *sistema, const char *texto);

/* Imprime cuantos riesgos hay por clasificacion y cual es el mas grave. */
void mostrarResumen(const Sistema *sistema);

#endif /* RIESGO_H */
