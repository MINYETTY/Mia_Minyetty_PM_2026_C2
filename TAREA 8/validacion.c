#include "validacion.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>  /* strcasecmp */

#define TAM_CABECERA 12

TipoImagen detectar_tipo_real(const char *ruta_archivo) {
    FILE *f = fopen(ruta_archivo, "rb"); /* "rb": modo binario, clave en Windows */
    if (f == NULL) {
        return TIPO_DESCONOCIDO;
    }

    unsigned char cabecera[TAM_CABECERA] = {0};
    size_t leidos = fread(cabecera, 1, TAM_CABECERA, f);
    fclose(f);

    if (leidos < 2) {
        return TIPO_DESCONOCIDO; /* archivo demasiado pequeño */
    }

    /* PNG: 8 bytes fijos */
    static const unsigned char firma_png[8] = {
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A
    };
    if (leidos >= 8 && memcmp(cabecera, firma_png, 8) == 0) {
        return TIPO_PNG;
    }

    /* JPG: FF D8 FF (JFIF/EXIF comparten estos 3 bytes) */
    static const unsigned char firma_jpg[3] = {0xFF, 0xD8, 0xFF};
    if (leidos >= 3 && memcmp(cabecera, firma_jpg, 3) == 0) {
        return TIPO_JPG;
    }

    /* BMP: "BM" */
    if (cabecera[0] == 0x42 && cabecera[1] == 0x4D) {
        return TIPO_BMP;
    }

    return TIPO_DESCONOCIDO;
}

TipoImagen tipo_segun_extension(const char *nombre_archivo) {
    const char *punto = strrchr(nombre_archivo, '.');
    if (punto == NULL) {
        return TIPO_DESCONOCIDO;
    }

    if (strcasecmp(punto, ".png") == 0) {
        return TIPO_PNG;
    }
    if (strcasecmp(punto, ".jpg") == 0 || strcasecmp(punto, ".jpeg") == 0) {
        return TIPO_JPG;
    }
    if (strcasecmp(punto, ".bmp") == 0) {
        return TIPO_BMP;
    }

    return TIPO_DESCONOCIDO;
}

const char *nombre_tipo(TipoImagen tipo) {
    switch (tipo) {
        case TIPO_PNG: return "PNG";
        case TIPO_JPG: return "JPG/JPEG";
        case TIPO_BMP: return "BMP";
        default:       return "DESCONOCIDO";
    }
}
