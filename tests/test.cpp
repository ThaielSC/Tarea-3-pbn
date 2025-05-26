// src/test_dungeon.cpp
#include "../src/classes/dungeon.h"        // Ajusta la ruta si es necesario
#include "../src/utils/read_dungeon_csv.h" // Ajusta la ruta si es necesario
#include <cassert>                         // Para las aserciones
#include <iostream>
#include <vector>

void run_dungeon_tests() {
  std::cout << "--- Iniciando Pruebas para la Clase Dungeon ---" << std::endl;

  // Prueba de carga de Dungeons desde CSV
  std::cout << "\n[TEST] Cargando Dungeons desde data/mazmorras.csv..."
            << std::endl;
  std::vector<Dungeon> dungeons = leerDungeonsDesdeCSV("data/mazmorras.csv"); //

  // Verificar que se cargaron dungeons
  // El archivo data/mazmorras.csv tiene 3 líneas/dungeons
  assert(!dungeons.empty() && "Error: No se cargaron dungeons o el archivo CSV "
                              "está vacío/mal formateado.");
  assert(dungeons.size() == 3 &&
         "Error: El número de dungeons cargados no es 3.");
  std::cout << "  PASSED: Se cargaron " << dungeons.size() << " dungeons."
            << std::endl;

  if (dungeons.size() >= 1) {
    const Dungeon &d1 = dungeons[0];
    std::cout << "\n[TEST] Verificando Dungeon 1 (primera línea del CSV):"
              << std::endl;

    // Dimensiones de la sala principal (según data/mazmorras.csv: 15,4,...)
    // Interpretación: Alto=15, Ancho=4
    assert(d1.mainRoom.size.height == 15 &&
           "Error: Dungeon 1 - Alto de sala principal incorrecto.");
    assert(d1.mainRoom.size.width == 4 &&
           "Error: Dungeon 1 - Ancho de sala principal incorrecto.");
    std::cout << "  PASSED: Dimensiones sala principal (Alto: "
              << d1.mainRoom.size.height
              << ", Ancho: " << d1.mainRoom.size.width << ")" << std::endl;

    // Verificar que el tamaño del vector del mapa coincida
    assert(static_cast<int>(d1.mainRoom.map.size()) ==
               d1.mainRoom.size.height &&
           "Error: Discrepancia en filas del mapa principal.");
    if (d1.mainRoom.size.height > 0) {
      assert(static_cast<int>(d1.mainRoom.map[0].size()) ==
                 d1.mainRoom.size.width &&
             "Error: Discrepancia en columnas del mapa principal.");
    }
    std::cout
        << "  PASSED: Consistencia de tamaño del vector del mapa principal."
        << std::endl;

    // Celdas específicas de la sala principal (Dungeon 1)
    // Recordar: map[fila][columna] -> map[y][x]
    // Fila 0, Col 0 (primera celda): "X"
    // Fila 1, Col 1 (X,L,-,X): "L"
    // Fila 14, Col 3 (última celda del mapa principal: X,X,X,X): "X"
    if (d1.mainRoom.size.height == 15 && d1.mainRoom.size.width == 4) {
      assert(d1.mainRoom.map[0][0] == "X" &&
             "Error: Celda (0,0) sala principal incorrecta.");
      assert(d1.mainRoom.map[1][1] == "L" &&
             "Error: Celda (1,1) sala principal incorrecta.");
      assert(d1.mainRoom.map[14][3] == "X" &&
             "Error: Celda (14,3) sala principal incorrecta.");
      std::cout
          << "  PASSED: Verificación de celdas específicas sala principal."
          << std::endl;
    }

    // Dimensiones de la sala del jefe (según data/mazmorras.csv, parte de la
    // primera línea: ...,6,6,...) Interpretación: Alto=6, Ancho=6
    assert(d1.bossRoom.size.height == 6 &&
           "Error: Dungeon 1 - Alto de sala jefe incorrecto.");
    assert(d1.bossRoom.size.width == 6 &&
           "Error: Dungeon 1 - Ancho de sala jefe incorrecto.");
    std::cout << "  PASSED: Dimensiones sala jefe (Alto: "
              << d1.bossRoom.size.height
              << ", Ancho: " << d1.bossRoom.size.width << ")" << std::endl;

    assert(static_cast<int>(d1.bossRoom.map.size()) ==
               d1.bossRoom.size.height &&
           "Error: Discrepancia en filas del mapa jefe.");
    if (d1.bossRoom.size.height > 0) {
      assert(static_cast<int>(d1.bossRoom.map[0].size()) ==
                 d1.bossRoom.size.width &&
             "Error: Discrepancia en columnas del mapa jefe.");
    }
    std::cout << "  PASSED: Consistencia de tamaño del vector del mapa de jefe."
              << std::endl;

    // Celdas específicas de la sala del jefe (Dungeon 1)
    // Fila 1, Col 2 (X,X,L,-,X,X): "L"
    // Fila 3, Col 3 (X,-,-,J,-,X): "J"
    if (d1.bossRoom.size.height == 6 && d1.bossRoom.size.width == 6) {
      assert(d1.bossRoom.map[1][2] == "L" &&
             "Error: Celda (1,2) sala jefe incorrecta.");
      assert(d1.bossRoom.map[3][3] == "J" &&
             "Error: Celda (3,3) sala jefe incorrecta.");
      std::cout << "  PASSED: Verificación de celdas específicas sala jefe."
                << std::endl;
    }

    // Prueba del método show() (inspección visual)
    std::cout << "\n[TEST] Mostrando Dungeon 1 (inspección visual requerida):"
              << std::endl;
    d1.show();
  }

  if (dungeons.size() >= 2) {
    const Dungeon &d2 = dungeons[1];
    std::cout << "\n[TEST] Verificando Dungeon 2 (segunda línea del CSV):"
              << std::endl;
    // data/mazmorras.csv segunda línea: 5,30,... -> H=5, W=30
    assert(d2.mainRoom.size.height == 5 &&
           "Error: Dungeon 2 - Alto de sala principal incorrecto.");
    assert(d2.mainRoom.size.width == 30 &&
           "Error: Dungeon 2 - Ancho de sala principal incorrecto.");
    std::cout << "  PASSED: Dimensiones sala principal (Alto: "
              << d2.mainRoom.size.height
              << ", Ancho: " << d2.mainRoom.size.width << ")" << std::endl;
    // ... (más aserciones para d2 si es necesario) ...
    std::cout << "\n[TEST] Mostrando Dungeon 2 (inspección visual requerida):"
              << std::endl;
    d2.show();
  }

  std::cout << "\n--- Pruebas para la Clase Dungeon Finalizadas ---"
            << std::endl;
}

// Puedes hacer que tu main.cpp llame a esta función,
// o compilar este archivo por separado para pruebas.
// Por ejemplo, si quieres un ejecutable solo para pruebas:

int main() {
  run_dungeon_tests();
  return 0;
}
