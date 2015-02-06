#include <iostream>
#include <vector>
#include "tile_map.hpp"

using namespace std;

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

