#include "jugador.h"

char aMinuscula(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c + ('a' - 'A');
  }
  return c;
}

Jugador::Jugador(int y, int x, int vida, int daño, int rango)
    : Entidad(y, x, vida, rango, daño), direccionActual('S'), ultimaTecla(' '),
      esperandoMovimiento(false), mazmorra(nullptr) {}

void Jugador::procesarEntrada(char tecla) {
  tecla = aMinuscula(tecla);

  // Direcciones
  char nuevaDireccion;
  switch (tecla) {
  case 'w':
    nuevaDireccion = 'N';
    break;
  case 's':
    nuevaDireccion = 'S';
    break;
  case 'd':
    nuevaDireccion = 'E';
    break;
  case 'a':
    nuevaDireccion = 'O';
    break;
  default:
    return;
  }

  // Si es la misma direccion mover
  if (tecla == aMinuscula(ultimaTecla) && direccionActual == nuevaDireccion) {
    esperandoMovimiento = true;
  } else {
    // Si es una tecla diferente solo girar
    direccionActual = nuevaDireccion;
    esperandoMovimiento = false;
  }

  ultimaTecla = tecla;
}

void Jugador::mover() {
  if (!esperandoMovimiento)
    return;

  int antiguoY = getY();
  int antiguoX = getX();
  int nuevoY = getY();
  int nuevoX = getX();

  // Calcular la nueva posición según la dirección
  switch (direccionActual) {
  case 'N':
    nuevoY--;
    break;
  case 'S':
    nuevoY++;
    break;
  case 'E':
    nuevoX++;
    break;
  case 'O':
    nuevoX--;
    break;
  }

  // Verificar si la nueva posición es valida
  if (mazmorra && nuevoY >= 0 && nuevoY < mazmorra->altoPrincipal &&
      nuevoX >= 0 && nuevoX < mazmorra->anchoPrincipal) {
    // Colisiones
    string nuevaCelda = mazmorra->salaPrincipal[nuevoY][nuevoX];
    if (nuevaCelda == "- ") {
      // Actualizar la posición
      setY(nuevoY);
      setX(nuevoX);
      // Actualizar el mapa
      mazmorra->actualizarPosicionJugador(antiguoY, antiguoX, getY(), getX());
    }
  }

  esperandoMovimiento = false;
}

// Encontrar la posición inicial de Link
Jugador Jugador::crearDesdeMapaMazmorra(const Mazmorra &mazmorra) {
  int posY = -1, posX = -1;
  for (int y = 0; y < mazmorra.altoPrincipal; y++) {
    for (int x = 0; x < mazmorra.anchoPrincipal; x++) {
      if (mazmorra.salaPrincipal[y][x] == "L" ||
          mazmorra.salaPrincipal[y][x] == "L ") {
        posY = y;
        posX = x;
        break;
      }
    }
    if (posY != -1)
      break;
  }

  return Jugador(posY, posX, 100, 20, 1);
}
