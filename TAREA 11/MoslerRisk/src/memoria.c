#include <stdio.h>
#include <stdlib.h>
#include "../include/memoria.h"

void agregarRiesgo(Sistema *sistema, Riesgo nuevo) {
    Riesgo *temp = realloc(sistema->riesgos, (sistema->cantidad + 1) * sizeof(Riesgo));

    if (temp == NULL) {
        printf("Error: no se pudo reservar memoria para el nuevo riesgo.\n");
        return; /* sistema->riesgos sigue apuntando al arreglo original, intacto */
    }

    sistema->riesgos = temp;
    sistema->riesgos[sistema->cantidad] = nuevo;
    sistema->cantidad++;
}

void eliminarRiesgoArreglo(Sistema *sistema, int indice) {
    if (indice < 0 || indice >= sistema->cantidad) {
        printf("Error interno: indice fuera de rango.\n");
        return;
    }

    for (int i = indice; i < sistema->cantidad - 1; i++) {
        sistema->riesgos[i] = sistema->riesgos[i + 1];
    }
    sistema->cantidad--;

    if (sistema->cantidad == 0) {
        free(sistema->riesgos);
        sistema->riesgos = NULL;
        return;
    }

    Riesgo *temp = realloc(sistema->riesgos, sistema->cantidad * sizeof(Riesgo));
    if (temp != NULL) {
        sistema->riesgos = temp;
    }
    /* si el realloc "hacia abajo" fallara (muy raro), seguimos usando el
     * bloque anterior: sigue siendo valido, solo un poco mas grande */
}

void liberarRiesgos(Sistema *sistema) {
    free(sistema->riesgos);
    sistema->riesgos = NULL;
    sistema->cantidad = 0;
}
