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
  vector<vector<string> > salaPrincipal;
  vector<vector<string> > salaJefe;

  Mazmorra(int anchoPrincipal, int altoPrincipal, int anchoJefe, int altoJefe,
           const vector<vector<string> > &salaPrincipal,
           const vector<vector<string> > &salaJefe,
           const vector<Enemigo> &enemigosIniciales, const Jefe &jefe,
           const vector<Enemigo> &enemigosJefe);

  virtual ~Mazmorra() = default;

  const vector<Enemigo> &getEnemigosIniciales() const;
  const Jefe &getJefe() const;
  const vector<Enemigo> &getEnemigosJefe() const;

  void mostrar() const;

  void actualizarPosicionJugador(int antiguoY, int antiguoX, int nuevoY,
                                 int nuevoX);

  void update(int oldx, int oldy, int newx, int newy, char symbol) noexcept override;

  // Métodos para manejar enemigos
  Enemigo *obtenerEnemigoEn(int y, int x);
  void eliminarEnemigoEn(int y, int x);
  void actualizarEnemigo(const Enemigo &enemigo);

private:
  vector<Enemigo> enemigosIniciales;
  Jefe jefe;
  vector<Enemigo> enemigosJefe;
};

#endif
