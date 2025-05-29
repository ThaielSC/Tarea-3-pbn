#include "jefe.h"
#include <sstream>
#include <fstream>
using namespace std;

Jefe::Jefe(const string& nombre, int y, int x, int vida, const vector<pair<int, int>>& movimientos, int daño, int rango, int frecuencia)
    : Entidad(y, x, vida, movimientos, rango, daño), nombre(nombre), frecuencia(frecuencia) {}

void Jefe::mover() {
    if (movimientos.empty()) return;
    auto [dy, dx] = movimientos[indiceMovimiento];
    y += dy;
    x += dx;
    indiceMovimiento = (indiceMovimiento + 1) % movimientos.size();
}

const string& Jefe::getNombre() const {
    return nombre;
}

int Jefe::getFrecuencia() const {
    return frecuencia;
}

Jefe Jefe::leerDesdeStream(ifstream& file) {
    string line;
    getline(file, line);
    istringstream ss(line);
    string token;
    vector<string> datos;

    while (getline(ss, token, ',')) {
        datos.push_back(token);
    }

    string nombre = datos[0];
    int y = stoi(datos[1]);
    int x = stoi(datos[2]);
    int numMovs = stoi(datos[3]);

    vector<pair<int, int>> movimientos;
    for (int i = 0; i < numMovs; ++i) {
        int dy = stoi(datos[4 + 2 * i]);
        int dx = stoi(datos[4 + 2 * i + 1]);
        movimientos.emplace_back(dy, dx);
    }

    int vida = stoi(datos[4 + 2 * numMovs]);
    int daño = stoi(datos[5 + 2 * numMovs]);
    int rango = stoi(datos[6 + 2 * numMovs]);
    int frecuencia = stoi(datos[7 + 2 * numMovs]);

    return Jefe(nombre, y, x, vida, movimientos, daño, rango, frecuencia);
}