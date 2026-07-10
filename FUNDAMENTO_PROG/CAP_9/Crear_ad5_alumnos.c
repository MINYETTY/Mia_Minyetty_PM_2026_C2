#include <stdio.h>
#include <string.h>

/*
    Este programa crea el archivo binario ad5_alumnos.dat.

    Ese archivo lo necesita el Programa 9.19.

    Importante:
    Los alumnos deben guardarse de MAYOR a MENOR por matricula,
    porque el Programa 9.19 los lee al reves para crear ad6_alumnos.dat
    de MENOR a MAYOR.
*/

typedef struct {
    int matricula;
    char nombre[30];
    char carrera[30];
    float promedio;
} alumno;

void limpiar_buffer(void);
void limpiar_salto(char []);
int leer_entero(char []);
float leer_real(char []);

int main(void) {
    FILE *ar;
    alumno alu;
    int i, n;

    ar = fopen("ad5_alumnos.dat", "wb");

    if (ar == NULL) {
        printf("No se pudo crear ad5_alumnos.dat\n");
        return 1;
    }

    n = leer_entero("Cuantos alumnos desea registrar?: ");

    printf("\nRecuerda ingresar las matriculas de MAYOR a MENOR.\n");

    for (i = 0; i < n; i++) {
        printf("\nAlumno %d\n", i + 1);

        alu.matricula = leer_entero("Matricula: ");

        printf("Nombre: ");
        fgets(alu.nombre, sizeof(alu.nombre), stdin);
        limpiar_salto(alu.nombre);

        printf("Carrera: ");
        fgets(alu.carrera, sizeof(alu.carrera), stdin);
        limpiar_salto(alu.carrera);

        alu.promedio = leer_real("Promedio: ");

        fwrite(&alu, sizeof(alumno), 1, ar);
    }

    fclose(ar);

    printf("\nArchivo ad5_alumnos.dat creado correctamente.\n");

    return 0;
}

void limpiar_buffer(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void limpiar_salto(char cadena[]) {
    cadena[strcspn(cadena, "\n")] = '\0';
}

int leer_entero(char mensaje[]) {
    int valor;

    while (1) {
        printf("%s", mensaje);

        if (scanf("%d", &valor) == 1) {
            limpiar_buffer();
            return valor;
        }

        printf("Entrada invalida. Escriba un numero entero.\n");
        limpiar_buffer();
    }
}

float leer_real(char mensaje[]) {
    float valor;

    while (1) {
        printf("%s", mensaje);

        if (scanf("%f", &valor) == 1) {
            limpiar_buffer();
            return valor;
        }

        printf("Entrada invalida. Escriba un numero.\n");
        limpiar_buffer();
    }
}