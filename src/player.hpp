#ifndef PLAYER_HPP__
#define PLAYER_HPP__

#include <iostream>
#include "direction.hpp"

using namespace std;

class Player
{
private:
  int startRow_;
  int startCol_;
  Direction facing_;

public:
  Player() : startRow_(10), startCol_(4), facing_(Direction::RIGHT) {}
  Player(int startRow, int startCol, Direction facing) : startRow_(startRow)
    , startCol_(startCol)
    , facing_(facing) {}

  friend ostream& operator<<(ostream&, const Player&);
};

ostream& operator<<(ostream& os, const Player& rhs);

#endif

