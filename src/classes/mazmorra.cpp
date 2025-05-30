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

Mazmorra::Mazmorra(
    int anchoPrincipal, int altoPrincipal,
    int anchoJefe, int altoJefe,
    const vector<vector<string> >& salaPrincipal,
    const vector<vector<string> >& salaJefe,
    const vector<Enemigo>& enemigosIniciales,
    const Jefe& jefe,
    const vector<Enemigo>& enemigosJefe
) : anchoPrincipal(anchoPrincipal), altoPrincipal(altoPrincipal),
    anchoJefe(anchoJefe), altoJefe(altoJefe),
    salaPrincipal(salaPrincipal), salaJefe(salaJefe),
    enemigosIniciales(enemigosIniciales), jefe(jefe), enemigosJefe(enemigosJefe) {}

const std::vector<Enemigo>& Mazmorra::getEnemigosIniciales() const {
    return enemigosIniciales;
}

const Jefe& Mazmorra::getJefe() const {
    return jefe;
}

const std::vector<Enemigo>& Mazmorra::getEnemigosJefe() const {
    return enemigosJefe;
}

void Mazmorra::actualizarPosicionJugador(int antiguoY, int antiguoX, int nuevoY, int nuevoX) {
    // Verificar que las coordenadas estén dentro de los límites
    if (antiguoY >= 0 && antiguoY < altoPrincipal && antiguoX >= 0 && antiguoX < anchoPrincipal &&
        nuevoY >= 0 && nuevoY < altoPrincipal && nuevoX >= 0 && nuevoX < anchoPrincipal) {
        // Borrar la posición anterior
        salaPrincipal[antiguoY][antiguoX] = "- ";
        // Colocar al jugador en la nueva posición
        salaPrincipal[nuevoY][nuevoX] = "L ";
    }
}