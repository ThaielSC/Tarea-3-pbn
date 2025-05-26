<<<<<<< HEAD
#include <iostream>

using namespace std;

int main() {
  cout << "Hello, World!" << endl;
=======
#include "utils/readcsv.h"
#include <iostream>
using namespace std;

int main() {

  // Leer mazmorras desde el CSV
  vector<Mazmorra> mazmorras = leerMazmorras("data/mazmorras.csv");

  int seleccion = 0;
  cout << "¿Qué mazmorra quieres jugar?: ";
  cin >> seleccion;

  if (seleccion < 1 || seleccion > static_cast<int>(mazmorras.size())) {
    cout << "Mazmorra inválida.\n";
    return 1;
  }

  // Mostrar mazmorra
  int idx = seleccion - 1;
  cout << "=== Mazmorra " << seleccion << " ===\n";
  cout << "\n";
  for (const auto &fila : mazmorras[idx].salaPrincipal) {
    for (const auto &celda : fila) {
      cout << celda << " ";
    }
    cout << endl;
  }
  cout << "\n\n";
  for (const auto &fila : mazmorras[idx].salaJefe) {
    for (const auto &celda : fila) {
      cout << celda << " ";
    }
    cout << endl;
  }
  cout << "======================\n";

>>>>>>> 316d5ea9d99eac8b10548c337d4fec0de2ddb49b
  return 0;
}
