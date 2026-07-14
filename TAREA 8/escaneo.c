#include "escaneo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int escanear_carpeta(const char *ruta, char lista[][MAX_NOMBRE], int max_items) {
    DIR *dir = opendir(ruta);
    if (dir == NULL) {
        perror("No se pudo abrir el directorio");
        return -1;
    }

    struct dirent *entrada;
    int contador = 0;

    while ((entrada = readdir(dir)) != NULL && contador < max_items) {
        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
            continue;
        }

        char ruta_completa[MAX_NOMBRE * 2];
        snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s", ruta, entrada->d_name);

        struct stat info;
        if (stat(ruta_completa, &info) == 0 && S_ISREG(info.st_mode)) {
            strncpy(lista[contador], entrada->d_name, MAX_NOMBRE - 1);
            lista[contador][MAX_NOMBRE - 1] = '\0';
            contador++;
        }
    }

    closedir(dir);
    return contador;
}

int mostrar_menu_y_elegir(char lista[][MAX_NOMBRE], int total) {
    if (total <= 0) {
        printf("No se encontraron archivos en el directorio.\n");
        return -1;
    }

    printf("\n===== Archivos disponibles =====\n");
    for (int i = 0; i < total; i++) {
        printf("  [%2d] %s\n", i + 1, lista[i]);
    }
    printf("  [ 0] Salir\n");
    printf("=================================\n");

    while (1) {
        printf("Seleccione el numero del archivo: ");

        char buffer[32];
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return -1;
        }

        char *fin;
        long valor = strtol(buffer, &fin, 10);

        if (fin == buffer) {
            printf("Entrada invalida. Ingrese un numero.\n");
            continue;
        }
        if (valor == 0) {
            return -1;
        }
        if (valor < 1 || valor > total) {
            printf("Numero fuera de rango. Intente de nuevo.\n");
            continue;
        }

        return (int)valor - 1;
    }
}
