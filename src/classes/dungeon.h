#include <string>
#include <vector>

class Dungeon {
private:
  using mapRow = std::vector<std::string>;
  using StringMap = std::vector<mapRow>;

  struct Room {
    struct Size {
      int width;
      int height;
    };
    Size size;
    StringMap map;

    Room(int w = 10, int h = 10) : size{w, h}, map(h, mapRow(w, ".")) {}
  };

  Room mainRoom;
  Room bossRoom;

public:
  Dungeon();
  void show();
};
