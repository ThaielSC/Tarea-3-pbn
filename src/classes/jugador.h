#ifndef JUGADOR_H
#define JUGADOR_H

#include "entidad.h"

class Jugador : public Entidad {
public:
    Jugador(int y, int x, int vida, int daño, int rango);

    void mover() override;

    virtual ~Jugador() = default;
};

#endif