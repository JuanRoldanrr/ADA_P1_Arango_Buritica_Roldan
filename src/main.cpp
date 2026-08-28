#include <iostream>
#include <string>

#include "bt_runner.hpp"
#include "fb_runner.hpp"

namespace {

void imprimirUso(const char* nombrePrograma) {
    std::cout << "Uso: " << nombrePrograma << " <modulo>\n"
              << "  bt   - ejecuta el Modulo BT (Backtracking)\n"
              << "  fb   - ejecuta el Modulo FB (Fuerza Bruta)\n"
              << "Si no se indica modulo, se ejecuta 'bt' por defecto.\n";
}

} // namespace

int main(int argc, char** argv) {
    std::string modulo = (argc >= 2) ? argv[1] : "bt";

    if (modulo == "bt") {
        ejecutarModuloBT("results");

    } else if (modulo == "fb") {
        ejecutarModulo();

    } else if (modulo == "-h" || modulo == "--help") {
        imprimirUso(argv[0]);

    } else {
        std::cerr << "Modulo desconocido: " << modulo << "\n\n";
        imprimirUso(argv[0]);
        return 1;
    }

    return 0;
}