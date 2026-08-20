/*
 * ============================================================
 * Archivo: main.c
 * Proyecto: Vehicle Cost Manager
 *
 * Propósito:
 * Punto de entrada del programa y menú principal.
 *
 * El programa administra múltiples vehículos mediante memoria
 * dinámica y permite guardar/cargar sus datos en CSV.
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/vehiculo.h"
#include "../include/calculos.h"
#include "../include/viaje.h"
#include "../include/archivo.h"
#include "../include/memoria.h"
#include "../include/utilidades.h"


#define MAX_ARCHIVO 250


/*
 * Busca un vehículo por su ID y devuelve su posición.
 * Devuelve -1 si no se encuentra.
 */
int buscarPorId(
    const Vehiculo *vehiculos,
    int cantidad,
    int id
)
{
    int i;

    for (i = 0; i < cantidad; i++)
    {
        if (vehiculos[i].id == id)
        {
            return i;
        }
    }

    return -1;
}


/*
 * Genera un ID nuevo para el próximo vehículo.
 */
int generarNuevoId(
    const Vehiculo *vehiculos,
    int cantidad
)
{
    int i;
    int mayor = 0;

    for (i = 0; i < cantidad; i++)
    {
        if (vehiculos[i].id > mayor)
        {
            mayor = vehiculos[i].id;
        }
    }

    return mayor + 1;
}


/*
 * Muestra todos los vehículos registrados.
 */
void mostrarTodos(
    const Vehiculo *vehiculos,
    int cantidad
)
{
    int i;

    if (cantidad == 0)
    {
        printf("\nNo hay vehiculos cargados.\n");
        return;
    }

    printf("\n========================================\n");
    printf("             VEHICULOS\n");
    printf("========================================\n");

    printf(
        "%-4s %-15s %-15s %-8s\n",
        "ID",
        "MARCA",
        "MODELO",
        "ANO"
    );

    printf("----------------------------------------\n");

    for (i = 0; i < cantidad; i++)
    {
        mostrarVehiculo(&vehiculos[i]);
    }
}


/*
 * Permite seleccionar un vehículo por ID.
 */
int seleccionarVehiculo(
    const Vehiculo *vehiculos,
    int cantidad
)
{
    int id;

    if (cantidad == 0)
    {
        printf("\nNo hay vehiculos disponibles.\n");
        return -1;
    }

    mostrarTodos(vehiculos, cantidad);

    id = leerEnteroPositivo("\nIntroduzca el ID: ");

    return buscarPorId(vehiculos, cantidad, id);
}


/*
 * Cambia el precio del combustible de un vehículo.
 */
void cambiarPrecioCombustible(
    Vehiculo *vehiculo
)
{
    printf("\nVehiculo: %s %s\n",
           vehiculo->marca,
           vehiculo->modelo);

    vehiculo->precioCombustible =
        leerDoublePositivo(
            "Nuevo precio del combustible (RD$/L): "
        );

    printf("Precio actualizado correctamente.\n");
}


/*
 * Ordena vehículos por costo real promedio aproximado.
 * Utilizamos una ordenación sencilla para mantener el código
 * fácil de entender.
 */
void ordenarPorCostoCiudad(
    Vehiculo *vehiculos,
    int cantidad
)
{
    int i;
    int j;

    for (i = 0; i < cantidad - 1; i++)
    {
        for (j = 0; j < cantidad - i - 1; j++)
        {
            if (
                calcularCostoRealKmCiudad(&vehiculos[j])
                >
                calcularCostoRealKmCiudad(&vehiculos[j + 1])
            )
            {
                Vehiculo temporal = vehiculos[j];
                vehiculos[j] = vehiculos[j + 1];
                vehiculos[j + 1] = temporal;
            }
        }
    }
}


/*
 * Compara dos vehículos según su costo real por km en ciudad.
 */
