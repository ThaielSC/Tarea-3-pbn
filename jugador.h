#include <iostream>
#ifndef JUGADOR_H
#define JUGADOR_H
using namespace std;

class Jugador {
    public:
        Jugador(int x, int y, int vida, int daño, int rango, string habilidad, string direccion, bool recibiendoDaño, int llaves, int llavesJefe, int pasos, int cofresAbiertos, int puertasAbiertas, int EnemigosDerrotados, int numBombas, bool usandoHabilidad, bool atacando, bool enSalaJefe, bool haGanado);
    
        Jugador(const std::vector<std::string>& filaCSV);

        int getVida() const {
            return vida;
        }

        int getX() const {
            return x;
        }

        int getY() const {
            return y;
        }
        
    private:
        int x;
        int y;
        int vida;
        int daño;
        int rango;
        string habilidad;
        string direccion;
        bool recibiendoDaño;
        int llaves;
        int llavesJefe;
        int pasos;
        int cofresAbiertos;
        int puertasAbiertas;
        int EnemigosDerrotados;
        int numBombas;
        bool usandoHabilidad;
        bool atacando;
        bool enSalaJefe;
        bool haGanado;
    };

    #endif