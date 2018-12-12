#include <iostream>
#include <array>

#include "Life.hpp"

int main() {
  std::array<Cell, 3> blinker { Cell(-1, 0), Cell(0, 0), Cell(1, 0) };
  std::array<Cell, 6> toad { Cell(0, 0), Cell(1, 0), Cell(2, 0),
                             Cell(1, 1), Cell(2, 1), Cell(3, 1) };
  std::array<Cell, 10> seed { Cell(0, 0), Cell(0, -1), Cell(0, -2),
			      Cell(1, 0), Cell(1, -2), Cell(2, -2),
			      Cell(3, -1), Cell(3, -1), Cell(4, -1),
			      Cell(4, 0) };
			    

  Life life(seed.begin(), seed.end());
  Cell tl(-5, 5);
  Cell br(5, -5);

  std::cout << life.view(tl, br) << '\n';
  while (life.has_living_cells()) {
    life.tick();    
    std::cout << '\n' << life.view(tl, br) << '\n';
  }
}