void compararVehiculos(
    const Vehiculo *vehiculos,
    int cantidad
)
{
    int pos1;
    int pos2;

    if (cantidad < 2)
    {
        printf("\nSe necesitan al menos dos vehiculos.\n");
        return;
    }

    printf("\nSeleccione el primer vehiculo.\n");
    pos1 = seleccionarVehiculo(vehiculos, cantidad);

    if (pos1 == -1)
    {
        printf("Vehiculo no encontrado.\n");
        return;
    }

    printf("\nSeleccione el segundo vehiculo.\n");
    pos2 = seleccionarVehiculo(vehiculos, cantidad);

    if (pos2 == -1)
    {
        printf("Vehiculo no encontrado.\n");
        return;
    }

    printf("\n========================================\n");
    printf("          COMPARACION DE VEHICULOS\n");
    printf("========================================\n");

    printf(
        "%s %s: RD$ %.4f/km en ciudad\n",
        vehiculos[pos1].marca,
        vehiculos[pos1].modelo,
        calcularCostoRealKmCiudad(&vehiculos[pos1])
    );

    printf(
        "%s %s: RD$ %.4f/km en ciudad\n",
        vehiculos[pos2].marca,
        vehiculos[pos2].modelo,
        calcularCostoRealKmCiudad(&vehiculos[pos2])
    );

    if (
        calcularCostoRealKmCiudad(&vehiculos[pos1])
        <
        calcularCostoRealKmCiudad(&vehiculos[pos2])
    )
    {
        printf(
            "\nEl primer vehiculo tiene menor costo por km en ciudad.\n"
        );
    }
    else if (
        calcularCostoRealKmCiudad(&vehiculos[pos1])
        >
        calcularCostoRealKmCiudad(&vehiculos[pos2])
    )
    {
        printf(
            "\nEl segundo vehiculo tiene menor costo por km en ciudad.\n"
        );
    }
    else
    {
        printf("\nAmbos tienen el mismo costo por km en ciudad.\n");
    }
}


/*
 * Menú principal.
 */
