#ifndef MEMORIA_H
#define MEMORIA_H

/*
 * ============================================================
 * Archivo: memoria.h
 * Propósito:
 * Operaciones de memoria dinámica para el arreglo de vehículos.
 * ============================================================
 */

#include "vehiculo.h"

Vehiculo *agregarVehiculo(
    Vehiculo *vehiculos,
    int *cantidad,
    Vehiculo nuevo
);

Vehiculo *eliminarVehiculo(
    Vehiculo *vehiculos,
    int *cantidad,
    int posicion
);

void liberarVehiculos(Vehiculo **vehiculos);

#endif
