#include "..//classes/jefe.h"
using namespace std;

Jefe::Jefe(const string& nombre, int y, int x, int vida, const vector<pair<int, int>>& movimientos, int daño, int rango, int frecuencia)
    : nombre(nombre), y(y), x(x), movimientos(movimientos), vida(vida), daño(daño), rango(rango), frecuencia(frecuencia) {}

void Jefe::mover() {
    if (movimientos.empty()) return;

    auto [dy, dx] = movimientos[indiceMovimiento];
    y += dy;
    x += dx;

    indiceMovimiento++;
    if (indiceMovimiento >= movimientos.size()) {
        indiceMovimiento = 0;
    }
}

int Jefe::getX() const { return x; }
int Jefe::getY() const { return y; }
int Jefe::getVida() const { return vida; }
int Jefe::getDaño() const { return daño; }
int Jefe::getRango() const { return rango; }
int Jefe::getFrecuencia() const { return frecuencia; }
string Jefe::getNombre() const { return nombre; }
