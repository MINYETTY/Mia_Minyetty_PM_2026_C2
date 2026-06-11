#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Juego de Lotería.
El programa permite al usuario configurar una cantidad de jugadas, ingresar 
sus nmeros junto al dinero apostado, y verificar si ha ganado multiplicando 
su apuesta por 1000 si acierta el número premiado. */

const int MAX = 50;

void main(void)
{
    int OPCION;
    int CANT = 1;               /* Por defecto se inicia permitiendo 1 jugada. */
    int NUMEROS[MAX];
    float DINERO[MAX];
    int I, GANADOR, GANO;
    float PREMIO;

    srand(time(NULL));          /* Inicializa la semilla para el sorteo aleatorio. */

    do
    {
        printf("\n\n--- MENU DE LOTERIA ---");
        printf("\n1. Jugar");
        printf("\n2. Elegir cantidad de jugadas (Actual: %d)", CANT);
        printf("\n3. Salir");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &OPCION);

        switch (OPCION)
        {
            case 1:
                printf("\n--- INGRESO DE JUGADAS --- \n");
                for (I = 0; I < CANT; I++)
                {
                    /* Validación: El número debe estar entre 1 y 40 */
                    do
                    {
                        printf("Jugada %d - Ingrese numero (1-40): ", I + 1);
                        scanf("%d", &NUMEROS[I]);
                        if (NUMEROS[I] < 1 || NUMEROS[I] > 40)
                            printf("Numero invalido. Debe estar entre 1 y 40.\n");
                    }
                    while (NUMEROS[I] < 1 || NUMEROS[I] > 40);

                    /* Validación: El dinero apostado debe ser mayor a cero */
                    do
                    {
                        printf("Jugada %d - Ingrese dinero a apostar: ", I + 1);
                        scanf("%f", &DINERO[I]);
                        if (DINERO[I] <= 0)
                            printf("El dinero debe ser mayor a 0.\n");
                    }
                    while (DINERO[I] <= 0);
                }

                /* Sorteo del número ganador (Genera un número entre 1 y 40) */
                GANADOR = (rand() % 40) + 1;
                printf("\n=================================");
                printf("\n¡EL NUMERO GANADOR DE HOY ES: %d!", GANADOR);
                printf("\n=================================\n");

                GANO = 0;       /* Variable bandera para saber si hubo algún premio. */
                
                /* Verificación de las jugadas */
                for (I = 0; I < CANT; I++)
                {
                    if (NUMEROS[I] == GANADOR)
                    {
                        PREMIO = DINERO[I] * 1000;
                        printf("\n¡Felicidades! Acertaste con el numero %d. Ganaste: %.2f", NUMEROS[I], PREMIO);
                        GANO = 1;
                    }
                }

                if (GANO == 0)
                    printf("\nNo hubo suerte en tus jugadas. ¡Sigue intentando!");
                break;

            case 2:
                /* Permite cambiar la cantidad de jugadas que se harán en la opción 1 */
                do
                {
                    printf("\n¿Cuantas jugadas deseas preparar? (1-%d): ", MAX);
                    scanf("%d", &CANT);
                    if (CANT < 1 || CANT > MAX)
                        printf("Cantidad no permitida. Intente de nuevo.");
                }
                while (CANT < 1 || CANT > MAX);
                break;

            case 3:
                printf("\n¡Gracias por jugar! Hasta luego.\n");
                break;

            default:
                printf("\nOpcion no valida. Intente de nuevo.");
                break;
        }
    }
    // El menu se repite siempre que la opción no sea 3 (Salir)
    while (OPCION != 3); 
}