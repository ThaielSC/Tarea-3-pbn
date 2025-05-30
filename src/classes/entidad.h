#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <utility>
#include <vector>

class Entidad {
private:
  int y, x;
  int vida;
  int rango;
  int daño;

public:
  Entidad() = default;

  Entidad(int y, int x, int vida, int rango, int daño);

  void setX(int);
  void setY(int);
  int getX() const;
  int getY() const;
  int getVida() const;
  int getRango() const;
  int getDaño() const;
  void updatePos(int, int);

  virtual void mover() = 0;
};

#endif
