#include <iostream>
#include <vector>
#include "tile_map.hpp"

std::ostream& operator<<(std::ostream& os, const TileMap& rhs)
{
  os << "TileMap { rows: " << rhs.rows_
     << " cols: " << rhs.cols_
     << " bgcolor: " << rhs.bgcolor_ << " grid: ";

  for(auto el : rhs.grid_)
  {
    std::copy(el.begin(), el.end(), std::ostream_iterator<int>(os, " "));
  }

  os << " }";

  return os;
}

