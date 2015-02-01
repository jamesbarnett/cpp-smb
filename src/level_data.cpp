#include <iostream>
#include "level_data.hpp"

using namespace std;

LevelData::LevelData(const LevelData& rhs)
{
  id_ = rhs.id_;
  copy(rhs.sounds_.begin(), rhs.sounds_.end(), back_inserter(sounds_));
  tiles_.reserve(rhs.tiles_.size());
  copy(rhs.tiles_.begin(), rhs.tiles_.end(), tiles_.begin());
  levels_.reserve(rhs.levels_.size());
  copy(rhs.levels_.begin(), rhs.levels_.end(), levels_.begin());
  rows_ = rhs.rows_;
  cols_ = rhs.cols_;
  tileWidth_ = rhs.tileWidth_;
  tileHeight_ = rhs.tileHeight_;
  backgroundColor_ = rhs.backgroundColor_;
  tileMap_ = rhs.tileMap_;
}

LevelData& LevelData::operator=(const LevelData& rhs)
{
  id_ = rhs.id_;
  tiles_.reserve(rhs.tiles_.size());
  copy(rhs.tiles_.begin(), rhs.tiles_.end(), tiles_.begin());
  levels_.reserve(rhs.levels_.size());
  copy(rhs.levels_.begin(), rhs.levels_.end(), levels_.begin());
  rows_ = rhs.rows_;
  cols_ = rhs.cols_;
  tileWidth_ = rhs.tileWidth_;
  tileHeight_ = rhs.tileHeight_;
  backgroundColor_ = rhs.backgroundColor_;
  tileMap_ = rhs.tileMap_;

  return *this;
}

ostream& operator<<(ostream& os, const LevelData& rhs)
{
  os << "LevelData { id: " << rhs.id_
     << " rows: " << rhs.rows_
     << " cols: " << rhs.cols_
     << " tileWidth: " << rhs.tileWidth_
     << " tileHeight: " << rhs.tileHeight_
     << " tilemap: " << rhs.tileMap_
     << " }";

  return os;
}

