#include "mazmorra.h"
#include "menu.h"
#include <iostream>
#include <vector>

Menu::Menu(string dungeong__path, string enemys_path)
    : game(dungeong__path, enemys_path) {
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
         \==\  / \ / / ///      /|\| |_____/| | |_____/| | |_/ /   | |   | |
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
  system("clear");
  cout << startDisplay << endl;
  cout << " >> Presiona enter  para empezar" << endl;
  cin.ignore();
  system("clear");
}

Mazmorra Menu::select_dungeon() {
  vector<Mazmorra> dungeons = game.get_dungeons();
  auto dungeon = dungeons.begin();
  char opcion;

  while (true) {
    system("clear");
    cout << "=== Mazmorra seleccionada ===" << endl;
    dungeon->mostrar();

    cout << "\nUsa [a] <-  [d] ->  [s] seleccionar\n";
    cin >> opcion;

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
}

void Menu::run() {
  start();
  Mazmorra selected_dungeon = select_dungeon();
  game.run();
}
