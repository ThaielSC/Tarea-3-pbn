#include "jugador.h"
#include <iostream>
#include <sstream>

char aMinuscula(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

Jugador::Jugador(int y, int x, int vida, int daño, int rango)
    : Entidad(y, x, vida, std::vector<std::pair<int, int> >(), rango, daño), 
      direccionActual('S'), 
      ultimaTecla(' '), 
      esperandoMovimiento(false),
      mazmorra(nullptr) {}

void Jugador::procesarEntrada(char tecla) {
    tecla = aMinuscula(tecla);
    
    // Direcciones
    if (tecla == 'w' || tecla == 's' || tecla == 'd' || tecla == 'a') {
        char nuevaDireccion;
        switch(tecla) {
            case 'w': nuevaDireccion = 'N'; break;
            case 's': nuevaDireccion = 'S'; break;
            case 'd': nuevaDireccion = 'E'; break;
            case 'a': nuevaDireccion = 'O'; break;
            default: return;
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
    // Ataque
    else if (tecla == 'x') {
        atacar();
    }
}

void Jugador::mover() {
    if (!esperandoMovimiento) return;
    
    int antiguoY = y;
    int antiguoX = x;
    int nuevoY = y;
    int nuevoX = x;
    
    // Calcular la nueva posición según la dirección
    switch(direccionActual) {
        case 'N': nuevoY--; break;
        case 'S': nuevoY++; break;
        case 'E': nuevoX++; break;
        case 'O': nuevoX--; break;
    }
    
    // Verificar si la nueva posición es valida
    if (mazmorra && nuevoY >= 0 && nuevoY < mazmorra->altoPrincipal && 
        nuevoX >= 0 && nuevoX < mazmorra->anchoPrincipal) {
        // Colisiones
        string nuevaCelda = mazmorra->salaPrincipal[nuevoY][nuevoX];
        if (nuevaCelda == "- ") {
            // Actualizar la posición
            y = nuevoY;
            x = nuevoX;
            // Actualizar el mapa
            mazmorra->actualizarPosicionJugador(antiguoY, antiguoX, y, x);
        }
    }
    
    esperandoMovimiento = false;
}

bool Jugador::hayEnemigoEnDireccion(int& enemigoY, int& enemigoX) const {
    if (!mazmorra) return false;
    
    enemigoY = y;
    enemigoX = x;
    
    // Obtener la casilla en la dirección que mira el jugador
    switch(direccionActual) {
        case 'N': enemigoY--; break;
        case 'S': enemigoY++; break;
        case 'E': enemigoX++; break;
        case 'O': enemigoX--; break;
    }
    
    // Verificar si está dentro de los límites
    if (enemigoY >= 0 && enemigoY < mazmorra->altoPrincipal &&
        enemigoX >= 0 && enemigoX < mazmorra->anchoPrincipal) {
        string celda = mazmorra->salaPrincipal[enemigoY][enemigoX];
        return (celda == "E " || celda == "J ");  // Enemigo o Jefe
    }
    
    return false;
}

string Jugador::atacar() {
    if (!mazmorra) return "";
    
    int enemigoY, enemigoX;
    if (hayEnemigoEnDireccion(enemigoY, enemigoX)) {
        mazmorra->salaPrincipal[enemigoY][enemigoX] = "- ";
    
        std::stringstream mensaje;
        mensaje << "¡Ataque con espada a enemigo en (" << enemigoY << ", " << enemigoX << ") ";
        return mensaje.str();
    }
    return "No hay un enemigo en la dirección actual";
}

// Encontrar la posición inicial de Link
Jugador Jugador::crearDesdeMapaMazmorra(const Mazmorra& mazmorra) {
    int posY = -1, posX = -1;
    for (int y = 0; y < mazmorra.altoPrincipal; y++) {
        for (int x = 0; x < mazmorra.anchoPrincipal; x++) {
            if (mazmorra.salaPrincipal[y][x] == "L" || mazmorra.salaPrincipal[y][x] == "L ") {
                posY = y;
                posX = x;
                break;
            }
        }
        if (posY != -1) break;
    }
    
    return Jugador(posY, posX, 100, 20, 1);
}
