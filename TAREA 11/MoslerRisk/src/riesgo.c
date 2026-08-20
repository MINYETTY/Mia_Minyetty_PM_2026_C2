#include <stdio.h>
#include <string.h>
#include "../include/riesgo.h"
#include "../include/mosler.h"
#include "../include/utilidades.h"
#include "../include/memoria.h"

static int siguienteId(const Sistema *sistema) {
    int maximo = 0;
    for (int i = 0; i < sistema->cantidad; i++) {
        if (sistema->riesgos[i].id > maximo) {
            maximo = sistema->riesgos[i].id;
        }
    }
    return maximo + 1;
}

void crearRiesgo(Sistema *sistema) {
    Riesgo nuevo;
    nuevo.id = siguienteId(sistema);

    printf("\n--- Nuevo riesgo (id %d) ---\n", nuevo.id);
    leerCadena("Nombre: ", nuevo.nombre, TAM_NOMBRE);
    leerCadena("Categoria: ", nuevo.categoria, TAM_CATEGORIA);
    leerCadena("Descripcion: ", nuevo.descripcion, TAM_DESCRIPCION);

    nuevo.funcion        = leerEnteroRango("Funcion (1-5): ", 1, 5);
    nuevo.sustitucion    = leerEnteroRango("Sustitucion (1-5): ", 1, 5);
    nuevo.profundidad    = leerEnteroRango("Profundidad (1-5): ", 1, 5);
    nuevo.extension      = leerEnteroRango("Extension (1-5): ", 1, 5);
    nuevo.agresion       = leerEnteroRango("Agresion (1-5): ", 1, 5);
    nuevo.vulnerabilidad = leerEnteroRango("Vulnerabilidad (1-5): ", 1, 5);

    agregarRiesgo(sistema, nuevo);
    printf("Riesgo creado con id %d.\n", nuevo.id);
}

int buscarRiesgoPorId(const Sistema *sistema, int id) {
    for (int i = 0; i < sistema->cantidad; i++) {
        if (sistema->riesgos[i].id == id) {
            return i;
        }
    }
    return -1;
}

void modificarRiesgo(Sistema *sistema) {
    if (sistema->cantidad == 0) {
        printf("No hay riesgos cargados.\n");
        return;
    }

    int id = leerEntero("Id del riesgo a modificar: ");
    int indice = buscarRiesgoPorId(sistema, id);

    if (indice == -1) {
        printf("No existe un riesgo con id %d.\n", id);
        return;
    }

    Riesgo *r = &sistema->riesgos[indice];

    printf("\n--- Modificando riesgo %d (ingresa los nuevos valores) ---\n", id);
    leerCadena("Nombre: ", r->nombre, TAM_NOMBRE);
    leerCadena("Categoria: ", r->categoria, TAM_CATEGORIA);
    leerCadena("Descripcion: ", r->descripcion, TAM_DESCRIPCION);

    r->funcion        = leerEnteroRango("Funcion (1-5): ", 1, 5);
    r->sustitucion    = leerEnteroRango("Sustitucion (1-5): ", 1, 5);
    r->profundidad    = leerEnteroRango("Profundidad (1-5): ", 1, 5);
    r->extension      = leerEnteroRango("Extension (1-5): ", 1, 5);
    r->agresion       = leerEnteroRango("Agresion (1-5): ", 1, 5);
    r->vulnerabilidad = leerEnteroRango("Vulnerabilidad (1-5): ", 1, 5);

    printf("Riesgo %d actualizado.\n", id);
}

void eliminarRiesgo(Sistema *sistema) {
    if (sistema->cantidad == 0) {
        printf("No hay riesgos cargados.\n");
        return;
    }

    int id = leerEntero("Id del riesgo a eliminar: ");
    int indice = buscarRiesgoPorId(sistema, id);

    if (indice == -1) {
        printf("No existe un riesgo con id %d.\n", id);
        return;
    }

    eliminarRiesgoArreglo(sistema, indice);
    printf("Riesgo %d eliminado.\n", id);
}

void mostrarRiesgo(const Riesgo *riesgo) {
    int er = calcularRiesgoEstimado(riesgo);
    printf("[%d] %-20s %-15s ER=%-5d %s\n",
           riesgo->id, riesgo->nombre, riesgo->categoria, er, clasificarRiesgo(er));
}

