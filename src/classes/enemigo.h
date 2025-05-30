#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "entidad.h"
#include <vector>
#include <string>

class Enemigo : public Entidad {
private:
    int frecuencia;

public:
    Enemigo() = default;

    Enemigo(int y, int x, int vida, const std::vector<std::pair<int, int> > & movimientos, int daño, int rango, int frecuencia);

    virtual ~Enemigo() = default;

    void mover() override;

    int getFrecuencia() const;

    int getNumeroMovimientos() const;

    static Enemigo leerDesdeStream(std::istream& is);

};

#endif