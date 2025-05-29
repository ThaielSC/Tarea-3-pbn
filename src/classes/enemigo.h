#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "entidad.h"
#include <vector>
#include <string>

class Enemigo : public Entidad {
private:
    int frecuencia;

public:
    Enemigo(int y, int x, int vida, const std::vector<std::pair<int, int>>& movimientos, int daño, int rango, int frecuencia);

    virtual ~Enemigo() = default;

    void mover() override;

    int getFrecuencia() const;

    static std::vector<Enemigo> leerDesdeCSV(const std::string &filename);
};

#endif