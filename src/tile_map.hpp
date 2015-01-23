#ifndef TILE_MAP_HPP__
#define TILE_MAP_HPP__

#include <iostream>

using namespace std;

class TileMap
{
private:
  int rows_;
  int cols_;
  string bgcolor_;
  vector<vector<int>> grid_;

public:
  TileMap() { }
  TileMap(int rows, int cols, string bgcolor, vector<vector<int>> grid) : rows_(rows)
    , cols_(cols)
    , bgcolor_(bgcolor)
    , grid_(grid) {}

  friend ostream& operator<<(ostream&, const TileMap&);
};

ostream& operator<<(ostream& os, const TileMap& rhs)
{
  os << "TileMap { rows: " << rhs.rows_
     << " cols: " << rhs.cols_
     << " bgcolor: " << rhs.bgcolor_ << " grid: ";

  for(auto el : rhs.grid_)
  {
    copy(el.begin(), el.end(), ostream_iterator<int>(os, " "));
  }

  os << " }";

  return os;
}

#endif
