#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>

#include "../src/fb_bruteforce.hpp"
#include "../src/third_party/picosha2.h"

// TEST 1: FB encuentra contraseña con A1
void probarFuerzaBrutaExitosa() {
    std::string clave = "abc";
    std::string hash_objetivo =
        picosha2::hash256_hex_string(clave);

    std::string alfabeto =
        "abcdefghijklmnopqrstuvwxyz";

    ResultadoFB res =
        FuerzaBruta(hash_objetivo, alfabeto, 3);

    assert(res.estado == "ENCONTRADA");
    assert(res.candidato == clave);
    assert(res.evaluaciones > 0);

    std::cout
        << "[PASS] Fuerza Bruta exitosa (A1)\n";
}

// TEST 2: FB no encuentra una contraseña
void probarFuerzaBrutaFallida() {
    std::string hash_falso =
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";

    std::string alfabeto = "abc";

    ResultadoFB res =
        FuerzaBruta(hash_falso, alfabeto, 3);

    assert(res.estado == "NO ENCONTRADA");
    assert(res.candidato == "NULO");
    assert(res.evaluaciones > 0);

    std::cout
        << "[PASS] Fuerza Bruta fallida\n";
}

// Test 3: FB con alfabeto A2
void probarFuerzaBrutaA2() {
    std::string clave = "a0";

    std::string hash_objetivo =
        picosha2::hash256_hex_string(clave);

    std::string alfabeto =
        "abcdefghijklmnopqrstuvwxyz0123456789";

    ResultadoFB res =
        FuerzaBruta(hash_objetivo, alfabeto, 2);

    assert(res.estado == "ENCONTRADA");
    assert(res.candidato == clave);
    assert(res.evaluaciones > 0);

    std::cout
        << "[PASS] Fuerza Bruta con alfabeto A2\n";
}

// Test 4: Ataque de diccionario encuentra una palabra
void probarDiccionarioExitoso() {
    const std::string ruta =
        "tests/diccionario_test.txt";

    std::ofstream archivo(ruta);

    assert(archivo.is_open());

    archivo << "hola1\n";
    archivo << "clave99\n";
    archivo << "sistemas6\n";

    archivo.close();

    std::string clave = "clave99";

    std::string hash_objetivo =
        picosha2::hash256_hex_string(clave);

    ResultadoFB res =
        AtaqueDiccionario(hash_objetivo, ruta);

    assert(res.estado == "ENCONTRADA");
    assert(res.candidato == clave);
    assert(res.evaluaciones == 2);

    std::remove(ruta.c_str());

    std::cout
        << "[PASS] Ataque de diccionario exitoso\n";
}

// Test 5: Ataque de diccionario no encuentra la palabra
void probarDiccionarioFallido() {
    const std::string ruta =
        "tests/diccionario_test.txt";

    std::ofstream archivo(ruta);

    assert(archivo.is_open());

    archivo << "hola1\n";
    archivo << "clave99\n";
    archivo << "sistemas6\n";

    archivo.close();

    std::string clave = "noesta";

    std::string hash_objetivo =
        picosha2::hash256_hex_string(clave);

    ResultadoFB res =
        AtaqueDiccionario(hash_objetivo, ruta);

    assert(res.estado == "NO ENCONTRADA");
    assert(res.candidato == "NULO");
    assert(res.evaluaciones == 3);

    std::remove(ruta.c_str());

    std::cout
        << "[PASS] Ataque de diccionario fallido\n";
}
// Test 6: Archivo de diccionario inexistente
void probarDiccionarioArchivoInexistente() {
    ResultadoFB res =
        AtaqueDiccionario(
            "hash_inexistente",
            "tests/archivo_que_no_existe.txt"
        );

    assert(res.estado == "ERROR_ARCHIVO");
    assert(res.candidato == "NULO");
    assert(res.evaluaciones == 0);

    std::cout
        << "[PASS] Archivo de diccionario inexistente\n";
}

// test 7: El número de evaluaciones es coherente
void probarEvaluaciones() {
    std::string clave = "ab";

    std::string hash_objetivo =
        picosha2::hash256_hex_string(clave);

    std::string alfabeto = "ab";

    ResultadoFB res =
        FuerzaBruta(hash_objetivo, alfabeto, 2);

    assert(res.estado == "ENCONTRADA");
    assert(res.candidato == clave);
    assert(res.evaluaciones > 0);

    std::cout
        << "[PASS] Conteo de evaluaciones\n";
}

int main() {

    std::cout
        << "Pruebas unitarias de Fuerza Bruta y Diccionario\n\n";

    probarFuerzaBrutaExitosa();
    probarFuerzaBrutaFallida();
    probarFuerzaBrutaA2();

    probarDiccionarioExitoso();
    probarDiccionarioFallido();
    probarDiccionarioArchivoInexistente();

    probarEvaluaciones();

    std::cout
        << "\nTodas las pruebas de Fuerza Bruta y Diccionario "
           "pasaron correctamente.\n";

    return 0;
}