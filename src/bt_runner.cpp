#include "bt_runner.hpp"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include "bt_policy.hpp"
#include "bt_backtracking.hpp"
#include "bt_sin_poda.hpp"

namespace {

struct Instancia {
    std::string etiqueta;
    std::string tipo;
    PolicyParams politica;
};

// Semilla del equipo: 2123.

std::vector<Instancia> construirInstancias() {
    return {

        {"Prueba n=3", "verificacion", {3, 1, 1, 1, 0, true, "verif_n3"}},
        {"Prueba n=4", "verificacion", {4, 1, 1, 1, 1, true, "verif_n4"}},

        {"Referencia (validacion)", "oficial", {6, 2, 1, 1, 1, true, "ref"}},
        {"(i) Completa n=8", "oficial", {8, 2, 2, 3, 1, true, "completa_n8"}},
        {"(ii) Completa n=6", "oficial", {6, 2, 2, 3, 1, true, "completa_n6"}},
        {"(iii) Completa n=10", "oficial", {10, 2, 2, 3, 1, true, "completa_n10"}},
        {"(iv) Relajada n=8", "oficial", {8, 1, 0, 0, 0, true, "relajada_n8"}},
        {"(v) Sin restricciones n=6", "oficial", {6, 0, 0, 0, 0, true, "sinrestr_n6"}},
    };
}

std::string fmt(double v) {
    std::ostringstream os;
    os << std::fixed << std::setprecision(2) << v;
    return os.str();
}

}

void ejecutarModuloBT(const std::string& carpetaResultados) {
    const std::string alfabeto = construirAlfabetoBT();
    const auto instancias = construirInstancias();

    std::ofstream csv(carpetaResultados + "/bt_resultados.csv");
    csv << "instancia,tipo,n,minLower,minUpper,minDigit,minSymbol,"
           "nodos_con_poda,con_poda_completo,ms_con_poda,"
           "nodos_sin_poda,sin_poda_completo,ms_sin_poda,"
           "nodos_teoricos_sin_poda,soluciones_con_poda,soluciones_sin_poda,"
           "soluciones_coinciden,reduccion_real_pct\n";

    std::cout << "Modulo BT: comparacion con poda vs sin poda\n";

    for (const auto& inst : instancias) {
        const auto& p = inst.politica;
        bool esVerificacion = inst.tipo == "verificacion";
        long long topeConPoda = esVerificacion ? 1000000000LL : 50000000LL;
        unsigned long long topeSinPoda = esVerificacion ? 1000000000ULL : 20000000ULL;

        auto t0 = std::chrono::steady_clock::now();
        ResultadoBT conPoda = ejecutarBacktracking(p, alfabeto, 20, topeConPoda);
        double msConPoda = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();

        auto t1 = std::chrono::steady_clock::now();
        ResultadoFuerzaBrutaBT sinPoda = ejecutarSinPoda(p, alfabeto, topeSinPoda);
        double msSinPoda = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t1).count();

        long double teorico = nodosTeoricosSinPoda(p.n, static_cast<int>(alfabeto.size()));
        bool comparable = conPoda.completo && sinPoda.completo;
        bool coinciden = comparable && (conPoda.solucionesEncontradas == sinPoda.solucionesEncontradas);
        double reduccion = comparable && sinPoda.nodosVisitados > 0
            ? 100.0 * (1.0 - (double)conPoda.nodosVisitados / (double)sinPoda.nodosVisitados)
            : -1.0;

        std::cout << "\n" << inst.etiqueta << "  (n=" << p.n << ", mins=" << p.minLower << "/"
                  << p.minUpper << "/" << p.minDigit << "/" << p.minSymbol << ")\n";
        std::cout << "  con poda  nodos=" << conPoda.nodosVisitados << (conPoda.completo ? "" : " (parcial)")
                  << "  sol=" << conPoda.solucionesEncontradas << "  " << fmt(msConPoda) << "ms\n";
        std::cout << "  sin poda  nodos=" << sinPoda.nodosVisitados << (sinPoda.completo ? "" : " (parcial)")
                  << "  sol=" << sinPoda.solucionesEncontradas << "  " << fmt(msSinPoda) << "ms\n";
        std::cout << "  teorico   " << (double)teorico << "\n";
        if (comparable)
            std::cout << "  reduccion " << fmt(reduccion) << "%  (soluciones coinciden: " << (coinciden ? "si" : "NO, revisar") << ")\n";
        else
            std::cout << "  reduccion no calculable, alguna de las dos versiones no termino\n";

        csv << p.nombre << ',' << inst.tipo << ',' << p.n << ',' << p.minLower << ',' << p.minUpper << ','
            << p.minDigit << ',' << p.minSymbol << ','
            << conPoda.nodosVisitados << ',' << conPoda.completo << ',' << msConPoda << ','
            << sinPoda.nodosVisitados << ',' << sinPoda.completo << ',' << msSinPoda << ','
            << (double)teorico << ',' << conPoda.solucionesEncontradas << ',' << sinPoda.solucionesEncontradas << ','
            << (comparable ? (coinciden ? "si" : "no") : "n/a") << ','
            << (comparable ? std::to_string(reduccion) : std::string("n/a")) << '\n';
    }

    std::cout << "\nGuardado en " << carpetaResultados << "/bt_resultados.csv\n";
}