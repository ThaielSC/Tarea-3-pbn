#ifndef JUGADOR_H
#define JUGADOR_H

#include "entidad.h"
#include "mazmorra.h"
#include <string>

class Jugador : public Entidad {
private:
    char direccionActual;
    char ultimaTecla;
    bool esperandoMovimiento;  // Dirección correcta
    Mazmorra* mazmorra;  // Puntero a la mazmorra actual

public:
    Jugador(int y, int x, int vida, int daño, int rango);

    void mover() override;
    void procesarEntrada(char tecla);
    char getDireccionActual() const { return direccionActual; }
    void setMazmorra(Mazmorra* m) { mazmorra = m; }

    // Método estático para crear un jugador desde una mazmorra
    static Jugador crearDesdeMapaMazmorra(const Mazmorra& mazmorra);

    virtual ~Jugador() = default;
};

#endif