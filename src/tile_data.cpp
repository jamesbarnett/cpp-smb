#include "tile_data.hpp"

using namespace std;

ostream& operator<<(ostream& os, const TileData& rhs)
{
  os << "TileData { width: " << rhs.width_
     << " height: " << rhs.height_
     << " tileTypes: ";

  copy(rhs.tileTypes_.begin(), rhs.tileTypes_.end(), ostream_iterator<Tile>(os, " "));

  os << " }";

  return os;
}

