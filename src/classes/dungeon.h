// src/classes/dungeon.h
#ifndef DUNGEON_H
#define DUNGEON_H

#include <iostream> // Añadido para Dungeon::show()
#include <string>
#include <vector>

class Dungeon {
public: // Es buena práctica declarar el tipo Room como público si se usa fuera
        // o en constructores parametrizados.
  using mapRow = std::vector<std::string>;
  using StringMap = std::vector<mapRow>;

  struct Room {
    struct Size {
      int width;
      int height;
    };
    Size size;
    StringMap map;

    // Constructor para Room, inicializa con dimensiones y un carácter por
    // defecto
    Room(int w = 0, int h = 0, const std::string &default_char = ".")
        : size{w, h}, map(h, mapRow(w, default_char)) {}

    void resize(int w, int h, const std::string &default_char = ".") {
      size.width = w;
      size.height = h;
      map.assign(h, mapRow(w, default_char));
    }
  };

  Room mainRoom;
  Room bossRoom;

public:
  Dungeon(); // Constructor por defecto
  // Constructor para inicializar con datos específicos (opcional, pero útil)
  Dungeon(const Room &mainR, const Room &bossR);

  void show() const; // Declaración del método show
};

#endif // DUNGEON_H
