/*
 * ============================================================
 * Archivo: mantenimiento.c
 * Propósito:
 * Cálculos relacionados con mantenimiento y costo anual base.
 * ============================================================
 */

#include "../include/vehiculo.h"
#include "../include/mantenimiento.h"

double calcularMantenimientoVidaUtil(const Vehiculo *vehiculo)
{
    return vehiculo->mantenimientoAnual
           * vehiculo->vidaUtil;
}

double calcularGastoAnualTotalBase(const Vehiculo *vehiculo)
{
    return vehiculo->seguroAnual
           + vehiculo->mantenimientoAnual;
}
