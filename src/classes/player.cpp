#include "player.h"
#include <iostream>
#include <string>
using namespace std;

// Subclass constructors
Player::Position::Position(int x, int y, std::string dir)
    : x(x), y(y), direction(dir) {}

Player::Stats::Stats(int m_hp, int dmg, int rng)
    : max_health(m_hp), damage(dmg), range(rng), steps(0), opened_chests(0),
      opened_doors(0), defeated_enemys(0) {}

Player::Inventory::Inventory(int k, int bk, int nb)
    : keys(k), boss_key(bk), number_bombs(nb) {}

Player::State::State(string sk, int hp)
    : health(hp), skill(sk), taking_damage(false), using_skill(false) {}

// Player constructor
Player::Player(int x, int y, int hp, int dmg, int rng, const string &sk,
               const string &dir, int k, int bk, int nb)
    : position(x, y, dir), stats(hp, dmg, rng), inventory(k, bk, nb),
      state(sk, hp) {}

void Player::printStatus() const {
  std::cout << "=== Estado del Jugador ===" << std::endl;
  std::cout << "Health: " << state.health << std::endl;
  std::cout << "Position{ x: " << position.x << ", y: " << position.y
            << "}\nDirection: " << position.direction << std::endl;
}

void Player::takeDamage(int amount) {
  state.health -= amount;
  state.taking_damage = true;
  if (state.health < 0)
    state.health = 0;
}

int Player::getHealth() const { return state.health; }
