/*
 * ============================================================
 * Archivo: calculos.c
 * Propósito:
 * Implementación de los cálculos de costo del vehículo.
 *
 * Nota:
 * Los resultados se calculan a partir de los datos guardados
 * en Vehiculo. No se almacenan resultados derivados dentro del
 * vehículo para evitar datos desactualizados.
 * ============================================================
 */

#include <stdio.h>
#include <math.h>

#include "../include/vehiculo.h"
#include "../include/calculos.h"
#include "../include/mantenimiento.h"

double calcularDepreciacionAnual(const Vehiculo *vehiculo)
{
    return (vehiculo->costo - vehiculo->valorResidual)
           / vehiculo->vidaUtil;
}

double calcularDepreciacionPorKm(const Vehiculo *vehiculo)
{
    return calcularDepreciacionAnual(vehiculo)
           / vehiculo->kmAnuales;
}

double calcularDepreciacionTotal(const Vehiculo *vehiculo)
{
    return vehiculo->costo - vehiculo->valorResidual;
}

double calcularCostoCombustibleKmCiudad(const Vehiculo *vehiculo)
{
    return vehiculo->precioCombustible
           / vehiculo->kmPorLitroCiudad;
}

double calcularCostoCombustibleKmAutopista(const Vehiculo *vehiculo)
{
    return vehiculo->precioCombustible
           / vehiculo->kmPorLitroAutopista;
}

double calcularCostoSeguroKm(const Vehiculo *vehiculo)
{
    return vehiculo->seguroAnual / vehiculo->kmAnuales;
}

double calcularCostoMantenimientoKm(const Vehiculo *vehiculo)
{
    return vehiculo->mantenimientoAnual
           / vehiculo->kmAnuales;
}

double calcularCostoJuegoNeumaticos(const Vehiculo *vehiculo)
{
    return vehiculo->precioNeumatico
           * vehiculo->cantidadNeumaticos;
}

double calcularJuegosNeumaticosVidaUtil(const Vehiculo *vehiculo)
{
    double kmVidaUtil = vehiculo->kmAnuales * vehiculo->vidaUtil;

    /*
     * ceil() redondea hacia arriba porque, si se necesita una
     * fracción de un juego, en la práctica se debe comprar un
     * juego completo.
     */
    return ceil(kmVidaUtil / vehiculo->vidaUtilNeumatico);
}

double calcularCostoNeumaticosVidaUtil(const Vehiculo *vehiculo)
{
    return calcularJuegosNeumaticosVidaUtil(vehiculo)
           * calcularCostoJuegoNeumaticos(vehiculo);
}

double calcularCostoNeumaticosKm(const Vehiculo *vehiculo)
{
    return calcularCostoJuegoNeumaticos(vehiculo)
           / vehiculo->vidaUtilNeumatico;
}

double calcularImprevistosAnuales(const Vehiculo *vehiculo)
{
    double base = vehiculo->seguroAnual
                  + vehiculo->mantenimientoAnual;

    return base * (vehiculo->porcentajeImprevistos / 100.0);
}

double calcularImprevistosKm(const Vehiculo *vehiculo)
{
    return calcularImprevistosAnuales(vehiculo)
           / vehiculo->kmAnuales;
}

double calcularCostoRealKmCiudad(const Vehiculo *vehiculo)
{
    return calcularDepreciacionPorKm(vehiculo)
           + calcularCostoCombustibleKmCiudad(vehiculo)
           + calcularCostoSeguroKm(vehiculo)
           + calcularCostoMantenimientoKm(vehiculo)
           + calcularCostoNeumaticosKm(vehiculo)
           + calcularImprevistosKm(vehiculo);
}

double calcularCostoRealKmAutopista(const Vehiculo *vehiculo)
{
    return calcularDepreciacionPorKm(vehiculo)
           + calcularCostoCombustibleKmAutopista(vehiculo)
           + calcularCostoSeguroKm(vehiculo)
           + calcularCostoMantenimientoKm(vehiculo)
           + calcularCostoNeumaticosKm(vehiculo)
           + calcularImprevistosKm(vehiculo);
}

