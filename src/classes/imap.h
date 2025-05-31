#include <cstdio>
class IMap {
public:
  virtual void update(int oldx, int oldy, int newx, int newy, char symbol) noexcept = 0;
  void show() { printf("hello"); }
  virtual ~IMap() = default;
};
