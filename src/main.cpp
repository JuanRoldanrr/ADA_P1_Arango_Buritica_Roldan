#include <iostream>
#include <string>
#include <chrono>
#include "fb_bruteforce.hpp"

void ejecutarFB() {
    std::string hash_objetivo;
    std::string opcion_alfabeto;
    std::string alfabeto;
    int longitud;

    std::cout << "Ingrese el Hash Objetivo (SHA-256): ";
    std::cin >> hash_objetivo;

    std::cout << "Seleccione Alfabeto (A1, A2): ";
    std::cin >> opcion_alfabeto;

    if (opcion_alfabeto == "a1" || opcion_alfabeto == "A1") {
        alfabeto = "abcdefghijklmnopqrstuvwxyz";
    } else if (opcion_alfabeto == "a2" || opcion_alfabeto == "A2") {
        alfabeto = "abcdefghijklmnopqrstuvwxyz0123456789";
    } else {
        std::cout << "Opcion no valida.\n";
        return;
    }

    std::cout << "Ingrese la longitud: ";
    std::cin >> longitud;

    bool longitud_valida = false;
    if ((opcion_alfabeto == "a1" || opcion_alfabeto == "A1") && (longitud >= 3 && longitud <= 6)) {
        longitud_valida = true;
    } else if ((opcion_alfabeto == "a2" || opcion_alfabeto == "A2") && (longitud >= 3 && longitud <= 5)) {
        longitud_valida = true;
    }

    if (!longitud_valida) {
        std::cout << "Longitud no valida para el alfabeto seleccionado.\n";
        return;
    }

    // Mediciones FB Pura
    auto tiempo_inicio = std::chrono::high_resolution_clock::now();
    ResultadoFB res = FuerzaBruta(hash_objetivo, alfabeto, longitud);
    auto tiempo_fin = std::chrono::high_resolution_clock::now();

    double tiempo_ejecucion = std::chrono::duration<double, std::milli>(
        tiempo_fin - tiempo_inicio
    ).count();

    // Mediciones Diccionario
    ResultadoFB res_dic = AtaqueDiccionario(hash_objetivo, "resources/diccionario.txt");

    std::cout << "\n Fuerza Bruta \n";
    std::cout << "Estado: " << res.estado << "\n";
    if (res.estado == "ENCONTRADA") {
        std::cout << "Candidato: " << res.candidato << "\n";
    }
    std::cout << "Evaluaciones: " << res.evaluaciones << "\n";
    std::cout << "Tiempo de ejecucion: " << tiempo_ejecucion << " ms\n";

    std::cout << "\n Diccionario\n";
    std::cout << "Estado: " << res_dic.estado << "\n";
    std::cout << "Evaluaciones: " << res_dic.evaluaciones << "\n";
}
