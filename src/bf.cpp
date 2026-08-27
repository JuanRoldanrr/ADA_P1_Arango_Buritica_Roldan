#include <iostream>
#include <string>
#include <cstdint>
#include <chrono>
#include "picosha2.h"

// Estructura para retornar el resultado múltiple
// (candidato, evaluaciones, estado)
struct ResultadoFB {
    std::string candidato;
    uint64_t evaluaciones;
    std::string estado;
};

// Algoritmo FuerzaBruta
ResultadoFB FuerzaBruta(const std::string& hash_objetivo,
                        const std::string& alfabeto,
                        int longitud) {

    std::string candidato(longitud, ' ');
    uint64_t evaluaciones = 0;

    // Procedimiento auxiliar recursivo Resolver
    auto Resolver = [&](auto& self, int posicion) -> bool {

        if (posicion == longitud) {

            evaluaciones = evaluaciones + 1;

            std::string hash_candidato =
                picosha2::hash256_hex_string(candidato);

            if (hash_candidato == hash_objetivo) {
                return true;
            }

            return false;
        }

        for (char ch : alfabeto) {

            candidato[posicion] = ch;

            if (self(self, posicion + 1)) {
                return true;
            }
        }

        return false;
    };

    bool encontrado = Resolver(Resolver, 0);

    if (encontrado) {
        return {candidato, evaluaciones, "ENCONTRADA"};
    } else {
        return {"NULO", evaluaciones, "NO ENCONTRADA"};
    }
}

// Algoritmo Principal
int main() {

    std::string hash_objetivo;
    std::string opcion_alfabeto;
    std::string alfabeto;
    int longitud;

    std::cout << "Ingrese el Hash Objetivo (SHA-256): ";
    std::cin >> hash_objetivo;

    std::cout << "Seleccione Alfabeto "
                 "(A1 para minusculas, A2 para alfanumerico): ";
    std::cin >> opcion_alfabeto;

    if (opcion_alfabeto == "a1" || opcion_alfabeto == "A1") {

        alfabeto = "abcdefghijklmnopqrstuvwxyz";

    } else if (opcion_alfabeto == "a2" ||
               opcion_alfabeto == "A2") {

        alfabeto = "abcdefghijklmnopqrstuvwxyz0123456789";

    } else {

        std::cout << "Opcion no valida.\n";
        return 0;
    }

    std::cout << "Ingrese la longitud (n): ";
    std::cin >> longitud;

    // Validación de longitudes permitidas según la práctica
    // A1: 3, 4, 5, 6
    // A2: 3, 4, 5
    bool longitud_valida = false;

    if ((opcion_alfabeto == "a1" ||
         opcion_alfabeto == "A1") &&
        (longitud >= 3 && longitud <= 6)) {

        longitud_valida = true;

    } else if ((opcion_alfabeto == "a2" ||
                opcion_alfabeto == "A2") &&
               (longitud >= 3 && longitud <= 5)) {

        longitud_valida = true;
    }

    if (!longitud_valida) {

        std::cout << "Longitud no valida para el alfabeto "
                     "seleccionado.\n";

        return 0;
    }

    // Temporizador
    auto tiempo_inicio =
        std::chrono::high_resolution_clock::now();

    ResultadoFB res =
        FuerzaBruta(hash_objetivo, alfabeto, longitud);

    auto tiempo_fin =
        std::chrono::high_resolution_clock::now();

    double tiempo_ejecucion =
        std::chrono::duration<double, std::milli>(
            tiempo_fin - tiempo_inicio
        ).count();

    // Impresión de resultados
    std::cout << "\n--- RESULTADO ---\n";
    std::cout << "Estado: " << res.estado << "\n";

    if (res.estado == "ENCONTRADA") {
        std::cout << "Candidato: " << res.candidato << "\n";
    }

    std::cout << "Evaluaciones: "
              << res.evaluaciones << "\n";

    std::cout << "Tiempo de ejecucion: "
              << tiempo_ejecucion << " ms\n";

    return 0;
}