#include "entidad.h"
using namespace std;

Entidad::Entidad(int y, int x, int vida, const vector<pair<int, int>>& movimientos, int rango, int daño)
    : y(y), x(x), vida(vida), movimientos(movimientos), rango(rango), daño(daño), indiceMovimiento(0) {}

int Entidad::getX() const { return x; }
int Entidad::getY() const { return y; }
int Entidad::getVida() const { return vida; }
int Entidad::getRango() const { return rango; }
int Entidad::getDaño() const { return daño; }
