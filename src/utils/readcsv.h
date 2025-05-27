#ifndef READCSV_H
#define READCSV_H
using namespace std;

#include <string>
#include <vector>
#include "..//classes/enemigo.h"
#include "../classes/mazmorra.h"
#include "../classes/jefe.h"

vector<Mazmorra> leerMazmorras(const string &filename);
vector<Enemigo> leerEnemigos(const string& nombreArchivo, Jefe & jefe, vector<Enemigo>& enemigosJefe);


#endif
