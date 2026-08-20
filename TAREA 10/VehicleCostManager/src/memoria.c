/*
 * ============================================================
 * Archivo: memoria.c
 * Propósito:
 * Administración de memoria dinámica para los vehículos.
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/memoria.h"

Vehiculo *agregarVehiculo(
    Vehiculo *vehiculos,
    int *cantidad,
    Vehiculo nuevo
)
{
    Vehiculo *temporal;

    /*
     * Aumentamos el arreglo en una posición.
     */
    temporal = realloc(
        vehiculos,
        (*cantidad + 1) * sizeof(Vehiculo)
    );

    /*
     * Si realloc devuelve NULL, la memoria anterior sigue
     * siendo válida, por lo que no debemos perderla.
     */
    if (temporal == NULL)
    {
        printf("Error: no se pudo reservar memoria.\n");
        return vehiculos;
    }

    vehiculos = temporal;

    vehiculos[*cantidad] = nuevo;
    (*cantidad)++;

    return vehiculos;
}

Vehiculo *eliminarVehiculo(
    Vehiculo *vehiculos,
    int *cantidad,
    int posicion
)
{
    int i;

    if (vehiculos == NULL || *cantidad <= 0)
    {
        return vehiculos;
    }

    if (posicion < 0 || posicion >= *cantidad)
    {
        return vehiculos;
    }

    /*
     * Movemos los elementos posteriores una posición hacia
     * la izquierda para llenar el espacio eliminado.
     */
    for (i = posicion; i < *cantidad - 1; i++)
    {
        vehiculos[i] = vehiculos[i + 1];
    }

    (*cantidad)--;

    /*
     * Si ya no quedan vehículos, liberamos todo el arreglo.
     */
    if (*cantidad == 0)
    {
        free(vehiculos);
        return NULL;
    }

    /*
     * Intentamos reducir el tamaño del arreglo.
     * Si falla, conservamos el bloque anterior.
     */
    {
        Vehiculo *temporal = realloc(
            vehiculos,
            (*cantidad) * sizeof(Vehiculo)
        );

        if (temporal != NULL)
        {
            vehiculos = temporal;
        }
    }

    return vehiculos;
}

void liberarVehiculos(Vehiculo **vehiculos)
{
    if (vehiculos != NULL && *vehiculos != NULL)
    {
        free(*vehiculos);
        *vehiculos = NULL;
    }
}
