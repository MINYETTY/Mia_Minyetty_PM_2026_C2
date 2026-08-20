#ifndef VEHICULO_H
#define VEHICULO_H

/*
 * ============================================================
 * Archivo: vehiculo.h
 * Propósito:
 * Estructuras y funciones relacionadas con los vehículos.
 * ============================================================
 */

typedef struct
{
    int id;

    char marca[50];
    char modelo[50];
    int anio;

    double costo;
    double valorResidual;
    int vidaUtil;

    double kmAnuales;

    double precioCombustible;
    double kmPorLitroCiudad;
    double kmPorLitroAutopista;

    double seguroAnual;
    double mantenimientoAnual;

    double precioNeumatico;
    int cantidadNeumaticos;
    double vidaUtilNeumatico;

    double porcentajeImprevistos;

} Vehiculo;

void crearVehiculo(Vehiculo *vehiculo, int id);
void modificarVehiculo(Vehiculo *vehiculo);
void mostrarVehiculo(const Vehiculo *vehiculo);
void mostrarVehiculoDetallado(const Vehiculo *vehiculo);

#endif
