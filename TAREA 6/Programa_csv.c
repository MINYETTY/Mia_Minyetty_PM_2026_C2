#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Declaracion de la estructura alumno utilizando typedef [cite: 2775]*/
typedef struct {
    char nombre[50];
    char apellido[50];
    char promedio[10];
    char materia[50];
} Alumno;

/*Prototipo de funciones [cite: 1184, 1191]*/
int ContarRegistros(FILE *);
void CargarDatos(FILE *, Alumno *, int);
void ImprimirDatos(Alumno *, int);

/*NO BULTO MIA LA MEJOR*/

int main() {
    FILE *ar;
    Alumno *arreglo;
    int n;

    /*Se abre el archivo para lectura y se verifica si se abrio correctamente [cite: 3231]*/
    if ((ar = fopen("Alumno.csv", "r")) != NULL) {
        n = ContarRegistros(ar);
        printf("Cantidad de alumnos detectados en CSV: %d\n", n);

        if (n > 0) {
            /* Se reserva la memoria dinamica requerida*/
            arreglo = (Alumno *)malloc(n * sizeof(Alumno));
            if (arreglo != NULL) {
                /* La funcion rewind reposiciona el apuntador al inicio del archivo*/
                rewind(ar);
                CargarDatos(ar, arreglo, n);
                ImprimirDatos(arreglo, n);
                free(arreglo); /* Se libera la memoria para evitar fugar */

            } else {
                printf("Error: Fallo en la asignacion de memoria. \n");
            }
        }
        fclose(ar); /* Se cierra el archivo para proteger la informacion [cite: 3197]*/
    } else {
        printf("No se puede abrir el archivo\n"); /* [cite: 3233]*/
    }
    return 0;

}

int ContarRegistros(FILE *ap) {
    char linea[256];
    int c = 0;

    if (fgets(linea, sizeof(linea), ap)) { /* Se salta la cabecera*/
/* Mientras no se detecte el fin del archivo se siguen leyendo cadenas de caracteres [cite: 3231, 3232]*/
        while (!feof(ap)){
            if (fgets(linea, sizeof(linea), ap) && strlen(linea) > 5) {
                c++;
            }
        }
    }
    return c;
}

void CargarDatos(FILE *ap, Alumno *A, int T) {
    char linea[256];
    int i = 0;
    char *token;

    fgets(linea, sizeof(linea), ap); /* Salta la cabecera nuevamente*/
    while (fgets(linea, sizeof(linea), ap) && i < T) {
        linea[strcspn(linea, "\r\n")] = 0;

        token = strtok(linea, ",");
        if (token) strcpy(A[i].nombre, token);

        token = strtok(NULL, ",");
        if (token) strcpy(A[i].apellido, token);

        token = strtok(NULL, ",");
        /*La funcion atof convierte una cadena de caracteres que contiene numeros reales a un valor */
        if (token) strcpy(A[i].promedio, token);

        token = strtok(NULL, ",");
        if (token) strcpy(A[i].materia, token);
    
        i++;
    }
 } /* Close the previous function */

    void ImprimirDatos(Alumno *A, int T)
    {
        int i;
        printf("\n============== DATOS DESDE CSV ==============\n");
        /* El ciclos iterativo itera a lo largo del array en memoria [cite: 1549]*/
        for (i = 0; i < T; i++) {
            printf("Alumno %d: %s %s | Promedio: %.2f | Materia: %s\n", i + 1, A[i].nombre, A[i].apellido, A[i].promedio, A[i].materia);
        }
    }