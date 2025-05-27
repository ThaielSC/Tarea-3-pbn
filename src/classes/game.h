#include "../classes/mazmorra.h"
// #include "../classes/dungeon.h" // TODO: Cambio de nombre
#include "../utils/readcsv.h"
#include <vector>

using namespace std;

class Utils {};

class Game {
private:
  // Dungeon current_dungeon;
  vector<Mazmorra> dungeons;

public:
  Game(string, string);
  void run();
  vector<Mazmorra> get_dungeons();
};
