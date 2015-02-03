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
  inline void rows(int val) { rows_ = val; }

  inline int cols() const { return cols_; }
  inline void cols(int val) { cols_ = val; }

  inline std::string bgcolor() const { return bgcolor_; }
  inline void bgcolor(std::string val) { bgcolor_ = val; }

  std::vector<std::vector<int>>& grid() { return grid_; }

  void addRow(const std::vector<int>& row)
  {
    grid_.push_back(row);
  }

  TileMap& operator=(const TileMap&);
  friend std::ostream& operator<<(std::ostream&, const TileMap&);
};

std::ostream& operator<<(std::ostream&, const TileMap&);

#endif

