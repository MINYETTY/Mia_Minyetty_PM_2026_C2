/*
 * ============================================================
 * Archivo: archivo.c
 * Propósito:
 * Guardar y cargar vehículos utilizando un archivo CSV.
 *
 * Cada vehículo ocupa una línea.
 * ============================================================
 */

#include <stdio.h>
#include <string.h>

#include "../include/archivo.h"

int crearArchivo(const char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "w");

    if (archivo == NULL)
    {
        return 0;
    }

    fprintf(
        archivo,
        "id,marca,modelo,anio,costo,valorResidual,vidaUtil,"
        "kmAnuales,precioCombustible,kmPorLitroCiudad,"
        "kmPorLitroAutopista,seguroAnual,mantenimientoAnual,"
        "precioNeumatico,cantidadNeumaticos,vidaUtilNeumatico,"
        "porcentajeImprevistos\n"
    );

    fclose(archivo);

    return 1;
}

int guardarVehiculos(
    const char *nombreArchivo,
    const Vehiculo *vehiculos,
    int cantidad
)
{
    FILE *archivo;
    int i;

    archivo = fopen(nombreArchivo, "w");

    if (archivo == NULL)
    {
        return 0;
    }

    fprintf(
        archivo,
        "id,marca,modelo,anio,costo,valorResidual,vidaUtil,"
        "kmAnuales,precioCombustible,kmPorLitroCiudad,"
        "kmPorLitroAutopista,seguroAnual,mantenimientoAnual,"
        "precioNeumatico,cantidadNeumaticos,vidaUtilNeumatico,"
        "porcentajeImprevistos\n"
    );

    for (i = 0; i < cantidad; i++)
    {
        fprintf(
            archivo,
            "%d,%s,%s,%d,%.10f,%.10f,%d,%.10f,%.10f,"
            "%.10f,%.10f,%.10f,%.10f,%.10f,%d,%.10f,%.10f\n",
            vehiculos[i].id,
            vehiculos[i].marca,
            vehiculos[i].modelo,
            vehiculos[i].anio,
            vehiculos[i].costo,
            vehiculos[i].valorResidual,
            vehiculos[i].vidaUtil,
            vehiculos[i].kmAnuales,
            vehiculos[i].precioCombustible,
            vehiculos[i].kmPorLitroCiudad,
            vehiculos[i].kmPorLitroAutopista,
            vehiculos[i].seguroAnual,
            vehiculos[i].mantenimientoAnual,
            vehiculos[i].precioNeumatico,
            vehiculos[i].cantidadNeumaticos,
            vehiculos[i].vidaUtilNeumatico,
            vehiculos[i].porcentajeImprevistos
        );
    }

    fclose(archivo);

    return 1;
}

int cargarVehiculos(
    const char *nombreArchivo,
    Vehiculo **vehiculos,
    int *cantidad
)
{
    FILE *archivo;
    char linea[1200];
    int primeraLinea = 1;

    *vehiculos = NULL;
    *cantidad = 0;

    archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        Vehiculo vehiculo;
        char *token;

        /*
         * La primera línea contiene los encabezados.
         */
        if (primeraLinea)
        {
            primeraLinea = 0;
            continue;
        }

        token = strtok(linea, ",");
        if (token == NULL) continue;
        vehiculo.id = atoi(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strncpy(vehiculo.marca, token, sizeof(vehiculo.marca) - 1);
        vehiculo.marca[sizeof(vehiculo.marca) - 1] = '\0';

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strncpy(vehiculo.modelo, token, sizeof(vehiculo.modelo) - 1);
        vehiculo.modelo[sizeof(vehiculo.modelo) - 1] = '\0';

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        vehiculo.anio = atoi(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        vehiculo.costo = atof(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        vehiculo.valorResidual = atof(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        vehiculo.vidaUtil = atoi(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        vehiculo.kmAnuales = atof(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        vehiculo.precioCombustible = atof(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        vehiculo.kmPorLitroCiudad = atof(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        vehiculo.kmPorLitroAutopista = atof(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        vehiculo.seguroAnual = atof(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        vehiculo.mantenimientoAnual = atof(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        vehiculo.precioNeumatico = atof(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        vehiculo.cantidadNeumaticos = atoi(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        vehiculo.vidaUtilNeumatico = atof(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        vehiculo.porcentajeImprevistos = atof(token);

        /*
         * Reservamos memoria para el nuevo vehículo.
         */
        {
            Vehiculo *temporal = realloc(
                *vehiculos,
                (*cantidad + 1) * sizeof(Vehiculo)
            );

            if (temporal == NULL)
            {
                fclose(archivo);
                free(*vehiculos);
                *vehiculos = NULL;
                *cantidad = 0;
                return 0;
            }

            *vehiculos = temporal;
            (*vehiculos)[*cantidad] = vehiculo;
            (*cantidad)++;
        }
    }

    fclose(archivo);

    return 1;
}
