#ifndef MAZMORRA_H
#define MAZMORRA_H

#include <vector>
#include <string>

class Mazmorra {
public:
    int anchoPrincipal, altoPrincipal;
    int anchoJefe, altoJefe;
    std::vector<std::vector<std::string> > salaPrincipal;
    std::vector<std::vector<std::string> > salaJefe;

    void mostrar() const;
};

#endif