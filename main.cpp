#include <iostream>
#include <array>
#include <thread>
#include <chrono>

#include "Life.hpp"
#include "Cell.hpp"

int main() {
  std::array<Cell, 10> seed { Cell(0, 0), Cell(2, 0), Cell(2, 1), Cell(4, 2), Cell(4, 3),
			      Cell(4, 4), Cell(6, 3), Cell(6, 4), Cell(6, 5), Cell(7, 4) };
  
  Life life(seed.begin(), seed.end());
  Cell tl(-50, 20);
  Cell br(50, -20);
  
  std::cout << life.view(tl, br) << '\n';
  while (life.has_living_cells()) {
    life.tick();    
    std::cout << '\n' << life.view(tl, br) << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
}

