#include <iostream>
#include <chrono>
#include "fb_bruteforce.hpp"

void ejecutarModuloFuerzaBruta() {
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
        std::cout << "Alfabeto no valido.\n";
        return;
    }

    std::cout << "Ingrese longitud: ";
    std::cin >> longitud;

    // Ejecución FB Pura
    auto t1_inicio = std::chrono::high_resolution_clock::now();
    ResultadoFB res_fb = FuerzaBruta(hash_objetivo, alfabeto, longitud);
    auto t1_fin = std::chrono::high_resolution_clock::now();
    double t_fb = std::chrono::duration<double, std::milli>(t1_fin - t1_inicio).count();

    // Ejecución Diccionario
    auto t2_inicio = std::chrono::high_resolution_clock::now();
    ResultadoFB res_dic = AtaqueDiccionario(hash_objetivo, "resources/diccionario.txt");
    auto t2_fin = std::chrono::high_resolution_clock::now();
    double t_dic = std::chrono::duration<double, std::milli>(t2_fin - t2_inicio).count();

    // Impresión de resultados
    std::cout << "\n Fuerza Bruta\n";
    std::cout << "Estado: " << res_fb.estado << "  Candidato: " << res_fb.candidato 
              << " Evaluaciones: " << res_fb.evaluaciones << "  Tiempo: " << t_fb << " ms\n";

    std::cout << "\n Por diccionario\n";
    std::cout << "Estado: " << res_dic.estado << "  Candidato: " << res_dic.candidato 
              << " Evaluacioned: " << res_dic.evaluaciones << "  Tiempo: " << t_dic << " ms\n";
}
