#pragma once
#include <string>
#include <algorithm>

// Parametros de la politica de contraseñas
struct PolicyParams {
    int n = 8;
    int minLower = 0;
    int minUpper = 0;
    int minDigit = 0;
    int minSymbol = 0;
    bool prohibirConsecutivosRepetidos = true; // regla fija, aplica a todas las instancias
    std::string nombre; // etiqueta corta para archivos/reportes (ej. "completa_n8")
};

enum class Categoria { MINUSCULA, MAYUSCULA, DIGITO, SIMBOLO };

inline Categoria categoriaDe(char c) {
    if (c >= 'a' && c <= 'z') return Categoria::MINUSCULA;
    if (c >= 'A' && c <= 'Z') return Categoria::MAYUSCULA;
    if (c >= '0' && c <= '9') return Categoria::DIGITO;
    return Categoria::SIMBOLO; // !, @, #, $, %
}

// Construye el alfabeto base

inline std::string construirAlfabetoBT() {
    std::string alfabeto;
    for (char c = 'a'; c <= 'z'; ++c) alfabeto += c;
    for (char c = 'A'; c <= 'Z'; ++c) alfabeto += c;
    for (char c = '0'; c <= '9'; ++c) alfabeto += c;
    for (char c : {'!', '@', '#', '$', '%'}) alfabeto += c;
    return alfabeto;
}


//  (funcion de factibilidad )
inline bool esFactible(int faltanLower, int faltanUpper,
                        int faltanDigit, int faltanSymbol,
                        int posicionesRestantes) {
    int faltanTotal = faltanLower + faltanUpper + faltanDigit + faltanSymbol;
    return faltanTotal <= posicionesRestantes;
}

// Verifica si una cadena completa cumple la politica
inline bool cumplePolitica(const std::string& s, const PolicyParams& p) {
    if (static_cast<int>(s.size()) != p.n) return false;
    int lower = 0, upper = 0, digit = 0, symbol = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        switch (categoriaDe(s[i])) {
            case Categoria::MINUSCULA: ++lower; break;
            case Categoria::MAYUSCULA: ++upper; break;
            case Categoria::DIGITO: ++digit; break;
            case Categoria::SIMBOLO: ++symbol; break;
        }
        if (p.prohibirConsecutivosRepetidos && i > 0 && s[i] == s[i - 1])
            return false;
    }
    return lower >= p.minLower && upper >= p.minUpper &&
           digit >= p.minDigit && symbol >= p.minSymbol;
}