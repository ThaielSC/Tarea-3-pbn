#ifndef GAME_H
#define GAME_H

#include "../classes/mazmorra.h"
// #include "../classes/dungeon.h" // TODO: Cambio de nombre
#include "../classes/jugador.h"
#include "../utils/readcsv.h"
#include "enemigo.h"
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Utils {};

class Game {
private:
  vector<Mazmorra> dungeons;
  string enemys_path;
  Mazmorra *mazmorra;
  Jugador *jugador;
  bool gameOver;
  int llaves;
  bool llavejefe;

  void mostrarEstado() const;
  void procesarComando(char comando);
  void limpiarPantalla() const;

public:
  // Constructor para el menú
  Game(string dungeon_path, string enemys_path);

  // Constructor para el juego
  Game(Mazmorra *maz, Jugador *jug);

  vector<Mazmorra> &get_dungeons();
  void run();
};

#endif
