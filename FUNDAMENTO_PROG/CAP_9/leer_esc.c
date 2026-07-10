#include <stdio.h>

/*
    Este programa lee el archivo binario esc.dat.

    Ese archivo se crea con crear_esc.c
    y lo usa el Programa 9.20.
*/

typedef struct {
    char materia[30];
    int calificacion;
} matcal;

typedef struct {
    int matricula;
    char nombre[30];
    matcal cal[5];
} alumno;

int main(void) {
    FILE *ap;
    alumno alu;
    int contador = 0;
    int i;

    ap = fopen("esc.dat", "rb");

    if (ap == NULL) {
        printf("No se pudo abrir esc.dat\n");
        printf("Primero ejecuta crear_esc.exe.\n");
        return 1;
    }

    printf("\nCONTENIDO DE ESC.DAT\n");

    while (fread(&alu, sizeof(alumno), 1, ap) == 1) {
        contador++;

        printf("\nAlumno %d", contador);
        printf("\nMatricula: %d", alu.matricula);
        printf("\nNombre: %s", alu.nombre);

        for (i = 0; i < 5; i++) {
            printf("\nMateria %d: %s", i + 1, alu.cal[i].materia);
            printf("\nCalificacion: %d", alu.cal[i].calificacion);
        }

        printf("\n");
    }

    fclose(ap);

    if (contador == 0) {
        printf("\nEl archivo esta vacio.\n");
    }

    return 0;
}