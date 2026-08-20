#ifndef VIAJE_H
#define VIAJE_H

/*
 * ============================================================
 * Archivo: viaje.h
 * Propósito:
 * Estructura y funciones para calcular viajes.
 * ============================================================
 */

typedef struct
{
    double kmCiudad;
    double kmAutopista;
} Viaje;

void calcularViaje(const Vehiculo *vehiculo);

#endif
