#include "jefe.h"
#include <sstream>

using namespace std;

Jefe::Jefe(const string &nombre, int y, int x, int vida,
           const vector<pair<int, int>> &movimientos, int daño, int rango,
           int frecuencia)
    : Enemigo(y, x, vida, movimientos, daño, rango, frecuencia),
      nombre(nombre) {}

const string &Jefe::getNombre() const { return nombre; }

Jefe Jefe::leerDesdeStream(std::istream &is) {
  string line;
  getline(is, line);
  istringstream ss(line);
  string token;
  vector<string> datos;

  while (getline(ss, token, ',')) {
    datos.push_back(token);
  }

  string nombre = datos[0];
  int y = stoi(datos[1]);
  int x = stoi(datos[2]);
  int numMovs = stoi(datos[3]);

  vector<pair<int, int>> movimientos;
  for (int i = 0; i < numMovs; ++i) {
    int dy = stoi(datos[4 + 2 * i]);
    int dx = stoi(datos[4 + 2 * i + 1]);
    movimientos.emplace_back(dy, dx);
  }

  int vida = stoi(datos[4 + 2 * numMovs]);
  int daño = stoi(datos[5 + 2 * numMovs]);
  int rango = stoi(datos[6 + 2 * numMovs]);
  int frecuencia = stoi(datos[7 + 2 * numMovs]);

  return Jefe(nombre, y, x, vida, movimientos, daño, rango, frecuencia);
}
