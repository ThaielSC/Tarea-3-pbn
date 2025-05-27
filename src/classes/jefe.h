#ifndef JEFE_H
#define JEFE_H

#include <string>
#include <vector>
using namespace std;

class Jefe {
private:
    string nombre;
    int y, x;
    vector<pair<int, int>> movimientos;
    int vida;
    int daño;
    int rango;
    int frecuencia;
    size_t indiceMovimiento = 0;

public:
    Jefe(const string& nombre, int y, int x, int vida, const vector<pair<int, int>>& movimientos, int daño, int rango, int frecuencia);

    void mover();

    // Getters
    int getX() const;
    int getY() const;
    int getVida() const;
    int getDaño() const;
    int getRango() const;
    int getFrecuencia() const;
    string getNombre() const;
};

#endif