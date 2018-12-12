#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <iostream>
#include <utility>

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
