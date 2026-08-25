
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

static constexpr int N = 8; // longitud fija de la politica (Modulo BT)

int main() {
    // Apellidos ya en minusculas y sin tildes
    // se ordenan alfabeticamente
    std::vector<std::string> apellidos = {"arango", "buritica", "roldan"};
    std::sort(apellidos.begin(), apellidos.end());

    std::string cadena;
    for (const auto& a : apellidos) cadena += a;

    long suma = 0;
    for (unsigned char c : cadena) suma += c;
    long semilla = suma % 100000;

    int minLower  = 2 + static_cast<int>(semilla % 3);
    int minUpper  = 1 + static_cast<int>(semilla % 2);
    int minDigit  = 1 + static_cast<int>(semilla % 3);
    int minSymbol = 1;

    int sumaCruda = minLower + minUpper + minDigit + minSymbol;
    int ajuste = std::max(0, sumaCruda - N);
    minLower -= ajuste;

    std::cout << "Apellidos ordenados : ";
    for (size_t i = 0; i < apellidos.size(); ++i)
        std::cout << apellidos[i] << (i + 1 < apellidos.size() ? ", " : "\n");
    std::cout << "Cadena concatenada  : " << cadena << "\n";
    std::cout << "Suma ASCII          : " << suma << "\n";
    std::cout << "SEMILLA             : " << semilla << "\n";
    std::cout << "minLower crudo/ajust: " << (minLower + ajuste) << " -> " << minLower << "\n";
    std::cout << "minUpper            : " << minUpper << "\n";
    std::cout << "minDigit            : " << minDigit << "\n";
    std::cout << "minSymbol           : " << minSymbol << "\n";
    std::cout << "Suma cruda / n      : " << sumaCruda << " / " << N << "\n";
    std::cout << "Ajuste aplicado     : " << ajuste
               << (ajuste > 0 ? " (se resta a minLower)\n" : " (ninguno)\n");
    std::cout << "Suma final          : " << (minLower + minUpper + minDigit + minSymbol) << "\n";
    std::cout << "Regla fija: prohibidos dos caracteres identicos consecutivos.\n";

    return 0;
}