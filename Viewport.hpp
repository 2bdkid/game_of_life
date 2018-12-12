#ifndef LIFE_VIEWPORT_HPP
#define LIFE_VIEWPORT_HPP

#include "Life.hpp"

class Life;
using Cell = std::pair<int, int>;

class Viewport {
public:
  Viewport(const Life& life, Cell top_left, Cell bottom_right);
  friend std::ostream& operator<<(std::ostream& out, const Viewport& view);
  
private:
  const Life& life;
  Cell top_left;
  Cell bottom_right;
};

#endif
