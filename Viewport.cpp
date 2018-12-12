#include "Viewport.hpp"

Viewport::Viewport(const Life& life, Cell top_left, Cell bottom_right)
  : life(life), top_left(top_left), bottom_right(bottom_right) {}

std::ostream& operator<<(std::ostream& out, const Viewport& view) {
  for (int y = view.top_left.second; y >= view.bottom_right.second; --y) {
    for (int x = view.top_left.first; x <= view.bottom_right.first; ++x) {
      Cell cord(x, y);
      if (view.life.grid.find(cord) != view.life.grid.end())
	out << 'O';
      else
	out << ' ';
    }
    out << '\n';
  }
  return out;
}

