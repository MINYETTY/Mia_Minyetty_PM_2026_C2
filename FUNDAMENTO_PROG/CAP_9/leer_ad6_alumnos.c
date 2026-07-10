#include <stdio.h>

/*
    Este programa lee el archivo binario ad6_alumnos.dat.

    Ese archivo lo crea el Programa 9.19.
    Sirve para verificar que los alumnos quedaron ordenados
    de menor a mayor por matricula.
*/

typedef struct {
    int matricula;
    char nombre[30];
    char carrera[30];
    float promedio;
} alumno;

int main(void) {
    FILE *ar;
    alumno alu;
    int contador = 0;

    ar = fopen("ad6_alumnos.dat", "rb");

    if (ar == NULL) {
        printf("No se pudo abrir ad6_alumnos.dat\n");
        printf("Primero ejecuta el Programa 9.19.\n");
        return 1;
    }

    printf("\nALUMNOS ORDENADOS DE MENOR A MAYOR\n");

    while (fread(&alu, sizeof(alumno), 1, ar) == 1) {
        contador++;

        printf("\nAlumno %d", contador);
        printf("\nMatricula: %d", alu.matricula);
        printf("\nNombre: %s", alu.nombre);
        printf("\nCarrera: %s", alu.carrera);
        printf("\nPromedio: %.2f\n", alu.promedio);
    }

    fclose(ar);

    if (contador == 0) {
        printf("\nEl archivo esta vacio.\n");
    }

    return 0;
}