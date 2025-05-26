#include "../classes/mazmorra.h"
#include "readcsv.h"
#include <fstream>
#include <sstream>

std::vector<Mazmorra> leerMazmorras(const std::string &archivo) {
  std::ifstream file(archivo);
  std::string line;
  std::vector<Mazmorra> mazmorras;

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string valor;

    // Leer ancho y alto de sala principal
    Mazmorra m;
    std::getline(ss, valor, ',');
    m.anchoPrincipal = std::stoi(valor);
    std::getline(ss, valor, ',');
    m.altoPrincipal = std::stoi(valor);

    // int totalSalaPrincipal = m.anchoPrincipal * m.altoPrincipal;

    // Leer sala principal
    for (int i = 0; i < m.altoPrincipal; ++i) {
      std::vector<std::string> fila;
      for (int j = 0; j < m.anchoPrincipal; ++j) {
        std::getline(ss, valor, ',');
        fila.push_back(valor);
      }
      m.salaPrincipal.push_back(fila);
    }

    // Leer ancho y alto de sala del jefe
    std::getline(ss, valor, ',');
    m.anchoJefe = std::stoi(valor);
    std::getline(ss, valor, ',');
    m.altoJefe = std::stoi(valor);

    // Leer sala del jefe
    for (int i = 0; i < m.altoJefe; ++i) {
      std::vector<std::string> fila;
      for (int j = 0; j < m.anchoJefe; ++j) {
        std::getline(ss, valor, ',');
        fila.push_back(valor);
      }
      m.salaJefe.push_back(fila);
    }

    mazmorras.push_back(m);
  }

  return mazmorras;
}
