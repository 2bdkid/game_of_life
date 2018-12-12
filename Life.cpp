#include "Life.hpp"

Viewport Life::view(Cell top_left, Cell bottom_right) const {
  return { *this, top_left, bottom_right };
}

void Life::tick() {
  std::vector<Cell> to_die;
  std::vector<Cell> to_create;

  // find cells that will die
  std::copy_if(grid.begin(), grid.end(), std::back_inserter(to_die),
               [this](const auto& cell){
                 const auto neighbors = neighbors_of(cell);
                 const auto alive_neighbors = n_alive_neighbors(neighbors);
                 return alive_neighbors < 2 || alive_neighbors > 3;
               });

  // find cell that will reproduce
  for (const auto& cell : grid) {
    const auto neighbors = neighbors_of(cell);
    for (const auto& neighbor : neighbors) {
      if (grid.find(neighbor) != grid.end()) continue;
      const auto neighbor_neighbors = neighbors_of(neighbor);
      const auto alive_neighbors = n_alive_neighbors(neighbor_neighbors);
      if (alive_neighbors == 3)
        to_create.push_back(neighbor);
    }
  }

  // kill cells
  for (const auto& cell : to_die)
    grid.erase(cell);

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
                       [this](const auto& cell){ return grid.find(cell) != grid.end(); });
}

