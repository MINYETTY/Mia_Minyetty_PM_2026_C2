#ifndef MANTENIMIENTO_H
#define MANTENIMIENTO_H

/*
 * ============================================================
 * Archivo: mantenimiento.h
 * Propósito:
 * Funciones para estimar mantenimiento durante la vida útil.
 * ============================================================
 */

double calcularMantenimientoVidaUtil(const Vehiculo *vehiculo);
double calcularGastoAnualTotalBase(const Vehiculo *vehiculo);

#endif
