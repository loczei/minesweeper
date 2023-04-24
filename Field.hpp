#ifndef FIELD_H
#define FIELD_H

class Field {
private:
  bool mine;
  unsigned int mines_amount;
  bool clicked;
  bool flagged;

public:
  Field();

  bool is_clicked();
  bool is_mine();
  void set_mine(bool);
  void set_amount_of_mines(unsigned int);
  unsigned int get_amount_of_mines();
  void set_flagged(bool);
  bool is_flagged();
  void set_clicked(bool);
};

#endif
