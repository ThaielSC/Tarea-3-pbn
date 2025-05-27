#include "classes/menu.h"

int main() {
  Menu mainMenu = Menu("data/mazmorras.csv", "data/enemigos.csv");
  mainMenu.run();
}
