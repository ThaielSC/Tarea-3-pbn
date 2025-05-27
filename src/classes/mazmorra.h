#ifndef MAZMORRA_H
#define MAZMORRA_H

#include <string>
#include <vector>
using namespace std;

class Mazmorra {
public:
  int anchoPrincipal, altoPrincipal;
  int anchoJefe, altoJefe;
  vector<vector<string> > salaPrincipal;
  vector<vector<string> > salaJefe;

  void mostrar() const;
};

#endif