void mostrarRiesgoDetallado(const Riesgo *riesgo) {
    int importancia, danos, caracter, probabilidad, riesgoEstimado;
    calcularMosler(riesgo, &importancia, &danos, &caracter, &probabilidad, &riesgoEstimado);

    printf("\n--- Riesgo %d ---\n", riesgo->id);
    printf("Nombre:        %s\n", riesgo->nombre);
    printf("Categoria:     %s\n", riesgo->categoria);
    printf("Descripcion:   %s\n", riesgo->descripcion);
    printf("F=%d S=%d P=%d E=%d A=%d V=%d\n",
           riesgo->funcion, riesgo->sustitucion, riesgo->profundidad,
           riesgo->extension, riesgo->agresion, riesgo->vulnerabilidad);
    printf("Importancia (I=FxS):       %d\n", importancia);
    printf("Danos (D=PxE):             %d\n", danos);
    printf("Caracter (C=I+D):          %d\n", caracter);
    printf("Probabilidad (Pb=AxV):     %d\n", probabilidad);
    printf("Riesgo Estimado (ER=CxPb): %d\n", riesgoEstimado);
    printf("Clasificacion:             %s\n", clasificarRiesgo(riesgoEstimado));
}

void mostrarRiesgos(const Sistema *sistema) {
    if (sistema->cantidad == 0) {
        printf("No hay riesgos cargados.\n");
        return;
    }

    printf("\n%-4s %-20s %-15s %-7s %s\n", "ID", "NOMBRE", "CATEGORIA", "ER", "CLASE");
    for (int i = 0; i < sistema->cantidad; i++) {
        mostrarRiesgo(&sistema->riesgos[i]);
    }
}

void ordenarPorGravedad(Sistema *sistema) {
    for (int i = 0; i < sistema->cantidad - 1; i++) {
        for (int j = 0; j < sistema->cantidad - 1 - i; j++) {
            int erJ  = calcularRiesgoEstimado(&sistema->riesgos[j]);
            int erJ1 = calcularRiesgoEstimado(&sistema->riesgos[j + 1]);
            if (erJ < erJ1) {
                Riesgo temp = sistema->riesgos[j];
                sistema->riesgos[j] = sistema->riesgos[j + 1];
                sistema->riesgos[j + 1] = temp;
            }
        }
    }
    printf("Riesgos ordenados de mayor a menor gravedad.\n");
}

void buscarPorNombre(const Sistema *sistema, const char *texto) {
    int encontrados = 0;

    for (int i = 0; i < sistema->cantidad; i++) {
        if (strstr(sistema->riesgos[i].nombre, texto) != NULL) {
            mostrarRiesgo(&sistema->riesgos[i]);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Ningun riesgo coincide con '%s'.\n", texto);
    }
}

void mostrarResumen(const Sistema *sistema) {
    if (sistema->cantidad == 0) {
        printf("No hay riesgos cargados.\n");
        return;
    }

    int conteo[5] = {0}; /* muy bajo, bajo, medio, alto, muy alto */
    int indiceMasGrave = 0;
    int erMasGrave = -1;

    for (int i = 0; i < sistema->cantidad; i++) {
        int er = calcularRiesgoEstimado(&sistema->riesgos[i]);
        const char *clase = clasificarRiesgo(er);

        if (strcmp(clase, "Muy bajo") == 0) conteo[0]++;
        else if (strcmp(clase, "Bajo") == 0) conteo[1]++;
        else if (strcmp(clase, "Medio") == 0) conteo[2]++;
        else if (strcmp(clase, "Alto") == 0) conteo[3]++;
        else conteo[4]++;

        if (er > erMasGrave) {
            erMasGrave = er;
            indiceMasGrave = i;
        }
    }

    printf("\n--- Resumen (%d riesgos) ---\n", sistema->cantidad);
    printf("Muy bajo: %d | Bajo: %d | Medio: %d | Alto: %d | Muy alto: %d\n",
           conteo[0], conteo[1], conteo[2], conteo[3], conteo[4]);
    printf("Riesgo mas grave:\n");
    mostrarRiesgo(&sistema->riesgos[indiceMasGrave]);
}
