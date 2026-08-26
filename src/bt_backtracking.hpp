#pragma once
#include <string>
#include <vector>
#include "bt_policy.hpp"

struct ResultadoBT {
    long long nodosVisitados = 0;
    long long solucionesEncontradas = 0;
    std::vector<std::string> ejemplos;
    bool completo = true;
};

ResultadoBT ejecutarBacktracking(const PolicyParams& p, const std::string& alfabeto,
                                  int maxEjemplos = 20,
                                  long long tope = 50000000LL);