#include <cassert>
#include <iostream>

#include "../src/bt_policy.hpp"
#include "../src/bt_backtracking.hpp"
#include "../src/bt_sin_poda.hpp"

int main() {

    const std::string alfabetoReal = construirAlfabetoBT();

    // TEST 1: Política imposible
    PolicyParams imposible{4, 2, 2, 2, 2, true, "imposible"};

    ResultadoBT r1 = ejecutarBacktracking(imposible, alfabetoReal);

    assert(r1.completo);
    assert(r1.solucionesEncontradas == 0);

    std::cout
        << "OK: politica imposible produce 0 soluciones.\n";

    // Test 2: Comparación con poda vs. sin poda
    std::string alfabetoChico = "abAB01!@";

    PolicyParams pChico{5, 1, 1, 1, 1, true, "chico"};

    ResultadoBT conPoda =
        ejecutarBacktracking(pChico, alfabetoChico, 20, 100000000ULL);

    ResultadoFuerzaBrutaBT sinPoda =
        ejecutarSinPoda(pChico, alfabetoChico, 100000000ULL);

    assert(conPoda.completo);
    assert(sinPoda.completo);

    assert(conPoda.solucionesEncontradas ==
           sinPoda.solucionesEncontradas);

    assert(conPoda.nodosVisitados < sinPoda.nodosVisitados);

    std::cout
        << "OK: con poda y sin poda encuentran la misma cantidad "
           "de soluciones.\n";

    std::cout
        << "    Soluciones: "
        << conPoda.solucionesEncontradas << "\n";

    std::cout
        << "    Nodos con poda: "
        << conPoda.nodosVisitados << "\n";

    std::cout
        << "    Nodos sin poda: "
        << sinPoda.nodosVisitados << "\n";

    double reduccion =
        100.0 *
        (1.0 -
         static_cast<double>(conPoda.nodosVisitados) /
         static_cast<double>(sinPoda.nodosVisitados));

    std::cout
        << "    Reduccion del espacio de busqueda: "
        << reduccion << " %\n";

    // Test 3: Las soluciones generadas cumplen la política
    for (const auto& sol : conPoda.ejemplos) {
        assert(cumplePolitica(sol, pChico));
    }

    std::cout
        << "OK: todos los ejemplos generados cumplen la politica.\n";

    // Test 4: Instancia oficial de referencia
    PolicyParams ref{6, 2, 1, 1, 1, true, "ref"};

    ResultadoBT rRef =
        ejecutarBacktracking(ref, alfabetoReal, 20, 50000000LL);

    std::cout
        << "Referencia oficial:\n"
        << "    Soluciones encontradas: "
        << rRef.solucionesEncontradas << "\n"
        << "    Nodos visitados: "
        << rRef.nodosVisitados << "\n"
        << "    Completo: "
        << (rRef.completo ? "si" : "no") << "\n";

    // Esta ejecución puede ser parcial debido al tope, puede que el número de soluciones no sea definitivo.
    if (!rRef.completo) {
        std::cout
            << "AVISO: la instancia oficial no termino dentro "
               "del tope establecido.\n";
    }

    // Test 5: Instancia propia del equipo con n = 6
    PolicyParams propiaN6{6, 2, 2, 3, 1, true, "completa_n6"};

    ResultadoBT rN6 =
        ejecutarBacktracking(propiaN6, alfabetoReal, 20, 50000000LL);

    assert(rN6.completo);
    assert(rN6.solucionesEncontradas == 0);

    std::cout
        << "OK: la politica propia n=6 es imposible y produce "
           "0 soluciones.\n";

    // Test 6: Verificar que el alfabeto tenga 67 caracteres
    assert(alfabetoReal.size() == 67);

    std::cout
        << "OK: el alfabeto BT contiene 67 caracteres.\n";

    // Test 7: Verificar que no existan ejemplos con caracteres
    for (const auto& sol : conPoda.ejemplos) {
        for (size_t i = 1; i < sol.size(); ++i) {
            assert(sol[i] != sol[i - 1]);
        }
    }

    std::cout
        << "OK: los ejemplos no contienen caracteres "
           "identicos consecutivos.\n";


    std::cout
        << "\nTodas las pruebas pasaron.\n";

    return 0;
}