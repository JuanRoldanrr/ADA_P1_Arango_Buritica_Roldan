#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {

    string apellidos = "Arango Buritica Roldan";
    string cadena;

    for (char c : apellidos) {
        if (c != ' ') {
            cadena += tolower(c);
        }
    }

    cout << "Cadena: " << cadena << endl;

    int suma = 0;

    for (char c : cadena) {
        suma += static_cast<unsigned char>(c);
    }

    int semilla = suma % 100000;

    cout << "Suma ASCII: " << suma << endl;
    cout << "Semilla: " << semilla << endl;

    return 0;
}