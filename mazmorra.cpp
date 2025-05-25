#include "mazmorra.h"
#include <iostream>

void Mazmorra::mostrar() const {
    for (const auto& fila : salaPrincipal) {
        for (const auto& celda : fila) {
            std::cout << celda;
        }
        std::cout << '\n';
    }
    for (const auto& fila : salaJefe) {
        for (const auto& celda : fila) {
            std::cout << celda;
        }
        std::cout << '\n';
    }
}