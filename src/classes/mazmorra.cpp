#include "mazmorra.h"
#include <iostream>

void Mazmorra::mostrar() const {
  // Mostrar sala principal
  for (const auto &fila : salaPrincipal) {
    for (const auto &celda : fila) {
      std::cout << celda;
    }
    std::cout << '\n';
  }
  std::cout << '\n';

  // Mostrar sala del jefe
  for (const auto &fila : salaJefe) {
    for (const auto &celda : fila) {
      std::cout << celda;
    }
    std::cout << '\n';
  }
}

Mazmorra::Mazmorra(int anchoPrincipal, int altoPrincipal, int anchoJefe,
                   int altoJefe, const vector<vector<string>> &salaPrincipal,
                   const vector<vector<string>> &salaJefe,
                   const vector<Enemigo> &enemigosIniciales, const Jefe &jefe,
                   const vector<Enemigo> &enemigosJefe)
    : anchoPrincipal(anchoPrincipal), altoPrincipal(altoPrincipal),
      anchoJefe(anchoJefe), altoJefe(altoJefe), salaPrincipal(salaPrincipal),
      salaJefe(salaJefe), enemigosIniciales(enemigosIniciales), jefe(jefe),
      enemigosJefe(enemigosJefe) {}

const std::vector<Enemigo> &Mazmorra::getEnemigosIniciales() const {
  return enemigosIniciales;
}

const Jefe &Mazmorra::getJefe() const { return jefe; }

const std::vector<Enemigo> &Mazmorra::getEnemigosJefe() const {
  return enemigosJefe;
}

void Mazmorra::actualizarPosicionJugador(int antiguoY, int antiguoX, int nuevoY,
                                         int nuevoX) {
  // Verificar que las coordenadas estén dentro de los límites
  if (antiguoY >= 0 && antiguoY < altoPrincipal && antiguoX >= 0 &&
      antiguoX < anchoPrincipal && nuevoY >= 0 && nuevoY < altoPrincipal &&
      nuevoX >= 0 && nuevoX < anchoPrincipal) {
    // Borrar la posición anterior
    salaPrincipal[antiguoY][antiguoX] = "- ";
    // Colocar al jugador en la nueva posición
    salaPrincipal[nuevoY][nuevoX] = "L ";
  }
}

void Mazmorra::update(int oldx, int oldy, int newx, int newy, char symbol) {
  // Asegurar que las coordenadas son válidas antes de acceder
  if (oldy >= 0 && oldy < altoPrincipal && oldx >= 0 && oldx < anchoPrincipal) {
    salaPrincipal[oldy][oldx] = "- "; // Suponiendo que "- " es celda vacía
  }
  // Actualizar nueva posición
  if (newy >= 0 && newy < altoPrincipal && newx >= 0 && newx < anchoPrincipal) {
    salaPrincipal[newy][newx] = std::string(1, symbol) + " ";
  } else {
    // Aquí podrías manejar actualización en salaJefe si corresponde
  }
}

Enemigo *Mazmorra::obtenerEnemigoEn(int y, int x) {
  // Buscar en enemigos iniciales
  for (auto &enemigo : enemigosIniciales) {
    if (enemigo.getY() == y && enemigo.getX() == x) {
      return &enemigo;
    }
  }

  // Buscar en enemigos del jefe
  for (auto &enemigo : enemigosJefe) {
    if (enemigo.getY() == y && enemigo.getX() == x) {
      return &enemigo;
    }
  }

  // Verificar si es el jefe
  if (jefe.getY() == y && jefe.getX() == x) {
    return &jefe;
  }

  return nullptr;
}

void Mazmorra::eliminarEnemigoEn(int y, int x) {
  // Eliminar de enemigos iniciales
  auto it = enemigosIniciales.begin();
  while (it != enemigosIniciales.end()) {
    if (it->getY() == y && it->getX() == x) {
      it = enemigosIniciales.erase(it);
      salaPrincipal[y][x] = "- ";
      return;
    }
    ++it;
  }

  // Eliminar de enemigos del jefe
  it = enemigosJefe.begin();
  while (it != enemigosJefe.end()) {
    if (it->getY() == y && it->getX() == x) {
      it = enemigosJefe.erase(it);
      salaJefe[y][x] = "- ";
      return;
    }
    ++it;
  }
}

void Mazmorra::actualizarEnemigo(const Enemigo &enemigo) {
  int y = enemigo.getY();
  int x = enemigo.getX();

  // Actualizar en enemigos iniciales
  for (auto &e : enemigosIniciales) {
    if (e.getY() == y && e.getX() == x) {
      e = enemigo;
      return;
    }
  }

  // Actualizar en enemigos del jefe
  for (auto &e : enemigosJefe) {
    if (e.getY() == y && e.getX() == x) {
      e = enemigo;
      return;
    }
  }
}
