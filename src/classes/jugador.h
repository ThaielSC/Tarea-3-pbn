#ifndef JUGADOR_H
#define JUGADOR_H

#include "entidad.h"
#include "mazmorra.h"
#include <string>

class Jugador : public Entidad {
private:
    char direccionActual;
    char ultimaTecla;
    bool esperandoMovimiento;
    bool debeAtacar;         
    Mazmorra* mazmorra;       
    bool hayEnemigoEnDireccion(int& enemigoY, int& enemigoX) const;
    bool hayObjetoInteractuableEnDireccion(int& objetoY, int& objetoX, string& tipoObjeto) const;

public:
    Jugador(int y, int x, int vida, int daño, int rango);

    string atacar();
    string interactuar();  
    void mover() override;
    void procesarEntrada(char tecla);
    char getDireccionActual() const { return direccionActual; }
    void setMazmorra(Mazmorra* m) { mazmorra = m; }

    // Crear un jugador desde una mazmorra
    static Jugador crearDesdeMapaMazmorra(const Mazmorra& mazmorra);

    virtual ~Jugador() = default;
};

#endif