double calcularCostoCombustibleViaje(
    const Vehiculo *vehiculo,
    double kmCiudad,
    double kmAutopista
)
{
    double litrosCiudad =
        kmCiudad / vehiculo->kmPorLitroCiudad;

    double litrosAutopista =
        kmAutopista / vehiculo->kmPorLitroAutopista;

    return (litrosCiudad + litrosAutopista)
           * vehiculo->precioCombustible;
}

double calcularCostoRealViaje(
    const Vehiculo *vehiculo,
    double kmCiudad,
    double kmAutopista
)
{
    double costoCiudad =
        kmCiudad * calcularCostoRealKmCiudad(vehiculo);

    double costoAutopista =
        kmAutopista * calcularCostoRealKmAutopista(vehiculo);

    return costoCiudad + costoAutopista;
}

void mostrarAnalisisCostos(const Vehiculo *vehiculo)
{
    double depreciacionKm =
        calcularDepreciacionPorKm(vehiculo);

    double combustibleCiudad =
        calcularCostoCombustibleKmCiudad(vehiculo);

    double combustibleAutopista =
        calcularCostoCombustibleKmAutopista(vehiculo);

    double seguroKm =
        calcularCostoSeguroKm(vehiculo);

    double mantenimientoKm =
        calcularCostoMantenimientoKm(vehiculo);

    double neumaticosKm =
        calcularCostoNeumaticosKm(vehiculo);

    double imprevistosKm =
        calcularImprevistosKm(vehiculo);

    printf("\n========================================\n");
    printf("          ANALISIS DE COSTOS\n");
    printf("========================================\n");

    printf("Vehiculo: %s %s\n",
           vehiculo->marca,
           vehiculo->modelo);

    printf("\n--- DEPRECIACION ---\n");
    printf("Depreciacion anual: RD$ %.2f\n",
           calcularDepreciacionAnual(vehiculo));

    printf("Depreciacion total: RD$ %.2f\n",
           calcularDepreciacionTotal(vehiculo));

    printf("Depreciacion por km: RD$ %.4f\n",
           depreciacionKm);

    printf("\n--- COMBUSTIBLE POR KM ---\n");
    printf("Ciudad: RD$ %.4f/km\n",
           combustibleCiudad);

    printf("Autopista: RD$ %.4f/km\n",
           combustibleAutopista);

    printf("\n--- COSTOS FIJOS/VARIABLES POR KM ---\n");
    printf("Seguro: RD$ %.4f/km\n", seguroKm);
    printf("Mantenimiento: RD$ %.4f/km\n", mantenimientoKm);
    printf("Neumaticos: RD$ %.4f/km\n", neumaticosKm);
    printf("Imprevistos: RD$ %.4f/km\n", imprevistosKm);

    printf("\n--- COSTO REAL POR KM ---\n");
    printf("Ciudad: RD$ %.4f/km\n",
           calcularCostoRealKmCiudad(vehiculo));

    printf("Autopista: RD$ %.4f/km\n",
           calcularCostoRealKmAutopista(vehiculo));

    printf("\n--- NEUMATICOS ---\n");
    printf("Costo de un juego: RD$ %.2f\n",
           calcularCostoJuegoNeumaticos(vehiculo));

    printf("Juegos estimados en vida util: %.0f\n",
           calcularJuegosNeumaticosVidaUtil(vehiculo));

    printf("Costo de neumaticos vida util: RD$ %.2f\n",
           calcularCostoNeumaticosVidaUtil(vehiculo));

    printf("\n--- MANTENIMIENTO ---\n");
    printf("Mantenimiento vida util: RD$ %.2f\n",
           calcularMantenimientoVidaUtil(vehiculo));

    printf("========================================\n");
}
