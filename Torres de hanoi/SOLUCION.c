#include <stdio.h>
#include <stdlib.h>

/*
 Función recursiva que resuelve las Torres de Hanói.
 n       -> número de discos a mover
 origen  -> poste de origen
 auxiliar-> poste auxiliar
 destino -> poste destino
 contador-> puntero al contador global de movimientos
 archivo -> puntero al archivo donde se registra cada movimiento
 */

void hanoi(int n, char origen, char auxiliar, char destino,
           int *contador, FILE *archivo) {

    // Caso base: no hay discos que mover
    if (n == 0) {
        return;
    }

    // 1. Mover n-1 discos de origen a auxiliar, usando destino como apoyo
    hanoi(n - 1, origen, destino, auxiliar, contador, archivo);

    // 2. Mover el disco n de origen a destino (el movimiento "real")
    (*contador)++;  // Se incrementa el contador a través del puntero

    printf("Movimiento %d: Mover disco %d de %c a %c\n",
           *contador, n, origen, destino);

    fprintf(archivo, "Movimiento %d: Mover disco %d de %c a %c\n",
            *contador, n, origen, destino);

    // 3. Mover n-1 discos de auxiliar a destino, usando origen como apoyo
    hanoi(n - 1, auxiliar, origen, destino, contador, archivo);
}

int main(void) {
    int numDiscos;
    int movimientos = 0;      // Contador de movimientos
    FILE *archivo;            // Puntero al archivo de salida

    printf("=== Torres de Hanoi ===\n");
    printf("Ingrese el numero de discos: ");

    if (scanf("%d", &numDiscos) != 1 || numDiscos <= 0) {
        printf("Numero de discos invalido.\n");
        return EXIT_FAILURE;
    }

    // Apertura del archivo en modo escritura ("w" sobreescribe si ya existe)
    archivo = fopen("movimientos.txt", "w");
    if (archivo == NULL) {
        printf("Error: no se pudo crear/abrir el archivo movimientos.txt\n");
        return EXIT_FAILURE;
    }

    // Encabezado informativo en el archivo
    fprintf(archivo, "Registro de movimientos - Torres de Hanoi (%d discos)\n",
            numDiscos);
    fprintf(archivo, "--------------------------------------------------\n");

    // Llamada inicial: mover todos los discos de A a C, usando B como auxiliar
    hanoi(numDiscos, 'A', 'B', 'C', &movimientos, archivo);

    // Cierre del archivo
    fclose(archivo);

    printf("\nTotal de movimientos realizados: %d\n", movimientos);
    printf("El registro completo se guardo en 'movimientos.txt'\n");

    return EXIT_SUCCESS;
}