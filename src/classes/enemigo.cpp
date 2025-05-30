#include "enemigo.h"
#include <fstream>
#include <sstream>
using namespace std;

Enemigo::Enemigo(int y, int x, int vida, const std::vector<std::pair<int, int>>& movimientos, int daño, int rango, int frecuencia)
    : Entidad(y, x, vida, movimientos, daño, rango), frecuencia(frecuencia) {}

int Enemigo::getFrecuencia() const {
    return frecuencia;
}

int Enemigo::getNumeroMovimientos() const {
    return movimientos.size();
}

void Enemigo::mover() {
    if (movimientos.empty()) return;
    auto [dy, dx] = movimientos[indiceMovimiento];
    y += dy;
    x += dx;
    indiceMovimiento = (indiceMovimiento + 1) % movimientos.size();
}


Enemigo Enemigo::leerDesdeStream(std::istream& is) {
    std::string line;
    if (!std::getline(is, line) || line.empty())
        throw std::runtime_error("Error al leer línea de enemigo");

    std::istringstream ss(line);
    std::vector<std::string> datos;
    std::string token;
    while (std::getline(ss, token, ',')) datos.push_back(token);

    if (datos.size() < 7)
        throw std::runtime_error("Datos insuficientes para crear Enemigo");

    int y = stoi(datos[0]);
    int x = stoi(datos[1]);
    int numMovs = stoi(datos[2]);
    std::vector<std::pair<int, int>> movimientos;
    for (int i = 0; i < numMovs; ++i) {
        int dy = stoi(datos[3 + 2 * i]);
        int dx = stoi(datos[3 + 2 * i + 1]);
        movimientos.emplace_back(dy, dx);
    }
    int vida = stoi(datos[3 + 2 * numMovs]);
    int daño = stoi(datos[4 + 2 * numMovs]);
    int rango = stoi(datos[5 + 2 * numMovs]);
    int frecuencia = stoi(datos[6 + 2 * numMovs]);

    return Enemigo(y, x, vida, movimientos, daño, rango, frecuencia);
}