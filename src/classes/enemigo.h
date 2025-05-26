#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <vector>
using namespace std;

class Enemigo {
private:
    int x, y;
    vector<pair<int, int>> movimientos;
    int vida;
    int daño;
    int rango;
    int frecuencia;
    size_t indiceMovimiento = 0;

public:
    Enemigo(int y, int x, int vida, const vector<pair<int, int>>& movimientos, int daño, int rango, int frecuencia);

    void mover();

    // Getters
    int getX() const;
    int getY() const;
    int getVida() const;
    int getDaño() const;
    int getRango() const;
    int getFrecuencia() const;
    const vector<pair<int, int>>& getMovimientos() const;
};

#endif