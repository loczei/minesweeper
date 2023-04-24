#ifndef GAMEAREA_H
#define GAMEAREA_H

#pragma once

#include "Field.hpp"

#include <cstdlib>
#include <vector>

class GameArea {
private:
  std::vector<std::vector<Field>> area;

public:
  GameArea(uint, uint, uint);

  Field &get(uint, uint);
  uint count_mines(uint, uint);
  void debug_print();
  uint size_x();
  uint size_y();
  void click(uint, uint);
  void flag(uint, uint);
  void reveal();
  void reveal_empty(uint, uint);
};

#endif
