#ifndef MAZMORRA_H
#define MAZMORRA_H

#include "enemigo.h"
#include "entidad.h"
#include "jefe.h"
#include <string>
#include <vector>
using namespace std;

class Mazmorra : public IMap {
public:
  int anchoPrincipal, altoPrincipal;
  int anchoJefe, altoJefe;
  int numEnemigosIniciales;
  vector<vector<string>> salaPrincipal;
  vector<vector<string>> salaJefe;

  Mazmorra(int anchoPrincipal, int altoPrincipal, int anchoJefe, int altoJefe,
           const vector<vector<string>> &salaPrincipal,
           const vector<vector<string>> &salaJefe,
           const vector<Enemigo> &enemigosIniciales, const Jefe &jefe,
           const vector<Enemigo> &enemigosJefe);

  const vector<Enemigo> &getEnemigosIniciales() const;
  const Jefe &getJefe() const;
  const vector<Enemigo> &getEnemigosJefe() const;

  void mostrar() const;
  void actualizarPosicionJugador(int antiguoY, int antiguoX, int nuevoY,
                                 int nuevoX);
  void update(int, int, int, int, char) override;

private:
  vector<Enemigo> enemigosIniciales;
  Jefe jefe;
  vector<Enemigo> enemigosJefe;
};

#endif
