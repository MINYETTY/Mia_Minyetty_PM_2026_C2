/*
 * ============================================================
 * Archivo: viaje.c
 * Propósito:
 * Interfaz para calcular el costo de un viaje mixto.
 * ============================================================
 */

#include <stdio.h>

#include "../include/viaje.h"
#include "../include/calculos.h"
#include "../include/utilidades.h"

void calcularViaje(const Vehiculo *vehiculo)
{
    Viaje viaje;
    double litrosCiudad;
    double litrosAutopista;
    double litrosTotales;
    double combustibleTotal;
    double costoRealTotal;
    double distanciaTotal;

    printf("\n========================================\n");
    printf("             CALCULAR VIAJE\n");
    printf("========================================\n");

    viaje.kmCiudad =
        leerDoubleNoNegativo("Km en ciudad: ");

    viaje.kmAutopista =
        leerDoubleNoNegativo("Km en autopista: ");

    distanciaTotal =
        viaje.kmCiudad + viaje.kmAutopista;

    if (distanciaTotal <= 0)
    {
        printf("El viaje debe tener al menos 1 km.\n");
        return;
    }

    litrosCiudad =
        viaje.kmCiudad / vehiculo->kmPorLitroCiudad;

    litrosAutopista =
        viaje.kmAutopista / vehiculo->kmPorLitroAutopista;

    litrosTotales =
        litrosCiudad + litrosAutopista;

    combustibleTotal =
        litrosTotales * vehiculo->precioCombustible;

    costoRealTotal =
        calcularCostoRealViaje(
            vehiculo,
            viaje.kmCiudad,
            viaje.kmAutopista
        );

    printf("\n--- RESULTADOS ---\n");

    printf("Distancia total: %.2f km\n", distanciaTotal);

    printf("\nCiudad:\n");
    printf("  Litros: %.3f L\n", litrosCiudad);
    printf("  Combustible: RD$ %.2f\n",
           litrosCiudad * vehiculo->precioCombustible);

    printf("\nAutopista:\n");
    printf("  Litros: %.3f L\n", litrosAutopista);
    printf("  Combustible: RD$ %.2f\n",
           litrosAutopista * vehiculo->precioCombustible);

    printf("\nTotal combustible:\n");
    printf("  %.3f L\n", litrosTotales);
    printf("  RD$ %.2f\n", combustibleTotal);

    printf("\nCosto real estimado del viaje:\n");
    printf("  RD$ %.2f\n", costoRealTotal);

    printf("Costo real promedio por km:\n");
    printf("  RD$ %.4f/km\n", costoRealTotal / distanciaTotal);

    printf("========================================\n");
}
