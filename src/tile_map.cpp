#include <iostream>
#include <vector>
#include "tile_map.hpp"

using namespace std;

TileMap::TileMap(const TileMap& rhs)
{
  rows_ = rhs.rows_;
  cols_ = rhs.cols_;
  bgcolor_ = rhs.bgcolor_;

  for (size_t i = 0; i < rhs.grid_.size(); ++i)
  {
    grid_.push_back(std::vector<int>(rhs.grid_.size()));

    for (size_t j = 0; j < rhs.grid_[i].size(); ++j)
    {
      grid_[i].push_back(rhs.grid_[i][j]);
    }
  }
}

TileMap& TileMap::operator=(const TileMap& rhs)
{
  rows_ = rhs.rows_;
  cols_ = rhs.cols_;
  bgcolor_ = rhs.bgcolor_;

  for (size_t i = 0; i < rhs.grid_.size(); ++i)
  {
    grid_.push_back(std::vector<int>(rhs.grid_.size()));

    for (size_t j = 0; j < rhs.grid_[i].size(); ++j)
    {
      grid_[i].push_back(rhs.grid_[i][j]);
    }
  }

  return *this;
}

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

