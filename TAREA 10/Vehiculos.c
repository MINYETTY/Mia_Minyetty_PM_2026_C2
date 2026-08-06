/* =====================================================================
   PROGRAMA: COSTO REAL DE OPERACION DE VEHICULOS
   -----------------------------------------------------------------
   Permite registrar vehiculos con sus parametros economicos y calcula:
     - Amortizacion del vehiculo (costo / vida util)
     - Gasto de mantenimiento a lo largo de la vida util
     - Consumo de combustible promedio
     - Costo por km en ciudad y en autopista
     - Costo real por km (amortizacion + mantenimiento + seguro +
       neumaticos + combustible)
     - Costo de un viaje especifico, dado km en ciudad y en autopista

   Persistencia:
     - Los vehiculos se guardan en el archivo binario "vehiculos.dat"
     - El precio del combustible se guarda en "combustible.cfg"

   Operaciones del menu:
     1. Crear vehiculo
     2. Borrar vehiculo
     3. Modificar parametros de un vehiculo
     4. Listar vehiculos
     5. Ver costos por km (ciudad/autopista) de un vehiculo
     6. Calcular costo de un viaje
     7. Modificar precio del combustible
     8. Salir
   ===================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVO_VEHICULOS "vehiculos.dat"
#define ARCHIVO_COMBUSTIBLE "combustible.cfg"
#define MAX_VEHICULOS 100
#define MAX_NOMBRE 50

/* ---------------------------------------------------------------------
   Estructura que representa un vehiculo y todos los parametros
   necesarios para calcular su costo real de operacion.
   --------------------------------------------------------------------- */
typedef struct {
    int    id;
    char   nombre[MAX_NOMBRE];       /* Ej: "Toyota Corolla 2020" */
    double costo;                    /* Costo de compra del vehiculo */
    int    vidaUtilAños;             /* Vida util estimada, en años */
    double kmAnualPromedio;          /* Km recorridos por año (promedio) */
    double mantenimientoAnual;       /* Gasto de mantenimiento por año */
    double seguroAnual;              /* Costo del seguro por año */
    double costoJuegoNeumaticos;     /* Costo de un juego de neumaticos */
    double vidaUtilNeumaticosKm;     /* Km que dura un juego de neumaticos */
    double consumoCiudad;            /* Rendimiento en ciudad, km/litro */
    double consumoAutopista;         /* Rendimiento en autopista, km/litro */
} Vehiculo;

/* ---------------------------------------------------------------------
   Prototipos
   --------------------------------------------------------------------- */
int cargarVehiculos(Vehiculo lista[]);
void guardarVehiculos(Vehiculo lista[], int n);
double cargarPrecioCombustible(void);
void guardarPrecioCombustible(double precio);

void crearVehiculo(void);
void borrarVehiculo(void);
void modificarVehiculo(void);
void listarVehiculos(void);
void verCostosPorKm(void);
void calcularViaje(void);
void modificarPrecioCombustible(void);

int buscarIndicePorId(Vehiculo lista[], int n, int id);
int siguienteId(Vehiculo lista[], int n);

double amortizacionPorKm(Vehiculo v);
double mantenimientoPorKm(Vehiculo v);
double seguroPorKm(Vehiculo v);
double neumaticosPorKm(Vehiculo v);
double consumoPromedio(Vehiculo v);
double costoPorKmCiudad(Vehiculo v, double precioCombustible);
double costoPorKmAutopista(Vehiculo v, double precioCombustible);

void limpiarBufer(void);
double leerDouble(const char *mensaje);
int leerEntero(const char *mensaje);
void leerTexto(const char *mensaje, char *destino, int tam);

/* =======================================================================
   MAIN: menu principal
   ======================================================================= */
