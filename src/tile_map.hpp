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
};

#endif
