#include "enemigo.h"
#include <fstream>
#include <sstream>
using namespace std;

Enemigo::Enemigo(int y, int x, int vida, const vector<pair<int, int>>& movimientos, int daño, int rango, int frecuencia)
    : Entidad(y, x, vida, movimientos, rango, daño), frecuencia(frecuencia) {}

int Enemigo::getFrecuencia() const {
    return frecuencia;
}

void Enemigo::mover() {
    if (movimientos.empty()) return;
    auto [dy, dx] = movimientos[indiceMovimiento];
    y += dy;
    x += dx;
    indiceMovimiento = (indiceMovimiento + 1) % movimientos.size();
}

vector<Enemigo> Enemigo::leerDesdeCSV(const string &filename) {
    ifstream file(filename);
    string line;
    vector<Enemigo> enemigos;

    while (getline(file, line)) {
        istringstream ss(line);
        string token;
        vector<string> datos;

        while (getline(ss, token, ',')) {
            datos.push_back(token);
        }

        int y = stoi(datos[0]);
        int x = stoi(datos[1]);
        int numMovs = stoi(datos[2]);
        vector<pair<int, int>> movimientos;

        for (int i = 0; i < numMovs; ++i) {
            int dy = stoi(datos[3 + 2 * i]);
            int dx = stoi(datos[3 + 2 * i + 1]);
            movimientos.emplace_back(dy, dx);
        }

        int vida = stoi(datos[3 + 2 * numMovs]);
        int daño = stoi(datos[4 + 2 * numMovs]);
        int rango = stoi(datos[5 + 2 * numMovs]);
        int frecuencia = stoi(datos[6 + 2 * numMovs]);

        enemigos.emplace_back(y, x, vida, movimientos, daño, rango, frecuencia);
    }

    return enemigos;
}