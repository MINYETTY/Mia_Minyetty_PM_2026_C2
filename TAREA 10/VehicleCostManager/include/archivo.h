#ifndef ARCHIVO_H
#define ARCHIVO_H

/*
 * ============================================================
 * Archivo: archivo.h
 * Propósito:
 * Funciones para crear, guardar y cargar archivos CSV.
 * ============================================================
 */

#include "vehiculo.h"

int crearArchivo(const char *nombreArchivo);
int guardarVehiculos(
    const char *nombreArchivo,
    const Vehiculo *vehiculos,
    int cantidad
);

int cargarVehiculos(
    const char *nombreArchivo,
    Vehiculo **vehiculos,
    int *cantidad
);

#endif
