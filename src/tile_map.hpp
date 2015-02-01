#ifndef TILE_MAP_HPP__
#define TILE_MAP_HPP__

#include <iostream>
#include <vector>

class TileMap
{
private:
  int rows_;
  int cols_;
  std::string bgcolor_;
  std::vector<std::vector<int>> grid_;

public:
  TileMap() : rows_(0), cols_(0), bgcolor_("")
    , grid_(std::vector<std::vector<int>>()) {}

  TileMap(int rows, int cols, const std::string& bgcolor,
      std::vector<std::vector<int>> grid) : rows_(rows)
    , cols_(cols)
    , bgcolor_(bgcolor)
    , grid_(grid)
  {
  }

  TileMap(const TileMap&);

  inline int rows() const { return rows_; }
  inline int cols() const { return cols_; }
  std::vector<std::vector<int>>& grid() { return grid_; }

  TileMap& operator=(const TileMap&);
  friend std::ostream& operator<<(std::ostream&, const TileMap&);
};

std::ostream& operator<<(std::ostream&, const TileMap&);

#endif

