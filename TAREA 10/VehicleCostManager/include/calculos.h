#ifndef CALCULOS_H
#define CALCULOS_H

/*
 * ============================================================
 * Archivo: calculos.h
 * Propósito:
 * Declaraciones de todos los cálculos económicos del vehículo.
 * ============================================================
 */

double calcularDepreciacionAnual(const Vehiculo *vehiculo);
double calcularDepreciacionPorKm(const Vehiculo *vehiculo);
double calcularDepreciacionTotal(const Vehiculo *vehiculo);

double calcularCostoCombustibleKmCiudad(const Vehiculo *vehiculo);
double calcularCostoCombustibleKmAutopista(const Vehiculo *vehiculo);

double calcularCostoSeguroKm(const Vehiculo *vehiculo);
double calcularCostoMantenimientoKm(const Vehiculo *vehiculo);
double calcularCostoNeumaticosKm(const Vehiculo *vehiculo);

double calcularCostoJuegoNeumaticos(const Vehiculo *vehiculo);
double calcularJuegosNeumaticosVidaUtil(const Vehiculo *vehiculo);
double calcularCostoNeumaticosVidaUtil(const Vehiculo *vehiculo);

double calcularImprevistosAnuales(const Vehiculo *vehiculo);
double calcularImprevistosKm(const Vehiculo *vehiculo);

double calcularCostoRealKmCiudad(const Vehiculo *vehiculo);
double calcularCostoRealKmAutopista(const Vehiculo *vehiculo);

double calcularCostoCombustibleViaje(
    const Vehiculo *vehiculo,
    double kmCiudad,
    double kmAutopista
);

double calcularCostoRealViaje(
    const Vehiculo *vehiculo,
    double kmCiudad,
    double kmAutopista
);

void mostrarAnalisisCostos(const Vehiculo *vehiculo);

#endif
