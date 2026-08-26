#include "bt_backtracking.hpp"

namespace {

void backtrack(const PolicyParams& p, const std::string& alfabeto,
               std::string& prefijo, int lower, int upper, int digit, int symbol,
               ResultadoBT& resultado, int maxEjemplos, long long tope) {
    if (resultado.nodosVisitados >= tope) {
        resultado.completo = false;
        return;
    }
    ++resultado.nodosVisitados;

    int k = static_cast<int>(prefijo.size());
    if (k == p.n) {
        if (cumplePolitica(prefijo, p)) {
            ++resultado.solucionesEncontradas;
            if (static_cast<int>(resultado.ejemplos.size()) < maxEjemplos)
                resultado.ejemplos.push_back(prefijo);
        }
        return;
    }

    int restantesTrasEste = p.n - (k + 1);

    for (char c : alfabeto) {
        if (p.prohibirConsecutivosRepetidos && !prefijo.empty() && prefijo.back() == c)
            continue;

        int nl = lower, nu = upper, nd = digit, ns = symbol;
        switch (categoriaDe(c)) {
            case Categoria::MINUSCULA: ++nl; break;
            case Categoria::MAYUSCULA: ++nu; break;
            case Categoria::DIGITO: ++nd; break;
            case Categoria::SIMBOLO: ++ns; break;
        }

        int faltanLower = std::max(0, p.minLower - nl);
        int faltanUpper = std::max(0, p.minUpper - nu);
        int faltanDigit = std::max(0, p.minDigit - nd);
        int faltanSymbol = std::max(0, p.minSymbol - ns);

        if (!esFactible(faltanLower, faltanUpper, faltanDigit, faltanSymbol, restantesTrasEste))
            continue;

        prefijo.push_back(c);
        backtrack(p, alfabeto, prefijo, nl, nu, nd, ns, resultado, maxEjemplos, tope);
        prefijo.pop_back();

        if (!resultado.completo) return;
    }
}

}

ResultadoBT ejecutarBacktracking(const PolicyParams& p, const std::string& alfabeto,
                                  int maxEjemplos, long long tope) {
    ResultadoBT resultado;
    std::string prefijo;
    prefijo.reserve(p.n);
    backtrack(p, alfabeto, prefijo, 0, 0, 0, 0, resultado, maxEjemplos, tope);
    return resultado;
}