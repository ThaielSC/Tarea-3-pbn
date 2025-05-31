#include "jugador.h"
#include <sstream>

char aMinuscula(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c + ('a' - 'A');
  }
  return c;
}

Jugador::Jugador(int y, int x, int vida, int daño, int rango)
    : Entidad(y, x, vida, rango, daño), 
      direccionActual('S'), 
      ultimaTecla(' '),
      esperandoMovimiento(false), 
      debeAtacar(false),
      mazmorra(nullptr) {}

void Jugador::procesarEntrada(char tecla) {
  tecla = aMinuscula(tecla);

  // Direcciones
  if (tecla == 'w' || tecla == 's' || tecla == 'd' || tecla == 'a') {
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
    debeAtacar = false;
  }
  // Ataque
  else if (tecla == 'x') {
    debeAtacar = true;
    ultimaTecla = tecla;
  }
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

bool Jugador::hayEnemigoEnDireccion(int &enemigoY, int &enemigoX) const {
  if (!mazmorra)
    return false;

  if (enemigoY >= 0 && enemigoY < mazmorra->altoPrincipal && enemigoX >= 0 &&
      enemigoX < mazmorra->anchoPrincipal) {
    string celda = mazmorra->salaPrincipal[enemigoY][enemigoX];
    return (celda == "E " || celda == "J ");
  }

  return false;
}

string Jugador::atacar() {
  if (!mazmorra || !debeAtacar)
    return "";

  int enemigoY = getY();
  int enemigoX = getX();

  // Calcular la posición del enemigo según la dirección
  switch (direccionActual) {
  case 'N':
    enemigoY--;
    break;
  case 'S':
    enemigoY++;
    break;
  case 'E':
    enemigoX++;
    break;
  case 'O':
    enemigoX--;
    break;
  }

  // Verificar si hay enemigo
  if (hayEnemigoEnDireccion(enemigoY, enemigoX)) {
    Enemigo* enemigo = mazmorra->obtenerEnemigoEn(enemigoY, enemigoX);
    if (!enemigo) return "";
    
    // Aplicar daño al enemigo
    enemigo->recibirDaño(getDaño());
    
    stringstream mensaje;
    mensaje << "Ataque con espada a enemigo en (" << enemigoY << ", "
            << enemigoX << ")";
    
    // Si el enemigo muere, eliminarlo
    if (!enemigo->estaVivo()) {
      mensaje << " ¡El enemigo ha sido derrotado!";
      mazmorra->eliminarEnemigoEn(enemigoY, enemigoX);
    } else {
      mensaje << " (Vida restante del enemigo: " << enemigo->getVida() << ")";
      mazmorra->actualizarEnemigo(*enemigo);
    }
    
    debeAtacar = false;
    return mensaje.str();
  }
  
  debeAtacar = false;
  return "";
}

bool Jugador::hayObjetoInteractuableEnDireccion(int& objetoY, int& objetoX, string& tipoObjeto) const {
    if (!mazmorra) return false;

    objetoY = getY();
    objetoX = getX();

    switch (direccionActual) {
    case 'N':
        objetoY--;
        break;
    case 'S':
        objetoY++;
        break;
    case 'E':
        objetoX++;
        break;
    case 'O':
        objetoX--;
        break;
    }

    if (objetoY >= 0 && objetoY < mazmorra->altoPrincipal &&
        objetoX >= 0 && objetoX < mazmorra->anchoPrincipal) {
        string celda = mazmorra->salaPrincipal[objetoY][objetoX];
        if (celda == "C " || celda == "U ") {
            tipoObjeto = "cofre";
            return true;
        }
        if (celda == "K " || celda == "U ") {
            tipoObjeto = "cofre_jefe";
            return true;
        }
        if (celda == "P ") {
            tipoObjeto = "puerta";
            return true;
        }
    }

    return false;
}

string Jugador::interactuar() {
    int objetoY, objetoX;
    string tipoObjeto;

    if (!hayObjetoInteractuableEnDireccion(objetoY, objetoX, tipoObjeto)) {
        return "No hay nada con qué interactuar en esa dirección.";
    }

    if (tipoObjeto == "cofre") {
        string estadoCofre = mazmorra->salaPrincipal[objetoY][objetoX];
        if (estadoCofre == "C ") {
            mazmorra->salaPrincipal[objetoY][objetoX] = "U ";
            return "¡Has abierto un cofre y obtenido una llave!";
        } else {
            return "Este cofre ya está abierto.";
        }
    } else if (tipoObjeto == "cofre_jefe") {
        string estadoCofre = mazmorra->salaPrincipal[objetoY][objetoX];
        if (estadoCofre == "K ") {
            mazmorra->salaPrincipal[objetoY][objetoX] = "U ";
            return "¡Has abierto un cofre y obtenido la llave del jefe!";
        } else {
            return "Este cofre ya está abierto.";
        }
    } else if (tipoObjeto == "puerta") {
        return "Interacción con puertas aún no implementada.";
    }

    return "";
}