int main(void) {
    int opcion;

    do {
        printf("\n===================================================\n");
        printf("   COSTO REAL DE OPERACION DE VEHICULOS\n");
        printf("===================================================\n");
        printf(" 1. Crear vehiculo\n");
        printf(" 2. Borrar vehiculo\n");
        printf(" 3. Modificar parametros de un vehiculo\n");
        printf(" 4. Listar vehiculos\n");
        printf(" 5. Ver costos por km (ciudad / autopista)\n");
        printf(" 6. Calcular costo de un viaje\n");
        printf(" 7. Modificar precio del combustible\n");
        printf(" 8. Salir\n");
        printf("---------------------------------------------------\n");
        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1: crearVehiculo(); break;
            case 2: borrarVehiculo(); break;
            case 3: modificarVehiculo(); break;
            case 4: listarVehiculos(); break;
            case 5: verCostosPorKm(); break;
            case 6: calcularViaje(); break;
            case 7: modificarPrecioCombustible(); break;
            case 8: printf("Hasta luego.\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while (opcion != 8);

    return 0;
}

/* =======================================================================
   PERSISTENCIA EN ARCHIVOS
   ======================================================================= */

/* Carga todos los vehiculos del archivo binario a la lista.
   Devuelve la cantidad de vehiculos leidos. */
int cargarVehiculos(Vehiculo lista[]) {
    FILE *f = fopen(ARCHIVO_VEHICULOS, "rb");
    if (f == NULL) return 0; /* No existe todavia: no hay vehiculos */

    int n = 0;
    n = (int) fread(lista, sizeof(Vehiculo), MAX_VEHICULOS, f);
    fclose(f);
    return n;
}

/* Sobrescribe el archivo binario con el contenido actual de la lista. */
void guardarVehiculos(Vehiculo lista[], int n) {
    FILE *f = fopen(ARCHIVO_VEHICULOS, "wb");
    if (f == NULL) {
        printf("Error: no se pudo escribir el archivo de vehiculos.\n");
        return;
    }
    fwrite(lista, sizeof(Vehiculo), n, f);
    fclose(f);
}

/* Lee el precio del combustible desde archivo. Si no existe,
   usa un valor por defecto y lo guarda. */
double cargarPrecioCombustible(void) {
    FILE *f = fopen(ARCHIVO_COMBUSTIBLE, "r");
    double precio;
    if (f == NULL) {
        precio = 250.0; /* valor por defecto, ej: pesos por litro/galon */
        guardarPrecioCombustible(precio);
        return precio;
    }
    if (fscanf(f, "%lf", &precio) != 1) {
        precio = 250.0;
    }
    fclose(f);
    return precio;
}

void guardarPrecioCombustible(double precio) {
    FILE *f = fopen(ARCHIVO_COMBUSTIBLE, "w");
    if (f == NULL) {
        printf("Error: no se pudo guardar el precio del combustible.\n");
        return;
    }
    fprintf(f, "%.4f\n", precio);
    fclose(f);
}

/* =======================================================================
   UTILIDADES DE ENTRADA
   ======================================================================= */

void limpiarBufer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

double leerDouble(const char *mensaje) {
    double valor;
    printf("%s", mensaje);
    while (scanf("%lf", &valor) != 1) {
        printf("Entrada invalida. Intente de nuevo: ");
        limpiarBufer();
    }
    limpiarBufer();
    return valor;
}

int leerEntero(const char *mensaje) {
    int valor;
    printf("%s", mensaje);
    while (scanf("%d", &valor) != 1) {
        printf("Entrada invalida. Intente de nuevo: ");
        limpiarBufer();
    }
    limpiarBufer();
    return valor;
}

void leerTexto(const char *mensaje, char *destino, int tam) {
    printf("%s", mensaje);
    fgets(destino, tam, stdin);
    /* Quitar el salto de linea final que deja fgets */
    size_t len = strlen(destino);
    if (len > 0 && destino[len - 1] == '\n') destino[len - 1] = '\0';
}

/* =======================================================================
   BUSQUEDA / IDs
   ======================================================================= */

int buscarIndicePorId(Vehiculo lista[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (lista[i].id == id) return i;
    }
    return -1;
}

int siguienteId(Vehiculo lista[], int n) {
    int maxId = 0;
    for (int i = 0; i < n; i++) {
        if (lista[i].id > maxId) maxId = lista[i].id;
    }
    return maxId + 1;
}

/* =======================================================================
   CALCULOS ECONOMICOS
   -----------------------------------------------------------------------
   Todo se expresa "por km" para poder combinarse facilmente:

   amortizacionPorKm   = costo del vehiculo / (vida util en años * km/año)
   mantenimientoPorKm  = mantenimiento anual / km por año
   seguroPorKm         = seguro anual / km por año
   neumaticosPorKm     = costo del juego de neumaticos / vida util en km
   ======================================================================= */

double amortizacionPorKm(Vehiculo v) {
    double kmTotalesVidaUtil = v.vidaUtilAños * v.kmAnualPromedio;
    if (kmTotalesVidaUtil <= 0) return 0;
    return v.costo / kmTotalesVidaUtil;
}

double mantenimientoPorKm(Vehiculo v) {
    if (v.kmAnualPromedio <= 0) return 0;
    return v.mantenimientoAnual / v.kmAnualPromedio;
}

double seguroPorKm(Vehiculo v) {
    if (v.kmAnualPromedio <= 0) return 0;
    return v.seguroAnual / v.kmAnualPromedio;
}

double neumaticosPorKm(Vehiculo v) {
    if (v.vidaUtilNeumaticosKm <= 0) return 0;
    return v.costoJuegoNeumaticos / v.vidaUtilNeumaticosKm;
}

/* Consumo promedio simple entre ciudad y autopista, en km/litro.
   Se usa como referencia general (no para un viaje especifico). */
double consumoPromedio(Vehiculo v) {
    if (v.consumoCiudad <= 0 || v.consumoAutopista <= 0) return 0;
    return (v.consumoCiudad + v.consumoAutopista) / 2.0;
}

/* Costo total por km en ciudad: combustible + costos fijos por km */
double costoPorKmCiudad(Vehiculo v, double precioCombustible) {
    double combustible = (v.consumoCiudad > 0)
        ? precioCombustible / v.consumoCiudad
        : 0;
    return combustible + amortizacionPorKm(v) + mantenimientoPorKm(v)
           + seguroPorKm(v) + neumaticosPorKm(v);
}

/* Costo total por km en autopista: combustible + costos fijos por km */
double costoPorKmAutopista(Vehiculo v, double precioCombustible) {
    double combustible = (v.consumoAutopista > 0)
        ? precioCombustible / v.consumoAutopista
        : 0;
    return combustible + amortizacionPorKm(v) + mantenimientoPorKm(v)
           + seguroPorKm(v) + neumaticosPorKm(v);
}

/* =======================================================================
   OPCION 1: CREAR VEHICULO
   ======================================================================= */
void crearVehiculo(void) {
    Vehiculo lista[MAX_VEHICULOS];
    int n = cargarVehiculos(lista);

    if (n >= MAX_VEHICULOS) {
        printf("No se pueden registrar mas vehiculos (limite %d).\n", MAX_VEHICULOS);
        return;
    }

    Vehiculo v;
    v.id = siguienteId(lista, n);

    printf("\n--- Nuevo vehiculo (ID asignado: %d) ---\n", v.id);
    leerTexto("Nombre / modelo: ", v.nombre, MAX_NOMBRE);
    v.costo                = leerDouble("Costo de compra: ");
    v.vidaUtilAños         = leerEntero("Vida util (años): ");
    v.kmAnualPromedio       = leerDouble("Km recorridos por año (promedio): ");
    v.mantenimientoAnual    = leerDouble("Gasto de mantenimiento por año: ");
    v.seguroAnual           = leerDouble("Costo del seguro por año: ");
    v.costoJuegoNeumaticos  = leerDouble("Costo de un juego de neumaticos: ");
    v.vidaUtilNeumaticosKm  = leerDouble("Vida util de los neumaticos (km): ");
    v.consumoCiudad         = leerDouble("Consumo en ciudad (km por litro): ");
    v.consumoAutopista      = leerDouble("Consumo en autopista (km por litro): ");

    lista[n] = v;
    n++;
    guardarVehiculos(lista, n);

    printf("Vehiculo guardado correctamente con ID %d.\n", v.id);
}

/* =======================================================================
   OPCION 2: BORRAR VEHICULO
   ======================================================================= */
void borrarVehiculo(void) {
    Vehiculo lista[MAX_VEHICULOS];
    int n = cargarVehiculos(lista);

    if (n == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    listarVehiculos();
    int id = leerEntero("\nID del vehiculo a borrar: ");
    int idx = buscarIndicePorId(lista, n, id);

    if (idx == -1) {
        printf("No existe un vehiculo con ese ID.\n");
        return;
    }

    /* Desplazar los elementos siguientes una posicion hacia atras */
    for (int i = idx; i < n - 1; i++) {
        lista[i] = lista[i + 1];
    }
    n--;

    guardarVehiculos(lista, n);
    printf("Vehiculo eliminado correctamente.\n");
}

/* =======================================================================
   OPCION 3: MODIFICAR VEHICULO
   ======================================================================= */
void modificarVehiculo(void) {
    Vehiculo lista[MAX_VEHICULOS];
    int n = cargarVehiculos(lista);

    if (n == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    listarVehiculos();
    int id = leerEntero("\nID del vehiculo a modificar: ");
    int idx = buscarIndicePorId(lista, n, id);

    if (idx == -1) {
        printf("No existe un vehiculo con ese ID.\n");
        return;
    }

    Vehiculo *v = &lista[idx];
    int campo;

    do {
        printf("\n--- Modificando: %s (ID %d) ---\n", v->nombre, v->id);
        printf(" 1. Nombre (actual: %s)\n", v->nombre);
        printf(" 2. Costo de compra (actual: %.2f)\n", v->costo);
        printf(" 3. Vida util en años (actual: %d)\n", v->vidaUtilAños);
        printf(" 4. Km por año (actual: %.2f)\n", v->kmAnualPromedio);
        printf(" 5. Mantenimiento anual (actual: %.2f)\n", v->mantenimientoAnual);
        printf(" 6. Seguro anual (actual: %.2f)\n", v->seguroAnual);
        printf(" 7. Costo juego de neumaticos (actual: %.2f)\n", v->costoJuegoNeumaticos);
        printf(" 8. Vida util neumaticos en km (actual: %.2f)\n", v->vidaUtilNeumaticosKm);
        printf(" 9. Consumo ciudad km/l (actual: %.2f)\n", v->consumoCiudad);
        printf("10. Consumo autopista km/l (actual: %.2f)\n", v->consumoAutopista);
        printf(" 0. Terminar y guardar\n");

        campo = leerEntero("Campo a modificar: ");

        switch (campo) {
            case 1: leerTexto("Nuevo nombre: ", v->nombre, MAX_NOMBRE); break;
            case 2: v->costo = leerDouble("Nuevo costo: "); break;
            case 3: v->vidaUtilAños = leerEntero("Nueva vida util (años): "); break;
            case 4: v->kmAnualPromedio = leerDouble("Nuevo km/año: "); break;
            case 5: v->mantenimientoAnual = leerDouble("Nuevo mantenimiento anual: "); break;
            case 6: v->seguroAnual = leerDouble("Nuevo seguro anual: "); break;
            case 7: v->costoJuegoNeumaticos = leerDouble("Nuevo costo juego neumaticos: "); break;
            case 8: v->vidaUtilNeumaticosKm = leerDouble("Nueva vida util neumaticos (km): "); break;
            case 9: v->consumoCiudad = leerDouble("Nuevo consumo ciudad (km/l): "); break;
            case 10: v->consumoAutopista = leerDouble("Nuevo consumo autopista (km/l): "); break;
            case 0: break;
            default: printf("Opcion invalida.\n");
        }
    } while (campo != 0);

    guardarVehiculos(lista, n);
    printf("Vehiculo actualizado correctamente.\n");
}

/* =======================================================================
   OPCION 4: LISTAR VEHICULOS
   ======================================================================= */
void listarVehiculos(void) {
    Vehiculo lista[MAX_VEHICULOS];
    int n = cargarVehiculos(lista);

    if (n == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("\n%-4s %-25s %-12s %-10s\n", "ID", "Nombre", "Costo", "Km/año");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-4d %-25s %-12.2f %-10.2f\n",
               lista[i].id, lista[i].nombre, lista[i].costo, lista[i].kmAnualPromedio);
    }
}

/* =======================================================================
   OPCION 5: VER COSTOS POR KM (CIUDAD / AUTOPISTA) DE UN VEHICULO
   ======================================================================= */
void verCostosPorKm(void) {
    Vehiculo lista[MAX_VEHICULOS];
    int n = cargarVehiculos(lista);
    double precioCombustible = cargarPrecioCombustible();

    if (n == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    listarVehiculos();
    int id = leerEntero("\nID del vehiculo a analizar: ");
    int idx = buscarIndicePorId(lista, n, id);

    if (idx == -1) {
        printf("No existe un vehiculo con ese ID.\n");
        return;
    }

    Vehiculo v = lista[idx];

    double amort = amortizacionPorKm(v);
    double mant  = mantenimientoPorKm(v);
    double seg   = seguroPorKm(v);
    double neum  = neumaticosPorKm(v);
    double cCiudad = costoPorKmCiudad(v, precioCombustible);
    double cAutopista = costoPorKmAutopista(v, precioCombustible);

    printf("\n=== Costo real por km: %s ===\n", v.nombre);
    printf("Precio del combustible actual: %.2f\n", precioCombustible);
    printf("Consumo promedio: %.2f km/litro\n", consumoPromedio(v));
    printf("-----------------------------------------------\n");
    printf("Amortizacion del vehiculo : %.4f por km\n", amort);
    printf("Mantenimiento             : %.4f por km\n", mant);
    printf("Seguro                    : %.4f por km\n", seg);
    printf("Neumaticos                : %.4f por km\n", neum);
    printf("-----------------------------------------------\n");
    printf("COSTO REAL EN CIUDAD      : %.4f por km\n", cCiudad);
    printf("COSTO REAL EN AUTOPISTA   : %.4f por km\n", cAutopista);
}

/* =======================================================================
   OPCION 6: CALCULAR COSTO DE UN VIAJE
   ======================================================================= */
void calcularViaje(void) {
    Vehiculo lista[MAX_VEHICULOS];
    int n = cargarVehiculos(lista);
    double precioCombustible = cargarPrecioCombustible();

    if (n == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    listarVehiculos();
    int id = leerEntero("\nID del vehiculo a usar: ");
    int idx = buscarIndicePorId(lista, n, id);

    if (idx == -1) {
        printf("No existe un vehiculo con ese ID.\n");
        return;
    }

    Vehiculo v = lista[idx];

    double kmCiudad    = leerDouble("Km en ciudad: ");
    double kmAutopista = leerDouble("Km en autopista: ");
    double kmTotal = kmCiudad + kmAutopista;

    /* Combustible: separado por tipo de via, cada uno con su consumo */
    double combustibleCiudad = (v.consumoCiudad > 0)
        ? (kmCiudad / v.consumoCiudad) * precioCombustible : 0;
    double combustibleAutopista = (v.consumoAutopista > 0)
        ? (kmAutopista / v.consumoAutopista) * precioCombustible : 0;
    double combustibleTotal = combustibleCiudad + combustibleAutopista;

    /* Costos fijos (amortizacion + mantenimiento + seguro + neumaticos)
       se aplican por km recorrido, sin importar el tipo de via */
    double costoFijoPorKm = amortizacionPorKm(v) + mantenimientoPorKm(v)
                             + seguroPorKm(v) + neumaticosPorKm(v);
    double costoFijoTotal = costoFijoPorKm * kmTotal;

    double costoTotal = combustibleTotal + costoFijoTotal;

    printf("\n=== Costo del viaje: %s ===\n", v.nombre);
    printf("Km en ciudad: %.2f | Km en autopista: %.2f | Total: %.2f km\n",
           kmCiudad, kmAutopista, kmTotal);
    printf("-----------------------------------------------\n");
    printf("Combustible en ciudad     : %.2f\n", combustibleCiudad);
    printf("Combustible en autopista  : %.2f\n", combustibleAutopista);
    printf("Combustible total         : %.2f\n", combustibleTotal);
    printf("Costos fijos (amort./mant./seguro/neum.): %.2f\n", costoFijoTotal);
    printf("-----------------------------------------------\n");
    printf("COSTO TOTAL DEL VIAJE     : %.2f\n", costoTotal);
    if (kmTotal > 0) {
        printf("Costo promedio por km     : %.4f\n", costoTotal / kmTotal);
    }
}

/* =======================================================================
   OPCION 7: MODIFICAR PRECIO DEL COMBUSTIBLE
   ======================================================================= */
void modificarPrecioCombustible(void) {
    double actual = cargarPrecioCombustible();
    printf("Precio actual del combustible: %.4f\n", actual);
    double nuevo = leerDouble("Nuevo precio del combustible: ");
    guardarPrecioCombustible(nuevo);
    printf("Precio del combustible actualizado correctamente.\n");
}
