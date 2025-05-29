#ifndef JEFE_H
#define JEFE_H

#include "entidad.h"
#include <string>

class Jefe : public Entidad {
private:
    std::string nombre;
    int frecuencia;

public:
    Jefe(const std::string& nombre, int y, int x, int vida, const std::vector<std::pair<int, int>>& movimientos, int daño, int rango, int frecuencia);

    void mover() override;

    const std::string& getNombre() const;
    int getFrecuencia() const;

    static Jefe leerDesdeStream(std::ifstream& file);
};

#endif