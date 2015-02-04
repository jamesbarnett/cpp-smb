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
  tiles_ = vector<vector<Tile>>();

  int x = 0;

  for (vector<vector<int>>::const_iterator it = tileMap_.grid().begin(); it != tileMap_.grid().end(); ++it)
  {
    cout << "Level#initTileGrid: size x: " << it->size() << endl;
    tiles_.push_back(vector<Tile>(it->size()));
    int y = 0;
    for (vector<int>::const_iterator it2 = it->begin(); it2 != it->end(); ++it2)
    {
      // cout << "Level#initTileGrid: size y: " << tiles_[x].size() << endl;

      vector<Tile>::const_iterator tile = find_if(tileTypes.begin(), tileTypes.end(),
        [x,y,this](Tile t) -> bool { return t.id() == tileMap_.grid()[x][y]; });

      if (tile == tileTypes.end())
      {
        stringstream err;
        err << "Failed to find tile: " << tileMap_.grid()[x][y] << "!";
        throw runtime_error(err.str());
      }

      tiles_[x].push_back(*tile);
      ++y;
    }

    ++x;
  }
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

