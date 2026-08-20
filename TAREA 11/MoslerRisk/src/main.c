#include <stdio.h>
#include "../include/riesgo.h"
#include "../include/menu.h"

int main(void) {
    Sistema sistema;
    sistema.riesgos = NULL;
    sistema.cantidad = 0;
    sistema.archivoActual[0] = '\0';
    sistema.archivoAbierto = 0;

    printf("Mosler Risk Manager\n");
    ejecutarMenu(&sistema);

    return 0;
}
