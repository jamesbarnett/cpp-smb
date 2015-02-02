#include <iostream>
#include "level.hpp"

using namespace std;

Level::Level(const Level& rhs)
{
  id_ = rhs.id_;
  player_ = rhs.player_;
  tileMap_ = rhs.tileMap_;
  tiles_.reserve(rhs.tiles_.size());
  copy(rhs.tiles_.begin(), rhs.tiles_.end(), tiles_.begin());
}

Level& Level::operator=(const Level& rhs)
{
  id_ = rhs.id_;
  player_ = rhs.player_;
  tileMap_ = rhs.tileMap_;
  tiles_.reserve(rhs.tiles_.size());
  copy(rhs.tiles_.begin(), rhs.tiles_.end(), tiles_.begin());

  return *this;
}

ostream& operator<<(ostream& os, const Level& rhs)
{
  os << "Level { id: " << rhs.id_
     << " player: " << rhs.player_
     << " tileMap: " << rhs.tileMap_
     << " tiles: ";

  // copy(rhs.tiles().begin(), rhs.tiles().end(), ostream_iterator<Tile>(os, "\n"));
  os << " } ";

  return os;
}

