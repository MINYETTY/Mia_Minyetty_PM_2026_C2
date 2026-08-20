/*
 * ============================================================
 * Archivo: vehiculo.c
 * Propósito:
 * Creación, modificación y visualización de vehículos.
 * ============================================================
 */

#include <stdio.h>
#include "../include/vehiculo.h"
#include "../include/utilidades.h"

void crearVehiculo(Vehiculo *vehiculo, int id)
{
    vehiculo->id = id;

    printf("\n========================================\n");
    printf("         CREAR NUEVO VEHICULO\n");
    printf("========================================\n");

    leerCadena("Marca: ", vehiculo->marca, sizeof(vehiculo->marca));
    leerCadena("Modelo: ", vehiculo->modelo, sizeof(vehiculo->modelo));

    vehiculo->anio = leerEnteroPositivo("Ano: ");

    printf("\n--- COMPRA Y VIDA UTIL ---\n");

    vehiculo->costo = leerDoublePositivo(
        "Costo de compra (RD$): "
    );

    vehiculo->valorResidual = leerDoubleNoNegativo(
        "Valor residual estimado (RD$): "
    );

    while (vehiculo->valorResidual >= vehiculo->costo)
    {
        printf("El valor residual debe ser menor que el costo.\n");
        vehiculo->valorResidual = leerDoubleNoNegativo(
            "Valor residual estimado (RD$): "
        );
    }

    vehiculo->vidaUtil = leerEnteroPositivo(
        "Vida util estimada (anos): "
    );

    printf("\n--- UTILIZACION ---\n");

    vehiculo->kmAnuales = leerDoublePositivo(
        "Kilometros anuales estimados: "
    );

    printf("\n--- COMBUSTIBLE ---\n");

    vehiculo->precioCombustible = leerDoublePositivo(
        "Precio del combustible (RD$/L): "
    );

    vehiculo->kmPorLitroCiudad = leerDoublePositivo(
        "Rendimiento en ciudad (km/L): "
    );

    vehiculo->kmPorLitroAutopista = leerDoublePositivo(
        "Rendimiento en autopista (km/L): "
    );

    printf("\n--- GASTOS ANUALES ---\n");

    vehiculo->seguroAnual = leerDoubleNoNegativo(
        "Seguro anual (RD$): "
    );

    vehiculo->mantenimientoAnual = leerDoubleNoNegativo(
        "Mantenimiento anual estimado (RD$): "
    );

    printf("\n--- NEUMATICOS ---\n");

    vehiculo->precioNeumatico = leerDoublePositivo(
        "Precio de un neumatico (RD$): "
    );

    vehiculo->cantidadNeumaticos = leerEnteroPositivo(
        "Cantidad de neumaticos: "
    );

    vehiculo->vidaUtilNeumatico = leerDoublePositivo(
        "Vida util del neumatico (km): "
    );

    printf("\n--- IMPREVISTOS ---\n");

    vehiculo->porcentajeImprevistos = leerDoubleNoNegativo(
        "Porcentaje de imprevistos anual (%%): "
    );

    printf("\nVehiculo creado correctamente.\n");
}

