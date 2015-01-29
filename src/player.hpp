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
  // Mimic the xml file to make Player default constructible for now
  Player() : startRow_(10), startCol_(4), facing_("right") {}
  Player(int startRow, int startCol, string facing) : startRow_(startRow)
    , startCol_(startCol)
    , facing_(facing) {}

  friend ostream& operator<<(ostream&, const Player&);
};

ostream& operator<<(ostream& os, const Player& rhs);

#endif

