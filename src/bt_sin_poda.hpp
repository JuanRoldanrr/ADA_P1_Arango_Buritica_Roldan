#pragma once
#include <string>
#include "bt_policy.hpp"

struct ResultadoFuerzaBrutaBT {
    long long nodosVisitados = 0;
    long long solucionesEncontradas = 0;
    bool completo = true;
    unsigned long long topeUsado = 0;
};

// Recorre el arbol completo sin usar factibilidad para descartar ramas,
// y filtra la politica solo en las hojas. Con 67 simbolos en el alfabeto
// esto crece muy rapido, asi que recibe un tope de seguridad: si se
// alcanza, completo queda en false y el conteo es parcial.
ResultadoFuerzaBrutaBT ejecutarSinPoda(const PolicyParams& p, const std::string& alfabeto,
                                        unsigned long long tope = 20000000ULL);


long double nodosTeoricosSinPoda(int n, int tamAlfabeto);