int main(void)
{
    Vehiculo *vehiculos = NULL;
    int cantidad = 0;

    char archivoActual[MAX_ARCHIVO] = "data/vehiculos.csv";

    int opcion;

    /*
     * Intentamos cargar automáticamente el archivo principal.
     * Si no existe, el programa inicia vacío.
     */
    if (cargarVehiculos(
            archivoActual,
            &vehiculos,
            &cantidad
        ))
    {
        printf(
            "Se cargaron %d vehiculo(s) desde %s.\n",
            cantidad,
            archivoActual
        );
    }

    do
    {
        printf("\n\n");
        printf("============================================\n");
        printf("          VEHICLE COST MANAGER\n");
        printf("============================================\n");

        printf("Archivo actual: %s\n", archivoActual);
        printf("Vehiculos cargados: %d\n", cantidad);

        printf("\n");
        printf("1. Crear archivo\n");
        printf("2. Abrir archivo\n");
        printf("3. Crear vehiculo\n");
        printf("4. Mostrar vehiculos\n");
        printf("5. Mostrar detalle de vehiculo\n");
        printf("6. Modificar vehiculo\n");
        printf("7. Eliminar vehiculo\n");
        printf("8. Calcular costos del vehiculo\n");
        printf("9. Calcular viaje\n");
        printf("10. Modificar precio del combustible\n");
        printf("11. Comparar vehiculos\n");
        printf("12. Ordenar por costo/km en ciudad\n");
        printf("13. Guardar cambios\n");
        printf("0. Salir\n");

        opcion = leerEnteroRango(
            "\nSeleccione una opcion: ",
            0,
            13
        );

        switch (opcion)
        {
            case 1:
            {
                char nuevoArchivo[MAX_ARCHIVO];

                leerCadena(
                    "Nombre del archivo (ej. empresa.csv): ",
                    nuevoArchivo,
                    sizeof(nuevoArchivo)
                );

                /*
                 * Si el usuario no escribe la carpeta data/,
                 * la agregamos automáticamente.
                 */
                snprintf(
                    archivoActual,
                    sizeof(archivoActual),
                    "data/%s",
                    nuevoArchivo
                );

                if (crearArchivo(archivoActual))
                {
                    liberarVehiculos(&vehiculos);
                    cantidad = 0;

                    printf(
                        "Archivo creado: %s\n",
                        archivoActual
                    );
                }
                else
                {
                    printf("No se pudo crear el archivo.\n");
                }

                break;
            }

            case 2:
            {
                char nuevoArchivo[MAX_ARCHIVO];
                Vehiculo *nuevos = NULL;
                int nuevaCantidad = 0;

                leerCadena(
                    "Nombre del archivo (ej. empresa.csv): ",
                    nuevoArchivo,
                    sizeof(nuevoArchivo)
                );

                snprintf(
                    archivoActual,
                    sizeof(archivoActual),
                    "data/%s",
                    nuevoArchivo
                );

                if (
                    cargarVehiculos(
                        archivoActual,
                        &nuevos,
                        &nuevaCantidad
                    )
                )
                {
                    liberarVehiculos(&vehiculos);

                    vehiculos = nuevos;
                    cantidad = nuevaCantidad;

                    printf(
                        "Archivo cargado. Vehiculos: %d\n",
                        cantidad
                    );
                }
                else
                {
                    printf(
                        "No se pudo abrir/cargar el archivo.\n"
                    );
                }

                break;
            }

            case 3:
            {
                Vehiculo nuevo;

                crearVehiculo(
                    &nuevo,
                    generarNuevoId(vehiculos, cantidad)
                );

                {
                    Vehiculo *resultado =
                        agregarVehiculo(
                            vehiculos,
                            &cantidad,
                            nuevo
                        );

                    /*
                     * Solo reemplazamos el puntero si la operación
                     * fue exitosa o si el arreglo original era NULL.
                     */
                    if (resultado != NULL || cantidad > 0)
                    {
                        vehiculos = resultado;
                    }
                }

                break;
            }

            case 4:
                mostrarTodos(vehiculos, cantidad);
                pausar();
                break;

            case 5:
            {
                int posicion =
                    seleccionarVehiculo(
                        vehiculos,
                        cantidad
                    );

                if (posicion != -1)
                {
                    mostrarVehiculoDetallado(
                        &vehiculos[posicion]
                    );
                }
                else
                {
                    printf("Vehiculo no encontrado.\n");
                }

                pausar();
                break;
            }

            case 6:
            {
                int posicion =
                    seleccionarVehiculo(
                        vehiculos,
                        cantidad
                    );

                if (posicion != -1)
                {
                    modificarVehiculo(
                        &vehiculos[posicion]
                    );
                }
                else
                {
                    printf("Vehiculo no encontrado.\n");
                }

                break;
            }

            case 7:
            {
                int posicion =
                    seleccionarVehiculo(
                        vehiculos,
                        cantidad
                    );

                if (posicion != -1)
                {
                    int confirmar =
                        leerEnteroRango(
                            "Confirmar eliminacion? (1=Si, 0=No): ",
                            0,
                            1
                        );

                    if (confirmar == 1)
                    {
                        vehiculos =
                            eliminarVehiculo(
                                vehiculos,
                                &cantidad,
                                posicion
                            );

                        printf(
                            "Vehiculo eliminado correctamente.\n"
                        );
                    }
                }
                else
                {
                    printf("Vehiculo no encontrado.\n");
                }

                break;
            }

            case 8:
            {
                int posicion =
                    seleccionarVehiculo(
                        vehiculos,
                        cantidad
                    );

                if (posicion != -1)
                {
                    mostrarAnalisisCostos(
                        &vehiculos[posicion]
                    );
                }
                else
                {
                    printf("Vehiculo no encontrado.\n");
                }

                pausar();
                break;
            }

            case 9:
            {
                int posicion =
                    seleccionarVehiculo(
                        vehiculos,
                        cantidad
                    );

                if (posicion != -1)
                {
                    calcularViaje(
                        &vehiculos[posicion]
                    );
                }
                else
                {
                    printf("Vehiculo no encontrado.\n");
                }

                pausar();
                break;
            }

            case 10:
            {
                int posicion =
                    seleccionarVehiculo(
                        vehiculos,
                        cantidad
                    );

                if (posicion != -1)
                {
                    cambiarPrecioCombustible(
                        &vehiculos[posicion]
                    );
                }
                else
                {
                    printf("Vehiculo no encontrado.\n");
                }

                break;
            }

            case 11:
                compararVehiculos(
                    vehiculos,
                    cantidad
                );
                pausar();
                break;

            case 12:
                ordenarPorCostoCiudad(
                    vehiculos,
                    cantidad
                );

                printf(
                    "Vehiculos ordenados por costo/km en ciudad.\n"
                );

                mostrarTodos(vehiculos, cantidad);
                pausar();
                break;

            case 13:
                if (
                    guardarVehiculos(
                        archivoActual,
                        vehiculos,
                        cantidad
                    )
                )
                {
                    printf(
                        "Cambios guardados correctamente.\n"
                    );
                }
                else
                {
                    printf("No se pudieron guardar los cambios.\n");
                }

                break;

            case 0:
                /*
                 * Guardamos automáticamente antes de salir.
                 */
                if (
                    guardarVehiculos(
                        archivoActual,
                        vehiculos,
                        cantidad
                    )
                )
                {
                    printf("Cambios guardados.\n");
                }

                printf("Saliendo del programa...\n");
                break;
        }

    } while (opcion != 0);

    /*
     * Liberamos toda la memoria dinámica antes de terminar.
     */
    liberarVehiculos(&vehiculos);

    return 0;
}
