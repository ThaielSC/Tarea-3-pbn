#include "../classes/enemigo.h"
#include "../classes/jefe.h"
#include "../classes/mazmorra.h"
#include "../utils/readcsv.h"
#include <fstream>
#include <sstream>
using namespace std;

// LECTURA MAZMORRAS
vector<Mazmorra> leerMazmorras(const string &archivo) {
  ifstream file(archivo);
  string line;
  vector<Mazmorra> mazmorras;

  while (getline(file, line)) {
    stringstream ss(line);
    string valor;

    // Leer ancho y alto de sala principal
    Mazmorra m;
    getline(ss, valor, ',');
    m.anchoPrincipal = stoi(valor);
    getline(ss, valor, ',');
    m.altoPrincipal = stoi(valor);

    // int totalSalaPrincipal = m.anchoPrincipal * m.altoPrincipal;

    // Leer sala principal
    for (int i = 0; i < m.anchoPrincipal; ++i) {
      vector<string> fila;
      for (int j = 0; j < m.altoPrincipal; ++j) {
        getline(ss, valor, ',');
        fila.push_back(valor);
      }
      m.salaPrincipal.push_back(fila);
    }

    // Leer ancho y alto de sala del jefe
    getline(ss, valor, ',');
    m.anchoJefe = stoi(valor);
    getline(ss, valor, ',');
    m.altoJefe = stoi(valor);

    // Leer sala del jefe
    for (int i = 0; i < m.anchoJefe; ++i) {
      vector<string> fila;
      for (int j = 0; j < m.altoJefe; ++j) {
        getline(ss, valor, ',');
        fila.push_back(valor);
      }
      m.salaJefe.push_back(fila);
    }

    mazmorras.push_back(m);
  }

  return mazmorras;
}

