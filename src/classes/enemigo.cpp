#include "..//classes/enemigo.h"
using namespace std;

Enemigo::Enemigo(int y, int x, int vida, const vector<pair<int, int>>& movimientos, int daño, int rango, int frecuencia)
    : x(x), y(y), movimientos(movimientos), vida(vida), daño(daño), rango(rango), frecuencia(frecuencia) {}

void Enemigo::mover() {
    if (movimientos.empty()) return;

    auto [dy, dx] = movimientos[indiceMovimiento];
    y += dy;
    x += dx;

    indiceMovimiento++;
    if (indiceMovimiento >= movimientos.size()) { // Cambia indiceMovimiento a size_t en la clase
        indiceMovimiento = 0;
    }
}

int Enemigo::getX() const { return x; }
int Enemigo::getY() const { return y; }
int Enemigo::getVida() const { return vida; }
int Enemigo::getDaño() const { return daño; }
int Enemigo::getRango() const { return rango; }
int Enemigo::getFrecuencia() const { return frecuencia; }
const vector<pair<int, int>>& Enemigo::getMovimientos() const { return movimientos; }
