#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <vector>
#include <utility>

class Entidad {
protected:
    int y, x;
    int vida;
    std::vector<std::pair<int, int> > movimientos;
    int rango;
    int daño;
    int indiceMovimiento;

public:
    Entidad() = default;

    Entidad(int y, int x, int vida, const std::vector<std::pair<int, int> > & movimientos, int rango, int daño);

    int getX() const;
    int getY() const;
    int getVida() const;
    int getRango() const;
    int getDaño() const;

    virtual ~Entidad() = default;

    virtual void mover()=0; //Esto porque se hace override en todas las clases que heredan
};

#endif