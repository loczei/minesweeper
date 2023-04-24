#include "Field.hpp"
#include "GameArea.hpp"

Field::Field() {
  this->mine = false;
  this->mines_amount = 0;
  this->clicked = false;
  this->flagged = false;
}

bool Field::is_clicked() { return this->clicked; }
bool Field::is_mine() { return this->mine; }
void Field::set_mine(bool is) { this->mine = is; }
void Field::set_amount_of_mines(unsigned int amount) {
  this->mines_amount = amount;
}
uint Field::get_amount_of_mines() { return this->mines_amount; }
void Field::set_flagged(bool is) { this->flagged = is; }
bool Field::is_flagged() { return this->flagged; }
void Field::set_clicked(bool is) { this->clicked = is; }
