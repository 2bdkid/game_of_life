#ifndef GAME_LIFE_HPP
#define GAME_LIFE_HPP

#include <unordered_set>
#include <iostream>
#include <vector>
#include <functional>
#include <array>
#include <iterator>
#include <cstddef>
#include <algorithm>
#include <utility>

#include "Viewport.hpp"

using Cell = std::pair<int, int>;
class Viewport;

namespace std {
  template<>
  struct hash<Cell> {
    std::size_t operator()(const Cell& cell) const {
      const std::hash<int> hasher;
      return hasher(cell.first) & hasher(cell.second);
    }
  };
}

class Life {
public:
  template<typename InputIt>
  Life(InputIt begin, InputIt end)
    : grid(begin, end) {}
  
  void tick();
  Viewport view(Cell top_left, Cell bottom_right) const;
  friend class Viewport;
  friend std::ostream& operator<<(std::ostream& out, const Viewport& view);
  
private:
  std::unordered_set<Cell> grid;
  std::array<Cell, 8> neighbors_of(const Cell& cell) const;
  int n_alive_neighbors(const std::array<Cell, 8>& neighbors) const;
};

#endif
