#include "../include/mosler.h"

int calcularImportancia(const Riesgo *riesgo) {
    return riesgo->funcion * riesgo->sustitucion;
}

int calcularDanos(const Riesgo *riesgo) {
    return riesgo->profundidad * riesgo->extension;
}

int calcularCaracter(const Riesgo *riesgo) {
    return calcularImportancia(riesgo) + calcularDanos(riesgo);
}

int calcularProbabilidad(const Riesgo *riesgo) {
    return riesgo->agresion * riesgo->vulnerabilidad;
}

int calcularRiesgoEstimado(const Riesgo *riesgo) {
    return calcularCaracter(riesgo) * calcularProbabilidad(riesgo);
}

const char *clasificarRiesgo(int riesgoEstimado) {
    if (riesgoEstimado <= 250) return "Muy bajo";
    if (riesgoEstimado <= 500) return "Bajo";
    if (riesgoEstimado <= 750) return "Medio";
    if (riesgoEstimado <= 1000) return "Alto";
    return "Muy alto";
}

void calcularMosler(const Riesgo *riesgo, int *importancia, int *danos,
                     int *caracter, int *probabilidad, int *riesgoEstimado) {
    *importancia = calcularImportancia(riesgo);
    *danos = calcularDanos(riesgo);
    *caracter = *importancia + *danos;
    *probabilidad = calcularProbabilidad(riesgo);
    *riesgoEstimado = (*caracter) * (*probabilidad);
}
