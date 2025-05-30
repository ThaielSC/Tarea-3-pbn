#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "entidad.h"
#include <string>
#include <vector>

class Enemigo : public Entidad {
private:
  int frecuencia;
  std::vector<std::pair<int, int>> movimientos;
  int indiceMovimiento;

public:
  Enemigo() = default;

  Enemigo(int y, int x, int vida,
          const std::vector<std::pair<int, int>> &movimientos, int daño,
          int rango, int frecuencia);

  virtual ~Enemigo() = default;

  void mover() override;

  int getFrecuencia() const;

  int getNumeroMovimientos() const;

  bool notMovments();

  static Enemigo leerDesdeStream(std::istream &is);

  void attack();
};

#endif
