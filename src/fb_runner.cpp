#include "fb_runner.hpp"
#include "fb_bruteforce.hpp"
#include <iostream>
#include <string>
#include <chrono>

void ejecutarModulo() {
    std::string hash_objetivo, opcion_alfabeto, alfabeto;
    int longitud;

    std::cout << "Ingrese Hash Objetivo: ";
    std::cin >> hash_objetivo;

    std::cout << "Alfabeto (A1/A2): ";
    std::cin >> opcion_alfabeto;

    if (opcion_alfabeto == "a1" || opcion_alfabeto == "A1") {
        alfabeto = "abcdefghijklmnopqrstuvwxyz";
    } else if (opcion_alfabeto == "a2" || opcion_alfabeto == "A2") {
        alfabeto = "abcdefghijklmnopqrstuvwxyz0123456789";
    } else {
        std::cout << "Opcion no valida.\n";
        return;
    }

    std::cout << "Ingrese longitud: ";
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

    // Mediciones FB
    auto t1_inicio = std::chrono::high_resolution_clock::now();
    ResultadoFB res_fb = FuerzaBruta(hash_objetivo, alfabeto, longitud);
    auto t1_fin = std::chrono::high_resolution_clock::now();
    double t_fb = std::chrono::duration<double, std::milli>(t1_fin - t1_inicio).count();

    // Mediciones Diccionario
    ResultadoFB res_dic = AtaqueDiccionario(hash_objetivo, "resources/diccionario.txt");

    std::cout << "\n Fuerza Bruta \n";
    std::cout << "Estado: " << res_fb.estado << "  Candidato: " << res_fb.candidato 
              << " Evaluaciones: " << res_fb.evaluaciones << "  Tiempo: " << t_fb << " ms\n";

    std::cout << "\n Diccionario \n";
    std::cout << "Estado: " << res_dic.estado << " Candidato: " << res_dic.candidato 
              << " Eval: " << res_dic.evaluaciones << "\n";
}
