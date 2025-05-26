#include "read_dungeon_csv.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<Dungeon> leerDungeonsDesdeCSV(const std::string &filePath) {
  std::vector<Dungeon> dungeons;
  std::ifstream file(filePath);
  std::string line;

  if (!file.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo " << filePath << std::endl;
    return dungeons; // Retorna vector vacío
  }

  int lineNum = 0;
  while (std::getline(file, line)) {
    lineNum++;
    if (line.empty() ||
        line.find_first_not_of(" \t\n\v\f\r,") == std::string::npos) {
      // Ignorar líneas vacías o que solo contienen comas/espacios en blanco
      continue;
    }
    std::stringstream ss(line);
    std::string valor;
    Dungeon currentDungeon;

    // Leer dimensiones y mapa de la sala principal
    int mainRoomHeight, mainRoomWidth;
    if (!std::getline(ss, valor, ',')) {
      std::cerr << "Error en línea " << lineNum
                << ": Falta alto de sala principal." << std::endl;
      continue;
    }
    try {
      mainRoomHeight = std::stoi(valor);
    } catch (const std::exception &e) {
      std::cerr << "Error en línea " << lineNum
                << ": alto de sala principal inválido '" << valor << "'. "
                << e.what() << std::endl;
      continue;
    }

    if (!std::getline(ss, valor, ',')) {
      std::cerr << "Error en línea " << lineNum
                << ": Falta ancho de sala principal." << std::endl;
      continue;
    }
    try {
      mainRoomWidth = std::stoi(valor);
    } catch (const std::exception &e) {
      std::cerr << "Error en línea " << lineNum
                << ": ancho de sala principal inválido '" << valor << "'. "
                << e.what() << std::endl;
      continue;
    }

    currentDungeon.mainRoom.resize(mainRoomWidth, mainRoomHeight);

    for (int i = 0; i < mainRoomHeight; ++i) {
      for (int j = 0; j < mainRoomWidth; ++j) {
        if (!std::getline(ss, valor, ',')) {
          std::cerr << "Error en línea " << lineNum
                    << ": Datos insuficientes para mapa de sala principal en ("
                    << i << "," << j << ")." << std::endl;
          goto next_line; // Salir de los bucles anidados para esta línea
        }
        currentDungeon.mainRoom.map[i][j] = valor;
      }
    }

    // Leer dimensiones y mapa de la sala del jefe
    int bossRoomHeight, bossRoomWidth;
    if (!std::getline(ss, valor, ',')) {
      std::cerr << "Error en línea " << lineNum << ": Falta alto de sala jefe."
                << std::endl;
      continue;
    }
    try {
      bossRoomHeight = std::stoi(valor);
    } catch (const std::exception &e) {
      std::cerr << "Error en línea " << lineNum
                << ": alto de sala jefe inválido '" << valor << "'. "
                << e.what() << std::endl;
      continue;
    }

    if (!std::getline(ss, valor, ',')) {
      std::cerr << "Error en línea " << lineNum << ": Falta ancho de sala jefe."
                << std::endl;
      continue;
    }
    try {
      bossRoomWidth = std::stoi(valor);
    } catch (const std::exception &e) {
      std::cerr << "Error en línea " << lineNum
                << ": ancho de sala jefe inválido '" << valor << "'. "
                << e.what() << std::endl;
      continue;
    }

    currentDungeon.bossRoom.resize(bossRoomWidth, bossRoomHeight);

    for (int i = 0; i < bossRoomHeight; ++i) {
      for (int j = 0; j < bossRoomWidth; ++j) {
        if (!std::getline(ss, valor, ',')) {
          std::cerr << "Error en línea " << lineNum
                    << ": Datos insuficientes para mapa de sala jefe en (" << i
                    << "," << j << ")." << std::endl;
          goto next_line; // Salir de los bucles anidados para esta línea
        }
        // Manejar el caso de la última celda que podría no tener coma final
        if (ss.eof() && valor.empty() &&
            (i == bossRoomHeight - 1 && j == bossRoomWidth - 1)) {
          // Si es la última celda y está vacía porque no hay más comas, puede
          // ser un error en el CSV. Pero si `valor` tiene contenido, está bien.
          // Si `getline` falla y `valor` está vacío, indica un problema.
        }
        currentDungeon.bossRoom.map[i][j] = valor;
      }
    }
    dungeons.push_back(currentDungeon);
  next_line:;
  }
  file.close();
  return dungeons;
}