void modificarVehiculo(Vehiculo *vehiculo)
{
    int opcion;

    do
    {
        printf("\n========================================\n");
        printf("          MODIFICAR VEHICULO\n");
        printf("========================================\n");
        printf("Vehiculo: %s %s\n", vehiculo->marca, vehiculo->modelo);

        printf("\n");
        printf("1. Marca\n");
        printf("2. Modelo\n");
        printf("3. Ano\n");
        printf("4. Costo\n");
        printf("5. Valor residual\n");
        printf("6. Vida util\n");
        printf("7. Km anuales\n");
        printf("8. Precio combustible\n");
        printf("9. Rendimiento ciudad\n");
        printf("10. Rendimiento autopista\n");
        printf("11. Seguro anual\n");
        printf("12. Mantenimiento anual\n");
        printf("13. Precio neumatico\n");
        printf("14. Cantidad de neumaticos\n");
        printf("15. Vida util neumaticos\n");
        printf("16. Porcentaje imprevistos\n");
        printf("0. Volver\n");

        opcion = leerEnteroRango("Seleccione: ", 0, 16);

        switch (opcion)
        {
            case 1:
                leerCadena("Nueva marca: ",
                           vehiculo->marca,
                           sizeof(vehiculo->marca));
                break;

            case 2:
                leerCadena("Nuevo modelo: ",
                           vehiculo->modelo,
                           sizeof(vehiculo->modelo));
                break;

            case 3:
                vehiculo->anio = leerEnteroPositivo("Nuevo ano: ");
                break;

            case 4:
                vehiculo->costo = leerDoublePositivo("Nuevo costo: ");
                if (vehiculo->valorResidual >= vehiculo->costo)
                {
                    printf("El valor residual actual ya no es valido.\n");
                    vehiculo->valorResidual =
                        leerDoubleNoNegativo("Nuevo valor residual: ");

                    while (vehiculo->valorResidual >= vehiculo->costo)
                    {
                        printf("Debe ser menor que el costo.\n");
                        vehiculo->valorResidual =
                            leerDoubleNoNegativo("Nuevo valor residual: ");
                    }
                }
                break;

            case 5:
                vehiculo->valorResidual =
                    leerDoubleNoNegativo("Nuevo valor residual: ");

                while (vehiculo->valorResidual >= vehiculo->costo)
                {
                    printf("Debe ser menor que el costo.\n");
                    vehiculo->valorResidual =
                        leerDoubleNoNegativo("Nuevo valor residual: ");
                }
                break;

            case 6:
                vehiculo->vidaUtil =
                    leerEnteroPositivo("Nueva vida util: ");
                break;

            case 7:
                vehiculo->kmAnuales =
                    leerDoublePositivo("Nuevos km anuales: ");
                break;

            case 8:
                vehiculo->precioCombustible =
                    leerDoublePositivo("Nuevo precio combustible: ");
                break;

            case 9:
                vehiculo->kmPorLitroCiudad =
                    leerDoublePositivo("Nuevo rendimiento ciudad: ");
                break;

            case 10:
                vehiculo->kmPorLitroAutopista =
                    leerDoublePositivo("Nuevo rendimiento autopista: ");
                break;

            case 11:
                vehiculo->seguroAnual =
                    leerDoubleNoNegativo("Nuevo seguro anual: ");
                break;

            case 12:
                vehiculo->mantenimientoAnual =
                    leerDoubleNoNegativo("Nuevo mantenimiento anual: ");
                break;

            case 13:
                vehiculo->precioNeumatico =
                    leerDoublePositivo("Nuevo precio neumatico: ");
                break;

            case 14:
                vehiculo->cantidadNeumaticos =
                    leerEnteroPositivo("Nueva cantidad: ");
                break;

            case 15:
                vehiculo->vidaUtilNeumatico =
                    leerDoublePositivo("Nueva vida util en km: ");
                break;

            case 16:
                vehiculo->porcentajeImprevistos =
                    leerDoubleNoNegativo("Nuevo porcentaje: ");
                break;

            case 0:
                break;
        }

    } while (opcion != 0);
}

void mostrarVehiculo(const Vehiculo *vehiculo)
{
    printf(
        "%-4d %-15s %-15s %-8d\n",
        vehiculo->id,
        vehiculo->marca,
        vehiculo->modelo,
        vehiculo->anio
    );
}

void mostrarVehiculoDetallado(const Vehiculo *vehiculo)
{
    printf("\n========================================\n");
    printf("       INFORMACION DEL VEHICULO\n");
    printf("========================================\n");

    printf("ID: %d\n", vehiculo->id);
    printf("Marca: %s\n", vehiculo->marca);
    printf("Modelo: %s\n", vehiculo->modelo);
    printf("Ano: %d\n", vehiculo->anio);

    printf("\n--- COMPRA Y VIDA UTIL ---\n");
    printf("Costo: RD$ %.2f\n", vehiculo->costo);
    printf("Valor residual: RD$ %.2f\n", vehiculo->valorResidual);
    printf("Vida util: %d anos\n", vehiculo->vidaUtil);

    printf("\n--- UTILIZACION ---\n");
    printf("Km anuales: %.2f\n", vehiculo->kmAnuales);

    printf("\n--- COMBUSTIBLE ---\n");
    printf("Precio: RD$ %.2f/L\n", vehiculo->precioCombustible);
    printf("Ciudad: %.2f km/L\n", vehiculo->kmPorLitroCiudad);
    printf("Autopista: %.2f km/L\n", vehiculo->kmPorLitroAutopista);

    printf("\n--- GASTOS ---\n");
    printf("Seguro anual: RD$ %.2f\n", vehiculo->seguroAnual);
    printf("Mantenimiento anual: RD$ %.2f\n",
           vehiculo->mantenimientoAnual);

    printf("\n--- NEUMATICOS ---\n");
    printf("Precio por neumatico: RD$ %.2f\n",
           vehiculo->precioNeumatico);
    printf("Cantidad: %d\n", vehiculo->cantidadNeumaticos);
    printf("Vida util: %.2f km\n", vehiculo->vidaUtilNeumatico);

    printf("\n--- IMPREVISTOS ---\n");
    printf("Porcentaje: %.2f%%\n",
           vehiculo->porcentajeImprevistos);

    printf("========================================\n");
}
