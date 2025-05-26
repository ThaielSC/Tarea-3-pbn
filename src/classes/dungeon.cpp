#include "dungeon.h"
#include <iostream>

Dungeon::Dungeon() : mainRoom(), bossRoom() {}

// Constructor para inicializar con datos específicos
Dungeon::Dungeon(const Room &mainR, const Room &bossR)
    : mainRoom(mainR), bossRoom(bossR) {}

void Dungeon::show() const {
  std::cout << "Main Room (" << mainRoom.size.height << "x"
            << mainRoom.size.width << "):" << std::endl;
  for (int i = 0; i < mainRoom.size.height; ++i) {
    for (int j = 0; j < mainRoom.size.width; ++j) {
      // Asegurarse de no acceder fuera de los límites si el mapa no está
      // completamente lleno
      if (i < static_cast<int>(mainRoom.map.size()) &&
          j < static_cast<int>(mainRoom.map[i].size())) {
        std::cout << mainRoom.map[i][j];
      } else {
        std::cout
            << "?"; // Carácter para celdas no inicializadas/fuera de rango
      }
      if (j < mainRoom.size.width - 1) {
        std::cout << " "; // Espacio entre celdas para mejor visualización
      }
    }
    std::cout << std::endl;
  }

  std::cout << "\nBoss Room (" << bossRoom.size.height << "x"
            << bossRoom.size.width << "):" << std::endl;
  for (int i = 0; i < bossRoom.size.height; ++i) {
    for (int j = 0; j < bossRoom.size.width; ++j) {
      if (i < static_cast<int>(bossRoom.map.size()) &&
          j < static_cast<int>(bossRoom.map[i].size())) {
        std::cout << bossRoom.map[i][j];
      } else {
        std::cout << "?";
      }
      if (j < bossRoom.size.width - 1) {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << "======================\n" << std::endl;
}
