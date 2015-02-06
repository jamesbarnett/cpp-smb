#include <iostream>
#include <sstream>
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

void Level::initTileGrid(const vector<Tile>& tileTypes)
{
  tiles_.clear();
  tiles_ = vector<vector<Tile>>(tileMap_.grid().size());

  int count = 0;

  cout << "initTileGrid: grid[0].size(): " << tileMap_.grid()[0].size() << endl;

  for (size_t x = 0; x < tileMap_.grid().size(); ++x)
  {
    for (size_t y = 0; y < tileMap_.grid()[0].size(); ++y)
    {
      vector<Tile>::const_iterator tile = find_if(tileTypes.begin(), tileTypes.end(),
        [x,y,this](Tile t) -> bool { return t.id() == tileMap_.grid()[x][y]; });

      if (tile == tileTypes.end())
      {
        stringstream err;
        err << "Failed to find tile: " << tileMap_.grid()[x][y] << "!";
        throw runtime_error(err.str());
      }

      tiles_[x].push_back(*tile);
      ++count;
    }
  }

  cout << "tiles.size(): " << tiles_.size() << endl;
  cout << "tiles[0].size(): " << tiles_[0].size() << endl;
  cout << "Tiles added: " << count << endl;
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

