#include "GameArea.hpp"
#include <iostream>

GameArea::GameArea(unsigned int sx, unsigned int sy, unsigned int mines) {
  this->area =
      std::vector<std::vector<Field>>(sy, std::vector<Field>(sx, Field()));

  this->revealed = 0;
  this->mines = mines;

  std::cout << "Generating new game area with size " << sx << " " << sy
            << std::endl;

  for (int i = 0; i < mines;) {
    unsigned int x = rand() % sx;
    unsigned int y = rand() % sy;

    std::cout << "New mine on " << x << " " << y << std::endl;

    if (this->get(x, y).is_mine())
      continue;

    this->get(x, y).set_mine(true);
    i++;
  }

  for (uint y = 0; y < this->area.size(); y++) {
    for (uint x = 0; x < this->area[y].size(); x++) {
      uint m = this->count_mines(x, y);
      this->get(x, y).set_amount_of_mines(m);
    }
  }
}

Field &GameArea::get(uint x, uint y) {
  if (x >= this->area[0].size() || y >= this->area.size() || y < 0 || x < 0)
    throw 1;
  return this->area[y][x];
}

uint GameArea::count_mines(uint x, uint y) {
  int to_check[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                        {0, 1},   {1, -1}, {1, 0},  {1, 1}};

  uint mines = 0;

  for (auto e : to_check) {
    try {
      mines += this->get(x + e[1], y + e[0]).is_mine();
    } catch (int e) {
    }
  }

  return mines;
}

void GameArea::debug_print() {
  for (uint y = 0; y < this->area.size(); y++) {
    for (uint x = 0; x < this->area[y].size(); x++) {
      auto field = this->get(x, y);

      if (field.is_mine()) {
        std::cout << "M";
      } else if (field.is_flagged()) {
        std::cout << "F";
      } else {
        std::cout << field.get_amount_of_mines();
      }
    }

    std::cout << std::endl;
  }
}

uint GameArea::size_x() { return this->area[0].size(); }

uint GameArea::size_y() { return this->area.size(); }

void GameArea::flag(uint x, uint y) {
  this->get(x, y).set_flagged(!this->get(x, y).is_flagged());
}

void GameArea::reveal_empty(uint x, uint y) {
  this->get(x, y).set_clicked(true);
  this->revealed++;
  int to_check[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                        {0, 1},   {1, -1}, {1, 0},  {1, 1}};

  for (auto e : to_check) {
    try {
      auto field = this->get(x + e[1], y + e[0]);

      if (!field.is_mine() && !field.is_flagged() && !field.is_clicked()) {
        if (field.get_amount_of_mines() == 0) {
          this->reveal_empty(x + e[1], y + e[0]);
        } else {
          this->revealed++;
          this->get(x + e[1], y + e[0]).set_clicked(true);
        }
      }
    } catch (int e) {
    }
  }
}

void GameArea::click(uint x, uint y) {
  if (this->get(x, y).is_flagged())
    return;

  if (this->get(x, y).is_clicked()) {
    this->flagged_click(x, y);

    return;
  }

  if (this->get(x, y).is_mine()) {
    this->reveal();
    return;
  }

  if (this->get(x, y).get_amount_of_mines() == 0) {
    this->reveal_empty(x, y);

    return;
  }

  this->revealed++;
  this->get(x, y).set_clicked(true);
}

void GameArea::reveal() {
  for (auto &x : this->area) {
    for (auto &f : x) {
      f.set_clicked(true);
    }
  }
}

bool GameArea::check_win() {
  if (this->size_x() * this->size_y() - this->mines <= this->revealed) {
    this->reveal();
    return true;
  }

  uint flagged_mines = 0;

  for (auto &x : this->area) {
    for (auto &f : x) {
      if (f.is_flagged() && f.is_mine())
        flagged_mines++;
    }
  }

  if (this->mines <= flagged_mines) {
    this->reveal();
    return true;
  }

  return false;
}

void GameArea::flagged_click(uint x, uint y) {
  uint mines = this->get(x, y).get_amount_of_mines();

  uint flags = 0;

  int to_check[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                        {0, 1},   {1, -1}, {1, 0},  {1, 1}};
  for (auto e : to_check) {
    try {
      std::cout << "Getting b" << x + e[1] << " " << y + e[0] << std::endl;
      flags += this->get(x + e[1], y + e[0]).is_flagged();
    } catch (int e) {
    }
  }

  std::cout << "Flags " << flags << std::endl;

  if (flags == mines) {
    for (auto e : to_check) {
      try {
        std::cout << "Getting bruh " << x + e[1] << " " << y + e[0]
                  << std::endl;

        if (!this->get(x + e[1], y + e[0]).is_clicked()) {
          this->click(x + e[1], y + e[0]);
        }
      } catch (int e) {
      }
    }
  }
}
