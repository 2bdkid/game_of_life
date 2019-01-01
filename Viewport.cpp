#include "Viewport.hpp"
#include "Life.hpp"

Viewport::Viewport(const Life& life, Cell top_left, Cell bottom_right)
  : life(life), top_left(top_left), bottom_right(bottom_right) {}

std::ostream& operator<<(std::ostream& out, const Viewport& view) {
  for (int x = view.top_left.first; x <= view.bottom_right.first + 2; ++x) {
    out << '-';
  }

  out << '\n';
  
  for (int y = view.top_left.second; y >= view.bottom_right.second; --y) {
    out << '|';
    for (int x = view.top_left.first; x <= view.bottom_right.first; ++x) {
      if (view.life.alive({x, y}))
	out << 'O';
      else
	out << ' ';
    }
    out << "|\n";
  }

  for (int x = view.top_left.first; x <= view.bottom_right.first + 2; ++x) {
    out << '-';
  }
  
  return out;
}

