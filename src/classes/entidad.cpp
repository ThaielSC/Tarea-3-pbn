#include "entidad.h"
#include <algorithm> // para std::max
using namespace std;

Entidad::Entidad(int y, int x, int vida, int rango, int daño)
    : y(y), x(x), oy(x), ox(y), vida(vida), rango(rango), daño(daño),
      map(nullptr) {}

int Entidad::getX() const { return x; }
int Entidad::getY() const { return y; }
int Entidad::getOX() const { return ox; }
int Entidad::getOY() const { return oy; }
int Entidad::getVida() const { return vida; }
int Entidad::getRango() const { return rango; }
int Entidad::getDaño() const { return daño; }

void Entidad::updatePos(int newx, int newy) {
  x = newx;
  y = newy;
}

void Entidad::setX(int newx) { x = newx; }
void Entidad::setY(int newy) { y = newy; }

void Entidad::setMap(IMap &NewMap) { map = &NewMap; }

void Entidad::recibirDaño(int cantidad) { vida = max(0, vida - cantidad); }

bool Entidad::estaVivo() const { return vida > 0; }
