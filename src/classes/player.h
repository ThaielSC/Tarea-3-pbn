#include <string>

using namespace std;

class Player {
private:
  class Position {
  public:
    int x;
    int y;
    string direction;

    Position(int, int, string);
  };

  class Stats {
  public:
    int max_health;
    int damage;
    int range;
    int steps;
    int opened_chests;
    int opened_doors;
    int defeated_enemys;

    Stats(int, int, int);
  };

  class Inventory {
  public:
    int keys;
    int boss_key;
    int number_bombs;

    Inventory(int, int, int);
  };

  class State {
  public:
    int health;
    string skill;
    bool taking_damage;
    bool using_skill;

    State(string sk, int hp = 100);
  };

  Position position;
  Stats stats;
  Inventory inventory;
  State state;

public:
  Player(int x = 0, int y = 0, int hp = 100, int dmg = 10, int rng = 1,
         const string &sk = "Escudo", const string &dir = "ABAJO", int k = 0,
         int bk = 0, int nb = 3);

  // Metodos
  void printStatus() const;
  void takeDamage(int amount);
  int getHealth() const;
};
