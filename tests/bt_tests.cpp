#include <cassert>
#include <iostream>
#include "../src/bt_policy.hpp"
#include "../src/bt_backtracking.hpp"
#include "../src/bt_sin_poda.hpp"

int main() {
    const std::string alfabetoReal = construirAlfabetoBT();

    PolicyParams imposible{4, 2, 2, 2, 2, true, "imposible"};
    ResultadoBT r1 = ejecutarBacktracking(imposible, alfabetoReal);
    assert(r1.solucionesEncontradas == 0);
    std::cout << "OK: politica imposible produce 0 soluciones (nodos visitados="
              << r1.nodosVisitados << ").\n";

    std::string alfabetoChico = "abAB01!@";
    PolicyParams pChico{5, 1, 1, 1, 1, true, "chico"};

    ResultadoBT conPoda = ejecutarBacktracking(pChico, alfabetoChico);
    ResultadoFuerzaBrutaBT sinPoda = ejecutarSinPoda(pChico, alfabetoChico, 100000000ULL);

    assert(sinPoda.completo);
    assert(conPoda.solucionesEncontradas == sinPoda.solucionesEncontradas);
    std::cout << "OK: con poda (" << conPoda.solucionesEncontradas << " soluciones, "
              << conPoda.nodosVisitados << " nodos) coincide con sin poda ("
              << sinPoda.solucionesEncontradas << " soluciones, "
              << sinPoda.nodosVisitados << " nodos).\n";
    std::cout << "    Reduccion de espacio de busqueda en este caso de prueba: "
              << 100.0 * (1.0 - (double)conPoda.nodosVisitados / (double)sinPoda.nodosVisitados)
              << " %\n";

    for (const auto& sol : conPoda.ejemplos) assert(cumplePolitica(sol, pChico));
    std::cout << "OK: todos los ejemplos generados cumplen la politica.\n";

    PolicyParams ref{6, 2, 1, 1, 1, true, "ref"};
    ResultadoBT rRef = ejecutarBacktracking(ref, alfabetoReal);
    std::cout << "Instancia de referencia oficial: " << rRef.solucionesEncontradas
              << " soluciones, " << rRef.nodosVisitados << " nodos visitados con poda.\n";

    std::cout << "\nTodas las pruebas pasaron.\n";
    return 0;
}