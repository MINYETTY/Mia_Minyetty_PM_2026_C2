#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
#define MAX_NOMBRES 20
#define LONG_NOMBRE 50
 
typedef struct Estudiante {
    int id;
    float promedio;
    char nombre[LONG_NOMBRE];
} Estudiante;
 
typedef struct Nodo {
    Estudiante dato;
    struct Nodo *siguiente;
} Nodo;
 
Nodo *crearNodo(Estudiante e) {
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("Error: no se pudo asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    nuevo->dato = e;
    nuevo->siguiente = NULL;
    return nuevo;
}
 
void insertarFinal(Nodo **cabeza, Estudiante e) {
    Nodo *nuevo = crearNodo(e);
    if (*cabeza == NULL) {
        *cabeza = nuevo;
        return;
    }
    Nodo *actual = *cabeza;
    while (actual->siguiente != NULL) {
        actual = actual->siguiente;
    }
    actual->siguiente = nuevo;
}
 
void generarNombreAleatorio(char *nombre) {
    char *nombres[] = {
        "Juan", "Maria", "Pedro", "Ana", "Luis",
        "Laura", "Carlos", "Sofia", "Jorge", "Elena",
        "Diego", "Paula", "Andres", "Lucia", "Miguel",
        "Carmen", "Raul", "Isabel", "Fernando", "Teresa"
    };
    char *apellidos[] = {
        "Garcia", "Rodriguez", "Martinez", "Lopez", "Sanchez",
        "Perez", "Gomez", "Fernandez", "Ruiz", "Diaz",
        "Torres", "Ramirez", "Vargas", "Castro", "Romero",
        "Ortiz", "Silva", "Mendoza", "Cruz", "Rios"
    };
    int n = rand() % MAX_NOMBRES;
    int a = rand() % MAX_NOMBRES;
    snprintf(nombre, LONG_NOMBRE, "%s %s", nombres[n], apellidos[a]);
}
 
void llenarLista(Nodo **cabeza, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        Estudiante e;
        e.id = 1000 + rand() % 9000;
        e.promedio = (float)(rand() % 1000) / 100.0f;
        generarNombreAleatorio(e.nombre);
        insertarFinal(cabeza, e);
    }
}
 
void imprimirLista(Nodo *cabeza) {
    Nodo *actual = cabeza;
    printf("%-8s %-20s %s\n", "ID", "Nombre", "Promedio");
    printf("--------------------------------------------\n");
    while (actual != NULL) {
        printf("%-8d %-20s %.2f\n", actual->dato.id, actual->dato.nombre, actual->dato.promedio);
        actual = actual->siguiente;
    }
}
 
void liberarLista(Nodo *cabeza) {
    Nodo *actual = cabeza;
    while (actual != NULL) {
        Nodo *tmp = actual;
        actual = actual->siguiente;
        free(tmp);
    }
}
 
void bubbleSortPorId(Nodo *cabeza) {
    if (cabeza == NULL) return;
    int intercambiado;
    Nodo *ptr;
    Nodo *limite = NULL;
 
    do {
        intercambiado = 0;
        ptr = cabeza;
        while (ptr->siguiente != limite) {
            if (ptr->dato.id > ptr->siguiente->dato.id) {
                Estudiante tmp = ptr->dato;
                ptr->dato = ptr->siguiente->dato;
                ptr->siguiente->dato = tmp;
                intercambiado = 1;
            }
            ptr = ptr->siguiente;
        }
        limite = ptr;
    } while (intercambiado);
}
 
void bubbleSortPorPromedio(Nodo *cabeza) {
    if (cabeza == NULL) return;
    int intercambiado;
    Nodo *ptr;
    Nodo *limite = NULL;
 
    do {
        intercambiado = 0;
        ptr = cabeza;
        while (ptr->siguiente != limite) {
            if (ptr->dato.promedio > ptr->siguiente->dato.promedio) {
                Estudiante tmp = ptr->dato;
                ptr->dato = ptr->siguiente->dato;
                ptr->siguiente->dato = tmp;
                intercambiado = 1;
            }
            ptr = ptr->siguiente;
        }
        limite = ptr;
    } while (intercambiado);
}
 
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
 
void agregarEstudiante(Nodo **cabeza) {
    Estudiante e;
    printf("\n--- Agregar nuevo estudiante ---\n");
    printf("ID: ");
    if (scanf("%d", &e.id) != 1) { printf("ID invalido\n"); limpiarBuffer(); return; }
    limpiarBuffer();
    printf("Nombre (nombre y apellido): ");
    if (fgets(e.nombre, LONG_NOMBRE, stdin) == NULL) { printf("Nombre invalido\n"); return; }
    e.nombre[strcspn(e.nombre, "\n")] = '\0';
    printf("Promedio (0.00 - 10.00): ");
    if (scanf("%f", &e.promedio) != 1) { printf("Promedio invalido\n"); limpiarBuffer(); return; }
    limpiarBuffer();
    insertarFinal(cabeza, e);
    printf("Estudiante agregado correctamente.\n");
}
 
void bubbleSortPorNombre(Nodo *cabeza) {
    if (cabeza == NULL) return;
    int intercambiado;
    Nodo *ptr;
    Nodo *limite = NULL;
 
    do {
        intercambiado = 0;
        ptr = cabeza;
        while (ptr->siguiente != limite) {
            if (strcmp(ptr->dato.nombre, ptr->siguiente->dato.nombre) > 0) {
                Estudiante tmp = ptr->dato;
                ptr->dato = ptr->siguiente->dato;
                ptr->siguiente->dato = tmp;
                intercambiado = 1;
            }
            ptr = ptr->siguiente;
        }
        limite = ptr;
    } while (intercambiado);
}
 
Nodo *copiarLista(Nodo *cabeza) {
    Nodo *copia = NULL;
    Nodo *actual = cabeza;
    while (actual != NULL) {
        insertarFinal(&copia, actual->dato);
        actual = actual->siguiente;
    }
    return copia;
}
 
void mostrarOrdenada(Nodo *cabeza, int criterio) {
    Nodo *copia = copiarLista(cabeza);
    switch (criterio) {
        case 1:
            bubbleSortPorId(copia);
            printf("\n=== Lista ordenada por ID ===\n");
            break;
        case 2:
            bubbleSortPorPromedio(copia);
            printf("\n=== Lista ordenada por Promedio ===\n");
            break;
        case 3:
            bubbleSortPorNombre(copia);
            printf("\n=== Lista ordenada por Nombre ===\n");
            break;
    }
    imprimirLista(copia);
    liberarLista(copia);
}
 
int main() {
    srand((unsigned int)time(NULL));
 
    Nodo *lista = NULL;
    llenarLista(&lista, 20);
 
    int opcion;
    do {
        printf("\n================ MENU ================\n");
        printf("1) Agregar un estudiante\n");
        printf("2) Mostrar lista ordenada por ID\n");
        printf("3) Mostrar lista ordenada por Promedio\n");
        printf("4) Mostrar lista ordenada por Nombre\n");
        printf("5) Salir\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) { limpiarBuffer(); continue; }
        limpiarBuffer();
        switch (opcion) {
            case 1:
                agregarEstudiante(&lista);
                break;
            case 2:
                mostrarOrdenada(lista, 1);
                break;
            case 3:
                mostrarOrdenada(lista, 2);
                break;
            case 4:
                mostrarOrdenada(lista, 3);
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 5);
 
    liberarLista(lista);
    return 0;
}