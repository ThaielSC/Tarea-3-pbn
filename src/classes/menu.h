#include "game.h"
#include "mazmorra.h"
#include <string>

using namespace std;

class Menu {
private:
  string startDisplay;
  Game game;

public:
  Menu(string, string);
  void run();
  void start();
  Mazmorra select_dungeon();
};
