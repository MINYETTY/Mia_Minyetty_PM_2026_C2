#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DISCOS 10
#define MAX_MOVIMIENTOS 1100
#define ANCHO_VENTANA 900
#define ALTO_VENTANA 500
#define RETRASO_MS 500        // pausa antes de iniciar el siguiente movimiento
#define DURACION_ANIM_MS 400  // duracion de la animacion de cada movimiento

/* ---------- Estructuras de datos ---------- */

typedef struct {
    int disco;
    char origen;
    char destino;
} Movimiento;

typedef struct {
    int discos[MAX_DISCOS]; // tamanos apilados, indice 0 = base
    int cantidad;
} Poste;

Movimiento listaMovimientos[MAX_MOVIMIENTOS];
int totalMovimientos = 0;

int numDiscos;
Poste postes[3]; // 0 = A, 1 = B, 2 = C

SDL_Color coloresDiscos[MAX_DISCOS] = {
    {231, 76, 60, 255}, {230, 126, 34, 255}, {241, 196, 15, 255},
    {46, 204, 113, 255}, {26, 188, 156, 255}, {52, 152, 219, 255},
    {155, 89, 182, 255}, {149, 165, 166, 255}, {211, 84, 0, 255},
    {192, 57, 43, 255}
};

/* ---------- Paso 1: el "planificador" (recursividad) ----------
   Genera la secuencia COMPLETA de movimientos antes de dibujar
   un solo fotograma. El game loop luego consume esta lista. */
void generarMovimientos(int n, char origen, char aux, char destino) {
    if (n == 0) return;

    generarMovimientos(n - 1, origen, destino, aux);

    listaMovimientos[totalMovimientos].disco = n;
    listaMovimientos[totalMovimientos].origen = origen;
    listaMovimientos[totalMovimientos].destino = destino;
    totalMovimientos++;

    generarMovimientos(n - 1, aux, origen, destino);
}

int indicePoste(char letra) { return letra - 'A'; }

void inicializarPostes(void) {
    for (int p = 0; p < 3; p++) postes[p].cantidad = 0;
    for (int d = numDiscos; d >= 1; d--) {
        postes[0].discos[postes[0].cantidad++] = d;
    }
}

int quitarDiscoSuperior(int poste) {
    postes[poste].cantidad--;
    return postes[poste].discos[postes[poste].cantidad];
}

void ponerDiscoEnPoste(int poste, int disco) {
    postes[poste].discos[postes[poste].cantidad++] = disco;
}

/* ---------- Geometria / dibujo ---------- */

int xPoste(int poste) {
    int ancho = ANCHO_VENTANA / 3;
    return ancho * poste + ancho / 2;
}

int yBase(void) { return ALTO_VENTANA - 60; }

int anchoDisco(int disco) { return 30 + disco * 18; }
int altoDisco(void) { return 22; }

void dibujarVarillas(SDL_Renderer *ren) {
    SDL_SetRenderDrawColor(ren, 120, 90, 60, 255);
    for (int p = 0; p < 3; p++) {
        SDL_Rect base = { xPoste(p) - 110, yBase() + 10, 220, 12 };
        SDL_Rect varilla = { xPoste(p) - 6, yBase() - 220, 12, 220 };
        SDL_RenderFillRect(ren, &varilla);
        SDL_RenderFillRect(ren, &base);
    }
}

void dibujarDisco(SDL_Renderer *ren, int disco, int cx, int cy) {
    int w = anchoDisco(disco);
    int h = altoDisco();
    SDL_Rect r = { cx - w / 2, cy - h / 2, w, h };
    SDL_Color c = coloresDiscos[(disco - 1) % MAX_DISCOS];
    SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, 255);
    SDL_RenderFillRect(ren, &r);
    SDL_SetRenderDrawColor(ren, 20, 20, 20, 255);
    SDL_RenderDrawRect(ren, &r);
}

/* Dibuja todos los discos "en reposo" en sus postes, salvo el que
   esta actualmente animandose (ese se dibuja aparte, en el aire). */
