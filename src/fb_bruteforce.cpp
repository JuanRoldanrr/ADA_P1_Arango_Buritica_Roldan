#include "fb_bruteforce.hpp"
#include "third_party/picosha2.h"
#include <fstream>
#include <iostream>

ResultadoFB FuerzaBruta(const std::string& hash_objetivo, const std::string& alfabeto, int longitud) {
    std::string candidato(longitud, ' ');
    uint64_t evaluaciones = 0;

    auto Resolver = [&](auto& self, int posicion) -> bool {
        if (posicion == longitud) {
            evaluaciones++;
            return picosha2::hash256_hex_string(candidato) == hash_objetivo;
        }
        for (char ch : alfabeto) {
            candidato[posicion] = ch;
            if (self(self, posicion + 1)) return true;
        }
        return false;
    };

    if (Resolver(Resolver, 0)) {
        return {candidato, evaluaciones, "ENCONTRADA"};
    }
    return {"NULO", evaluaciones, "NO ENCONTRADA"};
}

ResultadoFB AtaqueDiccionario(const std::string& hash_objetivo, const std::string& ruta_diccionario) {
    std::ifstream archivo(ruta_diccionario);
    if (!archivo.is_open()) return {"NULO", 0, "ERROR_ARCHIVO"};

    std::string palabra;
    uint64_t evaluaciones = 0;
    while (archivo >> palabra) {
        evaluaciones++;
        if (picosha2::hash256_hex_string(palabra) == hash_objetivo) {
            archivo.close();
            return {palabra, evaluaciones, "ENCONTRADA"};
        }
    }
    archivo.close();
    return {"NULO", evaluaciones, "NO ENCONTRADA"};
}
