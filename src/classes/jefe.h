#ifndef JEFE_H
#define JEFE_H

#include "enemigo.h"
#include <string>

class Jefe : public Enemigo {
private:
  std::string nombre;

public:
  Jefe(const std::string &nombre, int y, int x, int vida,
       const std::vector<std::pair<int, int>> &movimientos, int daño, int rango,
       int frecuencia);

  const std::string &getNombre() const;

  static Jefe leerDesdeStream(std::istream &is);
};

#endif
