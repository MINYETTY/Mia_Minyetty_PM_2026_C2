# Vehicle Cost Manager

Programa de consola desarrollado en C para administrar vehículos y calcular el costo real de propiedad y utilización.

## Funcionalidades

- Crear vehículos.
- Modificar vehículos.
- Eliminar vehículos.
- Mostrar vehículos.
- Guardar y cargar vehículos en CSV.
- Memoria dinámica con `realloc()` y `free()`.
- Depreciación lineal.
- Costo de combustible en ciudad y autopista.
- Seguro por kilómetro.
- Mantenimiento por kilómetro.
- Costo de neumáticos por kilómetro.
- Fondo de imprevistos configurable.
- Costo real por kilómetro.
- Cálculo de viajes mixtos.
- Comparación de vehículos.
- Ordenamiento por costo/km en ciudad.

## Fórmulas principales

### Depreciación anual

`(Costo - Valor residual) / Vida útil`

### Depreciación por km

`Depreciación anual / km anuales`

### Combustible ciudad

`km ciudad / km por litro ciudad`

### Combustible autopista

`km autopista / km por litro autopista`

### Costo de combustible por km

`Precio por litro / km por litro`

### Seguro por km

`Seguro anual / km anuales`

### Mantenimiento por km

`Mantenimiento anual / km anuales`

### Neumáticos por km

`(Precio neumático × cantidad) / vida útil del juego en km`

### Imprevistos

Se calcula como un porcentaje configurable sobre seguro + mantenimiento.

### Costo real por km

Incluye:

- depreciación
- combustible
- seguro
- mantenimiento
- neumáticos
- imprevistos

## Compilación con GCC / MinGW

Desde la carpeta raíz del proyecto:

```bash
gcc src/main.c src/vehiculo.c src/calculos.c src/viaje.c src/archivo.c src/memoria.c src/mantenimiento.c src/utilidades.c -o vehiculos -lm
```

En Windows:

```bash
.\vehiculos.exe
```

## Archivo

Los datos se almacenan en `data/vehiculos.csv` u otros archivos CSV dentro de `data/`.

## Nota

Los valores de ejemplo son solamente datos de prueba. Deben sustituirse por datos apropiados cuando se utilice el programa en un caso real.
