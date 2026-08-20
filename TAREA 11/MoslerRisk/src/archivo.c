#include <stdio.h>
#include <string.h>
#include "../include/archivo.h"
#include "../include/memoria.h"

#define CARPETA_DATOS "data/"

/* Formato de una linea del CSV (definido en la Fase 5 del plan):
 * ID,Nombre,Categoria,Descripcion,F,S,P,E,A,V
 * Se asume que nombre/categoria/descripcion no contienen comas: eso se
 * garantiza en el momento de la entrada (ver utilidades.c: leerCadena). */

static void construirRuta(char *destino, int tamano, const char *nombreEmpresa) {
    snprintf(destino, tamano, "%s%s.csv", CARPETA_DATOS, nombreEmpresa);
}

int archivoExiste(const char *ruta) {
    FILE *f = fopen(ruta, "r");
    if (f == NULL) {
        return 0;
    }
    fclose(f);
    return 1;
}

static void cargarRiesgosDesdeArchivo(Sistema *sistema) {
    FILE *f = fopen(sistema->archivoActual, "r");
    if (f == NULL) {
        printf("Error: no se pudo abrir '%s' para lectura.\n", sistema->archivoActual);
        return;
    }

    Riesgo temp;
    while (fscanf(f, "%d,%49[^,],%29[^,],%149[^,],%d,%d,%d,%d,%d,%d\n",
                   &temp.id, temp.nombre, temp.categoria, temp.descripcion,
                   &temp.funcion, &temp.sustitucion, &temp.profundidad,
                   &temp.extension, &temp.agresion, &temp.vulnerabilidad) == 10) {
        agregarRiesgo(sistema, temp);
    }

    fclose(f);
}

int crearArchivo(Sistema *sistema, const char *nombreEmpresa) {
    char ruta[TAM_RUTA];
    construirRuta(ruta, sizeof(ruta), nombreEmpresa);

    if (archivoExiste(ruta)) {
        printf("Ya existe un archivo para '%s'. Usa 'Abrir archivo' en su lugar.\n", nombreEmpresa);
        return 0;
    }

    FILE *f = fopen(ruta, "w");
    if (f == NULL) {
        printf("Error: no se pudo crear el archivo '%s'.\n", ruta);
        return 0;
    }
    fclose(f);

    if (sistema->archivoAbierto) {
        liberarRiesgos(sistema);
    }

    strncpy(sistema->archivoActual, ruta, TAM_RUTA - 1);
    sistema->archivoActual[TAM_RUTA - 1] = '\0';
    sistema->archivoAbierto = 1;
    sistema->cantidad = 0;
    sistema->riesgos = NULL;

    printf("Archivo '%s' creado y abierto.\n", ruta);
    return 1;
}

int abrirArchivo(Sistema *sistema, const char *nombreEmpresa) {
    char ruta[TAM_RUTA];
    construirRuta(ruta, sizeof(ruta), nombreEmpresa);

    if (!archivoExiste(ruta)) {
        printf("No existe un archivo para '%s'. Usa 'Crear archivo' primero.\n", nombreEmpresa);
        return 0;
    }

    if (sistema->archivoAbierto) {
        liberarRiesgos(sistema);
    }

    strncpy(sistema->archivoActual, ruta, TAM_RUTA - 1);
    sistema->archivoActual[TAM_RUTA - 1] = '\0';
    sistema->archivoAbierto = 1;
    sistema->cantidad = 0;
    sistema->riesgos = NULL;

    cargarRiesgosDesdeArchivo(sistema);

    printf("Archivo '%s' abierto. %d riesgo(s) cargado(s).\n", ruta, sistema->cantidad);
    return 1;
}

int guardarRiesgos(const Sistema *sistema) {
    FILE *f = fopen(sistema->archivoActual, "w");
    if (f == NULL) {
        printf("Error: no se pudo abrir '%s' para escritura.\n", sistema->archivoActual);
        return 0;
    }

    for (int i = 0; i < sistema->cantidad; i++) {
        const Riesgo *r = &sistema->riesgos[i];
        fprintf(f, "%d,%s,%s,%s,%d,%d,%d,%d,%d,%d\n",
                r->id, r->nombre, r->categoria, r->descripcion,
                r->funcion, r->sustitucion, r->profundidad,
                r->extension, r->agresion, r->vulnerabilidad);
    }

    fclose(f);
    printf("Guardado: %d riesgo(s) en '%s'.\n", sistema->cantidad, sistema->archivoActual);
    return 1;
}
