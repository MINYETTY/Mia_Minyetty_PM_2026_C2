#include <stdio.h>
#include "../include/menu.h"
#include "../include/archivo.h"
#include "../include/memoria.h"
#include "../include/utilidades.h"

static void mostrarOpciones(void) {
    printf("\n===== Mosler Risk Manager =====\n");
    printf("1.  Crear archivo\n");
    printf("2.  Abrir archivo\n");
    printf("3.  Crear riesgo\n");
    printf("4.  Modificar riesgo\n");
    printf("5.  Eliminar riesgo\n");
    printf("6.  Calcular / ver detalle de un riesgo\n");
    printf("7.  Mostrar riesgos\n");
    printf("8.  Buscar riesgo por nombre\n");
    printf("9.  Ordenar riesgos por gravedad\n");
    printf("10. Mostrar resumen\n");
    printf("11. Guardar cambios\n");
    printf("12. Salir\n");
}

void ejecutarMenu(Sistema *sistema) {
    int opcion;
    char nombreEmpresa[TAM_NOMBRE];

    do {
        mostrarOpciones();
        opcion = leerEnteroRango("Elige una opcion: ", 1, 12);

        switch (opcion) {
            case 1:
                leerCadena("Nombre de la empresa: ", nombreEmpresa, sizeof(nombreEmpresa));
                crearArchivo(sistema, nombreEmpresa);
                break;

            case 2:
                leerCadena("Nombre de la empresa: ", nombreEmpresa, sizeof(nombreEmpresa));
                abrirArchivo(sistema, nombreEmpresa);
                break;

            case 3:
                if (!sistema->archivoAbierto) {
                    printf("Primero crea o abre un archivo.\n");
                } else {
                    crearRiesgo(sistema);
                }
                break;

            case 4:
                if (!sistema->archivoAbierto) {
                    printf("Primero crea o abre un archivo.\n");
                } else {
                    modificarRiesgo(sistema);
                }
                break;

            case 5:
                if (!sistema->archivoAbierto) {
                    printf("Primero crea o abre un archivo.\n");
                } else {
                    eliminarRiesgo(sistema);
                }
                break;

            case 6: {
                if (sistema->cantidad == 0) {
                    printf("No hay riesgos cargados.\n");
                    break;
                }
                int id = leerEntero("Id del riesgo: ");
                int indice = buscarRiesgoPorId(sistema, id);
                if (indice == -1) {
                    printf("No existe un riesgo con id %d.\n", id);
                } else {
                    mostrarRiesgoDetallado(&sistema->riesgos[indice]);
                }
                break;
            }

            case 7:
                mostrarRiesgos(sistema);
                break;

            case 8: {
                char texto[TAM_NOMBRE];
                leerCadena("Texto a buscar en el nombre: ", texto, sizeof(texto));
                buscarPorNombre(sistema, texto);
                break;
            }

            case 9:
                ordenarPorGravedad(sistema);
                break;

            case 10:
                mostrarResumen(sistema);
                break;

            case 11:
                if (!sistema->archivoAbierto) {
                    printf("No hay archivo abierto.\n");
                } else {
                    guardarRiesgos(sistema);
                }
                break;

            case 12:
                if (sistema->archivoAbierto) {
                    int guardar = leerEnteroRango("Guardar cambios antes de salir? (1=si, 0=no): ", 0, 1);
                    if (guardar) {
                        guardarRiesgos(sistema);
                    }
                }
                printf("Cerrando Mosler Risk Manager...\n");
                break;
        }

        if (opcion != 12) {
            pausar();
        }

    } while (opcion != 12);

    liberarRiesgos(sistema);
}
