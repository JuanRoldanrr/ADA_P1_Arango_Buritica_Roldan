#include "fb_bruteforce.hpp"
#include "third_party/picosha2.h"
#include <fstream>
#include <iostream>

// Algoritmo de Fuerza Bruta Pura (DFS)
ResultadoFB FuerzaBruta(const std::string& hash_objetivo,
                        const std::string& alfabeto,
                        int longitud) {

    std::string candidato(longitud, ' ');
    uint64_t evaluaciones = 0;

    auto Resolver = [&](auto& self, int posicion) -> bool {
        if (posicion == longitud) {
            evaluaciones++;
            std::string hash_candidato = picosha2::hash256_hex_string(candidato);
            return hash_candidato == hash_objetivo;
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

// Algoritmo de Ataque por Diccionario
ResultadoFB AtaqueDiccionario(const std::string& hash_objetivo,
                               const std::string& ruta_diccionario) {
    std::ifstream archivo(ruta_diccionario);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de diccionario.\n";
        return {"NULO", 0, "ERROR_ARCHIVO"};
    }

    std::string palabra;
    uint64_t evaluaciones = 0;

    while (archivo >> palabra) {
        evaluaciones++;
        std::string hash_candidato = picosha2::hash256_hex_string(palabra);
        if (hash_candidato == hash_objetivo) {
            archivo.close();
            return {palabra, evaluaciones, "ENCONTRADA"};
        }
    }

    archivo.close();
    return {"NULO", evaluaciones, "NO ENCONTRADA"};
}
