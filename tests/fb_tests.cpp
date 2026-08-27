#include <iostream>
#include <cassert>
#include "../src/fb_bruteforce.hpp"
#include "../src/third_party/picosha2.h"

void probarFuerzaBrutaExitosa() {
    std::string clave = "abc";
    std::string hash_objetivo = picosha2::hash256_hex_string(clave);
    std::string alfabeto = "abcdefghijklmnopqrstuvwxyz";

    ResultadoFB res = FuerzaBruta(hash_objetivo, alfabeto, 3);

    assert(res.estado == "ENCONTRADA");
    assert(res.candidato == "abc");
    assert(res.evaluaciones > 0);
    std::cout << "[PASS] Prueba Fuerza Bruta Exitosa\n";
}

void probarFuerzaBrutaFallida() {
    std::string hash_falso = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
    std::string alfabeto = "abc";

    ResultadoFB res = FuerzaBruta(hash_falso, alfabeto, 3);

    assert(res.estado == "NO ENCONTRADA");
    assert(res.candidato == "NULO");
    std::cout << "[PASS] Prueba Fuerza Bruta Fallida\n";
}

int main() {
    std::cout << "Pruebas unitarias \n";
    probarFuerzaBrutaExitosa();
    probarFuerzaBrutaFallida();
    std::cout << "Todas las pruebas de Fuerza Bruta pasaron correctamente.\n";
    return 0;
}
