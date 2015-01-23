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

  void print()
  {
    cout << "Player { startRow: " << startRow_
         << ", startCol: " << startCol_
         << ", facing: " << facing_
         << " }" << endl;
  }
};

#endif
