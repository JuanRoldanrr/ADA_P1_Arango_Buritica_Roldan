#ifndef FB_BRUTEFORCE_HPP
#define FB_BRUTEFORCE_HPP

#include <string>
#include <cstdint>

struct ResultadoFB {
    std::string candidato;
    uint64_t evaluaciones;
    std::string estado;
};

ResultadoFB FuerzaBruta(const std::string& hash_objetivo, const std::string& alfabeto, int longitud);
ResultadoFB AtaqueDiccionario(const std::string& hash_objetivo, const std::string& ruta_diccionario);

#endif
