#include <iostream>
#include "jugador.h"
using namespace std;

Jugador::Jugador(int x, int y, int vida, int daño, int rango, string habilidad, string direccion, bool recibiendoDaño, int llaves, int llavesJefe, int pasos, int cofresAbiertos, int puertasAbiertas, int EnemigosDerrotados, int numBombas, bool usandoHabilidad, bool atacando, bool enSalaJefe, bool haGanado) {
    direccion = "derecha";
    vida = 100;
    daño = 20;
    rango = 1;
    llaves = 0;
    llavesJefe = 0;
    pasos = 0;
    cofresAbiertos = 0;
    puertasAbiertas = 0;
    EnemigosDerrotados = 0;
    numBombas = 3;
}
