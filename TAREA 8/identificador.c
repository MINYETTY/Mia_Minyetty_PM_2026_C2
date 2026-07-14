/* ============================================================================
  identificador.c - PROGRAMA 2
 
  Recorre la carpeta, y para cada archivo compara:
    - lo que su EXTENSIÓN dice que es  (.png / .jpg / .bmp / otra)
    - lo que su CONTENIDO REAL es       (magic number, primeros bytes)
 
  Si ambos coinciden, el archivo es válido. Si no coinciden (por ejemplo,
  un .txt renombrado a .jpg, o un .png que en realidad es un .bmp), se
  marca como "NO VALIDO / SOSPECHOSO".
 
  También permite, mediante el menú, inspeccionar un solo archivo
  puntual con más detalle.
 
  Compilar:
       gcc identificador.c escaneo.c validacion.c -o identificador
  ==========================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "escaneo.h"
#include "validacion.h"

/* Analiza un único archivo y muestra si es válido o no. */
void analizar_archivo(const char *ruta, const char *nombre_solo) {
    TipoImagen esperado = tipo_segun_extension(nombre_solo);
    TipoImagen real     = detectar_tipo_real(ruta);

    printf("  %-30s | extension dice: %-11s | contenido real: %-11s | ",
           nombre_solo, nombre_tipo(esperado), nombre_tipo(real));

    if (real == TIPO_DESCONOCIDO) {
        printf("NO ES UNA IMAGEN SOPORTADA\n");
    } else if (esperado != real) {
        printf("*** NO VALIDO (extension no coincide con el contenido) ***\n");
    } else {
        printf("OK\n");
    }
}

/* Recorre todos los archivos de la carpeta y los analiza uno por uno. */
void analizar_carpeta_completa(const char *carpeta, char lista[][MAX_NOMBRE], int total) {
    printf("\n===== Analisis de todos los archivos =====\n");
    for (int i = 0; i < total; i++) {
        char ruta_completa[MAX_NOMBRE * 2];
        snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s", carpeta, lista[i]);
        analizar_archivo(ruta_completa, lista[i]);
    }
    printf("============================================\n");
}

int main(int argc, char *argv[]) {
    const char *carpeta = (argc > 1) ? argv[1] : ".";

    static char archivos[MAX_ARCHIVOS][MAX_NOMBRE];

    printf("Escaneando carpeta: %s\n", carpeta);
    int total = escanear_carpeta(carpeta, archivos, MAX_ARCHIVOS);
    if (total <= 0) {
        return EXIT_FAILURE;
    }

    /* Primero mostramos el análisis general de toda la carpeta */
    analizar_carpeta_completa(carpeta, archivos, total);

    /* Luego dejamos elegir un archivo puntual si se quiere ver de nuevo */
    int indice = mostrar_menu_y_elegir(archivos, total);
    if (indice == -1) {
        printf("Saliendo del programa.\n");
        return EXIT_SUCCESS;
    }

    char ruta_completa[MAX_NOMBRE * 2];
    snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s", carpeta, archivos[indice]);

    printf("\n----- Detalle del archivo seleccionado -----\n");
    analizar_archivo(ruta_completa, archivos[indice]);

    return EXIT_SUCCESS;
}
