#include "bt_sin_poda.hpp"

namespace {

    void recorrer(const PolicyParams& p, const std::string& alfabeto, std::string& prefijo,
                  ResultadoFuerzaBrutaBT& resultado, unsigned long long tope) {
        if (resultado.nodosVisitados >= static_cast<long long>(tope)) {
            resultado.completo = false;
            return;
        }
        ++resultado.nodosVisitados;

        int k = static_cast<int>(prefijo.size());
        if (k == p.n) {
            if (cumplePolitica(prefijo, p)) ++resultado.solucionesEncontradas;
            return;
        }

        for (char c : alfabeto) {
            prefijo.push_back(c);
            recorrer(p, alfabeto, prefijo, resultado, tope);
            prefijo.pop_back();
            if (!resultado.completo) return;
        }
    }

}

ResultadoFuerzaBrutaBT ejecutarSinPoda(const PolicyParams& p, const std::string& alfabeto,
                                        unsigned long long tope) {
    ResultadoFuerzaBrutaBT resultado;
    resultado.topeUsado = tope;
    std::string prefijo;
    prefijo.reserve(p.n);
    recorrer(p, alfabeto, prefijo, resultado, tope);
    return resultado;
}

long double nodosTeoricosSinPoda(int n, int tamAlfabeto) {
    long double total = 0.0L, potencia = 1.0L;
    for (int k = 0; k <= n; ++k) {
        total += potencia;
        potencia *= tamAlfabeto;
    }
    return total;
}