/* ============================================================================
  conversor.c
 
 1.1 Lista los archivos de la carpeta actual (o la que se pase por
     argumento) y muestra un menú interactivo.
  1.2 El usuario selecciona por número el archivo a convertir.
 
  Antes de convertir, valida por magic number que el archivo elegido sea
  realmente PNG/JPG/BMP (usa validacion.c). Si no lo es, aborta con error
  en vez de intentar decodificar basura.
 
  Luego decodifica con stb_image, aplica la fórmula de luminancia
  (Y = 0.299 R + 0.587 G + 0.114 B) y guarda el resultado con el MISMO
  nombre y extensión del original, pero con el prefijo "resultado_"
  (ej: "foto.jpg" -> "resultado_foto.jpg"), en la misma carpeta del
  archivo de entrada.
 
  Dependencias externas que DEBES descargar y poner junto a este archivo.
       stb_image.h
       stb_image_write.h
 
  Compilar:
       gcc conversor.c escaneo.c validacion.c -o conversor -lm
  ==========================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "escaneo.h"
#include "validacion.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

/* ----------------------------------------------------------------------
  Conversión a escala de grises (fórmula de luminancia BT.601)
 * -------------------------------------------------------------------- */
void convertir_a_escala_de_grises(unsigned char *datos, int ancho, int alto, int canales) {
    if (canales < 3) {
        return; /* ya es monocromática (1 o 2 canales) */
    }

    long total_pixeles = (long)ancho * (long)alto;

    for (long i = 0; i < total_pixeles; i++) {
        unsigned char *pixel = datos + (i * canales);

        unsigned char r = pixel[0];
        unsigned char g = pixel[1];
        unsigned char b = pixel[2];

        unsigned char gris = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b + 0.5);

        pixel[0] = gris;
        pixel[1] = gris;
        pixel[2] = gris;
        /* pixel[3] (alfa), si existe, se deja intacto */
    }
}

/* Carga, convierte y guarda. `tipo` es el formato REAL detectado por
  magic number (no el de la extensión), y se usa para elegir con qué
  función de stb_image_write se debe guardar el resultado, de modo que
  el archivo de salida quede en el mismo formato que el original.
  Retorna 1 en éxito, 0 en fallo. */
int procesar_imagen(const char *ruta_entrada, const char *ruta_salida, TipoImagen tipo) {
    int ancho, alto, canales;

    unsigned char *datos = stbi_load(ruta_entrada, &ancho, &alto, &canales, 0);
    if (datos == NULL) {
        printf("Error al decodificar la imagen: %s\n", stbi_failure_reason());
        return 0;
    }

    printf("Imagen cargada: %dx%d px, %d canal(es).\n", ancho, alto, canales);

    convertir_a_escala_de_grises(datos, ancho, alto, canales);

    int ok = 0;
    switch (tipo) {
        case TIPO_PNG:
            ok = stbi_write_png(ruta_salida, ancho, alto, canales, datos, ancho * canales);
            break;
        case TIPO_BMP:
            ok = stbi_write_bmp(ruta_salida, ancho, alto, canales, datos);
            break;
        case TIPO_JPG:
            /* Calidad 90 (rango 1-100). JPG es un formato con pérdida,
              pero stb_image_write ofrece un codificador JPG estándar. */
            ok = stbi_write_jpg(ruta_salida, ancho, alto, canales, datos, 90);
            break;
        default:
            /* No debería ocurrir: ya se validó el tipo antes de llegar aquí */
            ok = 0;
            break;
    }

    stbi_image_free(datos);

    if (!ok) {
        printf("Error al escribir el archivo de salida '%s'.\n", ruta_salida);
        return 0;
    }

    printf("Archivo generado correctamente: %s\n", ruta_salida);
    return 1;
}

int main(int argc, char *argv[]) {
    const char *carpeta = (argc > 1) ? argv[1] : ".";

    static char archivos[MAX_ARCHIVOS][MAX_NOMBRE];

    /* --- 1.1 Escaneo de carpeta --- */
    printf("Escaneando carpeta: %s\n", carpeta);
    int total = escanear_carpeta(carpeta, archivos, MAX_ARCHIVOS);
    if (total <= 0) {
        return EXIT_FAILURE;
    }

    /* --- 1.2 Menú interactivo de selección --- */
    int indice = mostrar_menu_y_elegir(archivos, total);
    if (indice == -1) {
        printf("Saliendo del programa.\n");
        return EXIT_SUCCESS;
    }

    char ruta_completa[MAX_NOMBRE * 2];
    snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s", carpeta, archivos[indice]);

    /* --- Validación por magic number antes de procesar --- */
    printf("\nValidando archivo: %s\n", ruta_completa);
    TipoImagen tipo = detectar_tipo_real(ruta_completa);
    printf("Tipo real detectado (por bytes): %s\n", nombre_tipo(tipo));

    if (tipo == TIPO_DESCONOCIDO) {
        printf("ERROR: el archivo no es un PNG/JPG/BMP valido (aunque su nombre\n");
        printf("pueda sugerirlo). Posible archivo renombrado o corrupto.\n");
        return EXIT_FAILURE;
    }

    /* --- Conversión a blanco y negro --- */
    /* Nombre de salida: mismo nombre y extension del original, con el
      prefijo "resultado_", guardado en la misma carpeta del archivo
      de entrada. Ej: carpeta/foto.jpg -> carpeta/resultado_foto.jpg */
    char ruta_salida[MAX_NOMBRE * 2 + 10];
    snprintf(ruta_salida, sizeof(ruta_salida), "%s/resultado_%s", carpeta, archivos[indice]);

    printf("\nConvirtiendo a escala de grises...\n");
    if (!procesar_imagen(ruta_completa, ruta_salida, tipo)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
