#ifndef ENTIDAD_H
#define ENTIDAD_H

#include "imap.h"
#include <utility>
#include <vector>

class Entidad {
private:
  int y, x;
  int oy, ox;
  int vida;
  int rango;
  int daño;

public:
  IMap *map;
  Entidad() = default;

  Entidad(int y, int x, int vida, int rango, int daño);

  void setX(int);
  void setY(int);
  int getX() const;
  int getY() const;
  int getOX() const;
  int getOY() const;
  int getVida() const;
  int getRango() const;
  int getDaño() const;
  void updatePos(int, int);
  void setMap(IMap &map);

  // Métodos para manejar vida
  void recibirDaño(int cantidad);
  bool estaVivo() const;

  virtual void mover() = 0;
};

#endif
