#include "../classes/mazmorra.h"
#include "../classes/enemigo.h"
#include "../classes/jefe.h"
#include "..//utils/readcsv.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;


//LECTURA MAZMORRAS
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
    for (int i = 0; i < m.altoPrincipal; ++i) {
      vector<string> fila;
      for (int j = 0; j < m.anchoPrincipal; ++j) {
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
    for (int i = 0; i < m.altoJefe; ++i) {
      vector<string> fila;
      for (int j = 0; j < m.anchoJefe; ++j) {
        getline(ss, valor, ',');
        fila.push_back(valor);
      }
      m.salaJefe.push_back(fila);
    }

    mazmorras.push_back(m);
  }

  return mazmorras;
}

//LECTURA ENEMIGOS
vector<Enemigo> leerEnemigos(const string& filename) {
    ifstream file(filename);
    string line;
    vector<Enemigo> enemigos;

    while (getline(file, line)) {
        istringstream ss(line);
        string token;
        vector<string> datos;
        while (getline(ss, token, ',')) {
            datos.push_back(token);
        }

        int y = stoi(datos[0]);
        int x = stoi(datos[1]);
        int numMovs = stoi(datos[2]);
        vector<pair<int, int>> movimientos;
        for (int i = 0; i < numMovs; ++i) {
            int dy = stoi(datos[3 + 2*i]);
            int dx = stoi(datos[3 + 2*i + 1]);
            movimientos.emplace_back(dy, dx);
        }
        int vida = stoi(datos[3 + 2*numMovs]);
        int daño = stoi(datos[4 + 2*numMovs]);
        int rango = stoi(datos[5 + 2*numMovs]);
        int frecuencia = stoi(datos[6 + 2*numMovs]);

        enemigos.emplace_back(y, x, vida, movimientos, daño, rango, frecuencia);
    }

    return enemigos;
}

Jefe leerJefe(ifstream& file) {
    string line;
    getline(file, line);
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
        int dy = stoi(datos[4 + 2*i]);
        int dx = stoi(datos[4 + 2*i + 1]);
        movimientos.emplace_back(dy, dx);
    }
    int vida = stoi(datos[4 + 2*numMovs]);
    int daño = stoi(datos[5 + 2*numMovs]);
    int rango = stoi(datos[6 + 2*numMovs]);
    int frecuencia = stoi(datos[7 + 2*numMovs]);

    return Jefe(nombre, y, x, vida, movimientos, daño, rango, frecuencia);
}