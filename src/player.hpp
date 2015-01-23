#ifndef PLAYER_HPP__
#define PLAYER_HPP__

#include <iostream>

using namespace std;

class Player
{
private:
  int startRow_;
  int startCol_;
  string facing_;

public:
  Player(int startRow, int startCol, string facing) : startRow_(startRow)
    , startCol_(startCol)
    , facing_(facing) {}

  friend ostream& operator<<(ostream&, const Player&);
};

ostream& operator<<(ostream& os, const Player& rhs)
{
  os << "Player { startRow: " << rhs.startRow_
     << ", startCol: " << rhs.startCol_
     << ", facing: " << rhs.facing_
     << " }";

  return os;
}

#endif
