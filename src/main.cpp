#include "classes/menu.h"
#include <iostream>

int main() {
  try {
  Menu mainMenu = Menu("data/mazmorras.csv", "data/enemigos.csv");
  mainMenu.run();
    return 0;
  } catch (const std::exception& e) {
    std::cerr << "Error fatal: " << e.what() << std::endl;
    return 1;
  }
}