void dibujarPostesEstaticos(SDL_Renderer *ren, int discoEnAnimacion) {
    for (int p = 0; p < 3; p++) {
        for (int i = 0; i < postes[p].cantidad; i++) {
            int disco = postes[p].discos[i];
            if (disco == discoEnAnimacion) continue;
            int cy = yBase() - (i + 1) * (altoDisco() + 4);
            dibujarDisco(ren, disco, xPoste(p), cy);
        }
    }
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    printf("=== Torres de Hanoi (version SDL) ===\n");
    printf("Ingrese el numero de discos (1-%d): ", MAX_DISCOS);
    if (scanf("%d", &numDiscos) != 1 || numDiscos < 1 || numDiscos > MAX_DISCOS) {
        printf("Numero de discos invalido.\n");
        return EXIT_FAILURE;
    }

    /* --- Igual que en la version de consola: se calcula TODO primero
       y se registra en el archivo de texto --- */
    FILE *archivo = fopen("movimientos.txt", "w");
    if (archivo == NULL) {
        printf("Error al crear movimientos.txt\n");
        return EXIT_FAILURE;
    }
    fprintf(archivo, "Registro de movimientos - Torres de Hanoi (%d discos)\n", numDiscos);
    fprintf(archivo, "--------------------------------------------------\n");

    generarMovimientos(numDiscos, 'A', 'B', 'C');

    int contador = 0;
    for (int i = 0; i < totalMovimientos; i++) {
        contador++;
        fprintf(archivo, "Movimiento %d: Mover disco %d de %c a %c\n",
                contador, listaMovimientos[i].disco,
                listaMovimientos[i].origen, listaMovimientos[i].destino);
    }
    fclose(archivo);
    printf("Se calcularon %d movimientos (registrados en movimientos.txt)\n", totalMovimientos);

    inicializarPostes();

    /* --- Inicializacion de SDL --- */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error al iniciar SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *ventana = SDL_CreateWindow(
        "Torres de Hanoi - SDL",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        ANCHO_VENTANA, ALTO_VENTANA, SDL_WINDOW_SHOWN);
    if (!ventana) {
        printf("Error al crear ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Error al crear renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    /* --- Estado de la animacion --- */
    int indiceMovimientoActual = 0;
    int animando = 0;
    Uint32 tiempoInicioAnim = 0;
    Uint32 tiempoUltimoFin = 0;

    int discoActivo = 0;
    int origenPeg = 0, destinoPeg = 0;
    int xOrigen = 0, xDestino = 0;
    int yReposoOrigen = 0, yReposoDestino = 0;
    const int yTope = 60; // altura maxima del "vuelo" del disco

    int ejecutando = 1;
    SDL_Event evento;

    /* ---------- Game loop ---------- */
    while (ejecutando) {

        /* 1. Manejo de eventos */
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) ejecutando = 0;
        }

        Uint32 ahora = SDL_GetTicks();

        /* 2. Logica: iniciar el siguiente movimiento si corresponde */
        if (!animando && indiceMovimientoActual < totalMovimientos &&
            ahora - tiempoUltimoFin >= RETRASO_MS) {

            Movimiento m = listaMovimientos[indiceMovimientoActual];
            origenPeg = indicePoste(m.origen);
            destinoPeg = indicePoste(m.destino);

            discoActivo = quitarDiscoSuperior(origenPeg);

            xOrigen = xPoste(origenPeg);
            xDestino = xPoste(destinoPeg);
            yReposoOrigen = yBase() - (postes[origenPeg].cantidad + 1) * (altoDisco() + 4);
            yReposoDestino = yBase() - (postes[destinoPeg].cantidad + 1) * (altoDisco() + 4);

            animando = 1;
            tiempoInicioAnim = ahora;
        }

        /* 3. Actualizar posicion del disco si hay animacion en curso */
        int cxAnim = 0, cyAnim = 0;
        if (animando) {
            float t = (float)(ahora - tiempoInicioAnim) / DURACION_ANIM_MS;
            if (t >= 1.0f) {
                t = 1.0f;
                ponerDiscoEnPoste(destinoPeg, discoActivo);
                animando = 0;
                indiceMovimientoActual++;
                tiempoUltimoFin = ahora;
            }

            /* interpolacion horizontal lineal */
            cxAnim = xOrigen + (int)((xDestino - xOrigen) * t);

            /* interpolacion vertical en arco: sube y luego baja */
            if (t < 0.5f) {
                float progreso = t / 0.5f;
                cyAnim = yReposoOrigen - (int)((yReposoOrigen - yTope) * progreso);
            } else {
                float progreso = (t - 0.5f) / 0.5f;
                cyAnim = yTope + (int)((yReposoDestino - yTope) * progreso);
            }
        }

        /* 4. Renderizado */
        SDL_SetRenderDrawColor(renderer, 25, 25, 35, 255);
        SDL_RenderClear(renderer);

        dibujarVarillas(renderer);
        dibujarPostesEstaticos(renderer, animando ? discoActivo : 0);

        if (animando) {
            dibujarDisco(renderer, discoActivo, cxAnim, cyAnim);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); /* aprox. 60 FPS */
    }

    /* ---------- Liberacion de recursos ---------- */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    SDL_Quit();

    return EXIT_SUCCESS;
}
