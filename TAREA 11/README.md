# Mosler Risk Manager

Sistema en C para identificar, evaluar y gestionar la gravedad de riesgos
de una empresa utilizando el Método Mosler de gestión de riesgos.

## Estado del proyecto

Fase 0 completada: estructura base del proyecto y verificación del entorno
de compilación. Aún no hay lógica de negocio implementada.

## Estructura

```
MoslerRisk/
├── include/     Cabeceras (.h) — declaraciones de cada módulo
├── src/         Implementación (.c) de cada módulo
├── data/        Archivos CSV de riesgos (uno por empresa)
├── Makefile     Compilación del proyecto completo
└── .vscode/     Configuración de VS Code (build con Ctrl+Shift+B)
```

## Cómo compilar

Con `make` instalado (viene por defecto en la mayoría de distros Linux
y en el subsistema de WSL en Windows):

```
make        # compila el proyecto a ./mosler_risk
make run    # compila y ejecuta
make clean  # borra binarios y objetos generados
```

En VS Code: `Ctrl+Shift+B` ejecuta la tarea de compilación por defecto.

## Módulos (se completan progresivamente por fases)

| Módulo | Responsabilidad |
|---|---|
| `riesgo` | Crear, modificar, eliminar, buscar y mostrar un riesgo |
| `mosler` | Cálculos puros del Método Mosler (I, D, C, Pb, ER, clasificación) |
| `archivo` | Crear/verificar/cargar/guardar archivos CSV de riesgos |
| `memoria` | Gestión del arreglo dinámico de riesgos (malloc/realloc/free) |
| `menu` | Menú principal y navegación |
| `utilidades` | Validación de entrada y funciones generales |
