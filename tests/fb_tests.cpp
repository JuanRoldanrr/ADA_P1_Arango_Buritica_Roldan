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

// test 8: Ninguna de las claves de las pruebas aparece en el diccionario oficial
void probarDiccionarioOficial() {
    const std::string ruta =
        "resources/diccionario.txt";

    const std::string hashes[] = {
        // abc12 - referencia
        "8d51feb34e3e69f6fa6dffc577e2c60490cf9a7fcd835f9f6af1505b71d74773",

        // ijax
        "c56d1270821c92b3205d36e89d1fb0fd0bad3b9f2862242d6b2a5a3392a6b499",

        // ans9
        "b55df863e210fa4784207934f751b2342a6f1f59f63c5f0fabbca7a9f9fba7fa",

        // uxyby
        "3d703d21cf2e0792a465caf7e59b6e80b65fe53d90cea94fab66e40ebf663242",

        // r0la7
        "199d6d898dfc43886d05ba5540f3da1e42d56c66327de37f67fc981889962c1d",

        // wpctwv
        "1bc54ae0767a4dba59cb26bb16c4148d058d9a0d7b628340576f4c054432b96d"
    };

    for (const std::string& hash : hashes) {
        ResultadoFB res =
            AtaqueDiccionario(hash, ruta);

        assert(res.estado == "NO ENCONTRADA");
        assert(res.candidato == "NULO");
        assert(res.evaluaciones == 500);
    }

    std::cout
        << "[PASS] Diccionario oficial: "
        << "ninguna de las claves fue encontrada\n";
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
    probarDiccionarioOficial();

    probarEvaluaciones();

    std::cout
        << "\nTodas las pruebas de Fuerza Bruta y Diccionario "
           "pasaron correctamente.\n";

    return 0;
}