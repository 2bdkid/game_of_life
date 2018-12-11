#include <unordered_set>
#include <iostream>
#include <vector>
#include <functional>
#include <array>
#include <iterator>
#include <cstddef>
#include <algorithm>
#include <utility>

using Cell = std::pair<int, int>;

namespace std {
  template<>
  struct hash<Cell> {
    std::size_t operator()(const Cell& cell) const {
      const std::hash<int> hasher;
      return hasher(cell.first) & hasher(cell.second);
    }
  };
}

std::ostream& operator<<(std::ostream& out, const Cell& cell) {
  out << '(' << cell.first << ',' << cell.second << ')';
  return out;
}

class Life {
public:
  template<typename InputIt>
  Life(InputIt begin, InputIt end);

  void tick();
  friend std::ostream& operator<<(std::ostream& out, const Life& life);
  
private:
  std::unordered_set<Cell> grid;
  std::array<Cell, 8> neighbors_of(const Cell& cell) const;
  int n_alive_neighbors(const std::array<Cell, 8>& neighbors) const;
};

template<typename InputIt>
Life::Life(InputIt begin, InputIt end)
  : grid(begin, end) {}

void Life::tick() {
  std::vector<Cell> to_die;
  std::vector<Cell> to_create;
  std::vector<Cell> all_neighbors;

  // find cells that will die
  std::copy_if(grid.begin(), grid.end(), std::back_inserter(to_die),
               [&](const auto& cell){
                 const auto neighbors = neighbors_of(cell);
                 const auto alive_neighbors = n_alive_neighbors(neighbors);
                 return alive_neighbors < 2 || alive_neighbors > 3;
               });

  // collect neighbors of all cells
  std::for_each(grid.begin(), grid.end(),
                [&](const auto& cell){
                  const auto neighbors = neighbors_of(cell);
                  std::copy(neighbors.begin(), neighbors.end(), std::back_inserter(all_neighbors));
                });

  // find cells that will be created
  std::copy_if(all_neighbors.begin(), all_neighbors.end(), std::back_inserter(to_create),
               [&](const auto& cell) {
                 if (grid.find(cell) != grid.end()) return false;
                 const auto neighbors = neighbors_of(cell);
                 const auto alive_neighbors = n_alive_neighbors(neighbors);
                 return alive_neighbors == 3;
               });

  // kill cells
  std::for_each(to_die.begin(), to_die.end(), [&](const auto& cell){ grid.erase(cell); });
  // reproduce cells
  grid.insert(to_create.begin(), to_create.end());
}

std::array<Cell, 8> Life::neighbors_of(const Cell& cell) const {
  return { Cell(cell.first - 1, cell.second + 1),
           Cell(cell.first, cell.second + 1),
           Cell(cell.first + 1, cell.second + 1),
           Cell(cell.first + 1, cell.second),
           Cell(cell.first + 1, cell.second - 1),
           Cell(cell.first, cell.second - 1),
           Cell(cell.first - 1, cell.second - 1),
           Cell(cell.first - 1, cell.second) };
}

int Life::n_alive_neighbors(const std::array<Cell, 8>& neighbors) const {
  return std::count_if(neighbors.begin(), neighbors.end(),
                       [&](const auto& cell){ return grid.find(cell) != grid.end(); });
}

std::ostream& operator<<(std::ostream& out, const Life& life) {
  if (life.grid.empty()) return out;
  out << *life.grid.begin();
  std::for_each(std::next(life.grid.begin()), life.grid.end(),
		[&](const auto& cell){ out << '\n' << cell; });
  return out;
}

int main() {
  std::array<Cell, 3> blinker { Cell(-1, 0), Cell(0, 0), Cell(1, 0) };
  std::array<Cell, 6> toad { Cell(0, 0), Cell(1, 0), Cell(2, 0),
			     Cell(1, 1), Cell(2, 1), Cell(3, 1) };

  Life life(toad.begin(), toad.end());

  std::cout << life << '\n';
  for (int i = 0; i < 6; ++i) {
    life.tick();    
    std::cout << '\n' << life << '\n';
  }
}

