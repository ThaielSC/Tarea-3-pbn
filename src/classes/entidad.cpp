#include "entidad.h"
using namespace std;

Entidad::Entidad(int y, int x, int vida, int rango, int daño)
    : y(y), x(x), vida(vida), rango(rango), daño(daño) {}

int Entidad::getX() const { return x; }
int Entidad::getY() const { return y; }
int Entidad::getVida() const { return vida; }
int Entidad::getRango() const { return rango; }
int Entidad::getDaño() const { return daño; }
void Entidad::updatePos(int newx, int newy) {
  x += newx;
  y += newy;
};

void Entidad::setX(int newx) { x = newx; }
void Entidad::setY(int newy) { y = newy; }
