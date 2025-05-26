#include "../src/classes/player.h"
#include <iostream>

int tests_passed = 0;
int tests_failed = 0;

void assertEqual(int actual, int expected, const std::string &testName) {
  if (actual == expected) {
    std::cout << "[OK] " << testName << std::endl;
    tests_passed++;
  } else {
    std::cout << "[FAIL] " << testName << ": expected " << expected << ", got "
              << actual << std::endl;
    tests_failed++;
  }
}

int main() {
  std::cout << "=== Ejecutando tests para Player ===" << std::endl;

  Player player;

  // Test de salud inicial
  assertEqual(player.getHealth(), 100, "Salud inicial del jugador");

  // Simular daño
  player.takeDamage(30);
  assertEqual(player.getHealth(), 70, "Salud después de 30 de daño");

  // Más daño
  player.takeDamage(80);
  assertEqual(player.getHealth(), 0, "Salud no debe ser negativa");

  // Mostrar estado completo
  // player.printStatus();

  std::cout << "\n===> Tests pasados: " << tests_passed
            << ", fallados: " << tests_failed << std::endl;

  return tests_failed == 0 ? 0 : 1;
}
