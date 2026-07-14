/* ============================================================================
 * escaneo.h - Escaneo de carpeta y menú interactivo (compartido por ambos
 * programas: conversor.c e identificador.c)
 * ==========================================================================
 */
#ifndef ESCANEO_H
#define ESCANEO_H

#define MAX_ARCHIVOS 256
#define MAX_NOMBRE   260

/* Lee el contenido de `ruta` y guarda en `lista` los nombres de los
 * archivos regulares encontrados (omite subcarpetas, "." y ".."). 
 * Retorna la cantidad de archivos, o -1 si no se pudo abrir la ruta. */
int escanear_carpeta(const char *ruta, char lista[][MAX_NOMBRE], int max_items);

/* Imprime la lista numerada y pide al usuario elegir un archivo.
 * Retorna el índice (base 0) elegido, o -1 si el usuario decide salir. */
int mostrar_menu_y_elegir(char lista[][MAX_NOMBRE], int total);

#endif /* ESCANEO_H */
