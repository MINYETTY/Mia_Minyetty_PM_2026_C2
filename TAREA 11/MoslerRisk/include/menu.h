#ifndef MENU_H
#define MENU_H

#include "riesgo.h"

/* Muestra el menu principal en un bucle hasta que el usuario elige salir.
 * Al salir, si hay un archivo abierto, pregunta si se desea guardar. */
void ejecutarMenu(Sistema *sistema);

#endif
