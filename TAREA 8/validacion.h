/* ============================================================================
 * validacion.h - Detección REAL del tipo de archivo (magic numbers)
 *
 * Este módulo es compartido por ambos programas:
 *   - conversor.c     (programa 1: convierte a blanco y negro)
 *   - identificador.c (programa 2: valida extension vs contenido real)
 * ==========================================================================
 */
#ifndef VALIDACION_H
#define VALIDACION_H

typedef enum {
    TIPO_DESCONOCIDO = 0,
    TIPO_PNG,
    TIPO_JPG,
    TIPO_BMP
} TipoImagen;

/* Lee los primeros bytes de `ruta_archivo` en modo binario y determina
 * el tipo real comparando contra las firmas oficiales de PNG/JPG/BMP.
 * Ignora por completo el nombre/extension del archivo. */
TipoImagen detectar_tipo_real(const char *ruta_archivo);

/* Determina qué tipo "dice ser" el archivo según su extensión
 * (.png, .jpg/.jpeg, .bmp). Solo mira el nombre, nunca el contenido. */
TipoImagen tipo_segun_extension(const char *nombre_archivo);

/* Nombre legible para imprimir en pantalla */
const char *nombre_tipo(TipoImagen tipo);

#endif /* VALIDACION_H */
