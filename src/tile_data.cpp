#include <iterator>
#include "tile_data.hpp"

using namespace std;

TileData& TileData::operator=(const TileData& rhs)
{
  width_ = rhs.width_;
  height_ = rhs.height_;
  copy(rhs.tileTypes_.begin(), rhs.tileTypes_.end(), back_inserter(tileTypes_));

  return *this;
}

TileData::TileData(const TileData& rhs)
{
  width_ = rhs.width_;
  height_ = rhs.height_;
  copy(rhs.tileTypes_.begin(), rhs.tileTypes_.end(), back_inserter(tileTypes_));
}

ostream& operator<<(ostream& os, const TileData& rhs)
{
  os << "TileData { width: " << rhs.width_
     << " height: " << rhs.height_
     << " tileTypes: ";

  copy(rhs.tileTypes_.begin(), rhs.tileTypes_.end(), ostream_iterator<Tile>(os, " "));

  os << " }";

  return os;
}

