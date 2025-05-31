#include "mazmorra.h"
#include "menu.h"
#include "game.h"
#include "jugador.h"
#include <iostream>
#include <vector>
#include "../utils/readcsv.h"

Menu::Menu(string dungeon_path, string enemys_path)
    : game(dungeon_path, enemys_path) {
  startDisplay = R"(
                                       /@
                       __        __   /\/
                      /==\      /  \_/\/   
                    /======\    \/\__ \__
                  /==/\  /\==\    /\_|__ \
               /==/    ||    \=\ / / / /_/
             /=/    /\ || /\   \=\/ /     
          /===/   /   \||/   \   \===\
        /===/   /_________________ \===\
     /====/   / |                /  \====\
   /====/   /   |  _________    /  \   \===\    THE LEGEND OF 
   /==/   /     | /   /  \ / / /  __________\_____      ______       ___
  |===| /       |/   /____/ / /   \   _____ |\   /      \   _ \      \  \
   \==\             /\   / / /     | |  /= \| | |        | | \ \     / _ \
   \===\__    \    /  \ / / /   /  | | /===/  | |        | |  \ \   / / \ \
     \==\ \    \\ /____/   /_\ //  | |_____/| | |        | |   | | / /___\ \
     \===\ \   \\\\\\\/   /////// /|  _____ | | |        | |   | | |  ___  |
       \==\/     \\\\/ / //////   \| |/==/ \| | |        | |   | | | /   \ |
       \==\     _ \\/ / /////    _ | |==/     | |        | |  / /  | |   | |
         \==\  / \ / / ///      /|\| |_____/| | |        | |_/ /   | |   | |
         \==\ /   / / /________/ |/_________|/_________|/_____/   /___\ /___\
           \==\  /               | /==/
           \=\  /________________|/=/    
             \==\     _____     /==/ 
            / \===\   \   /   /===/
           / / /\===\  \_/  /===/
          / / /   \====\ /====/
         / / /      \===|===/
         |/_/         \===/
                        =
                      )";
}

void Menu::start() {
  try {
    system("clear");  // Limpia la pantalla antes de mostrar el menú
    cout << startDisplay << endl;
    cout << " >> Presiona enter para empezar" << endl;
    cin.ignore();
    system("clear");  // Limpia la pantalla antes de mostrar el juego
  } catch (const exception& e) {
    cerr << "Error al iniciar el menú: " << e.what() << endl;
    throw;
  }
}

Mazmorra Menu::select_dungeon() {
  try {
    vector<Mazmorra> dungeons = game.get_dungeons();
    if (dungeons.empty()) {
      throw runtime_error("No hay mazmorras disponibles para seleccionar");
    }

    auto dungeon = dungeons.begin();
    char opcion;

    while (true) {
      system("clear"); 
      cout << "=== Mazmorra seleccionada ===" << endl;
      dungeon->mostrar();

      mostrarEnemigos(*dungeon);

      cout << "\nUsa [a] <-  [d] ->  [s] seleccionar\n";
      if (!(cin >> opcion)) {
        cin.clear();
        cin.ignore(10000, '\n');
        continue;
      }

      if (opcion == 'd') {
        if ((dungeon + 1) != dungeons.end()) {
          ++dungeon;
        }
      } else if (opcion == 'a') {
        if (dungeon != dungeons.begin()) {
          --dungeon;
        }
      } else if (opcion == 's') {
        break;
      }
    }

    Mazmorra seleccionada = *dungeon;
    seleccionada.mostrar();
    return seleccionada;
  } catch (const exception& e) {
    cerr << "Error al seleccionar mazmorra: " << e.what() << endl;
    throw;
  }
}

void Menu::run() {
  start();
  Mazmorra selected_dungeon = select_dungeon();
  
  // Crear jugador 
  Jugador jugador = Jugador::crearDesdeMapaMazmorra(selected_dungeon);
  jugador.setMazmorra(&selected_dungeon);
  
  // Crear y ejecutar el juego
  Game game(&selected_dungeon, &jugador);
  game.run();
}
