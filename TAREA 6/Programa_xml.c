#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*NO BULTO MIA LA MEJOR*/

typedef struct {
    char nombre[50];
    char apellido[50];
    float promedio;
    char materia[50];
} Alumno;

/* Prototipos de funciones  */
int ContarRegistros(FILE *);
void CargarDatos(FILE *, Alumno *, int);
void ImprimirDatos(Alumno *, int);

int main() {
    FILE *ar;
    Alumno *arreglo;
    int n;

    if ((ar = fopen("Alumno.xml", "r")) != NULL) { /*  */
        n = ContarRegistros(ar);
        printf("Cantidad de alumnos detectados en XML: %d\n", n);

        if (n > 0) {
            arreglo = (Alumno *)malloc(n * sizeof(Alumno));
            if (arreglo != NULL) {
                rewind(ar); /*  */
                CargarDatos(ar, arreglo, n);
                ImprimirDatos(arreglo, n);
                free(arreglo);
            } else {
                printf("Error en asignación de memoria.\n");
            }
        }
        fclose(ar); /* [cite: 3197] */
    } else {
        printf("No se puede abrir el archivo\n");
    }
    return 0;
}

int ContarRegistros(FILE *ap) {
    char linea[256];
    int c = 0;
    while (!feof(ap)) { /* [cite: 3231, 3232] */
        if (fgets(linea, sizeof(linea), ap)) {
            if (strstr(linea, "<alumno>")) {
                c++;
            }
        }
    }
    return c;
}

void CargarDatos(FILE *ap, Alumno *A, int T) {
    char linea[256];
    int i = -1;
    char *pos;

    while (fgets(linea, sizeof(linea), ap)) {
        if (strstr(linea, "<alumno>")) {
            i++;
            continue;
        }
        if (i >= 0 && i < T) {
            if ((pos = strstr(linea, "<nombre>"))) {
                sscanf(pos, "<nombre>%[^<]</nombre>", A[i].nombre);
            } else if ((pos = strstr(linea, "<apellido>"))) {
                sscanf(pos, "<apellido>%[^<]</apellido>", A[i].apellido);
            } else if ((pos = strstr(linea, "<promedio>"))) {
                sscanf(pos, "<promedio>%f</promedio>", &A[i].promedio);
            } else if ((pos = strstr(linea, "<materia>"))) {
                sscanf(pos, "<materia>%[^<]</materia>", A[i].materia);
            }
        }
    }
}

void ImprimirDatos(Alumno *A, int T) {
    int i;
    printf("\n================ DATOS DESDE XML ================\n");
    for (i = 0; i < T; i++) {
        printf("Alumno %d: %s %s | Promedio: %.2f | Materia: %s\n",
               i + 1, A[i].nombre, A[i].apellido, A[i].promedio, A[i].materia);
    }
}