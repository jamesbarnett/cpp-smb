#ifndef LEVEL_HPP__
#define LEVEL_HPP__

#include <iostream>
#include "player.hpp"
#include "tile_map.hpp"

class Level
{
private:
  int id_;
  Player player_;
  TileMap tileMap_;

public:
  Level() {}
  Level(int id, const Player& player, const TileMap& tileMap) 
    : id_(id)
    , player_(player)
    , tileMap_(tileMap) {}

  int id() const { return id_; }
  void id(int val) { id_ = val; }
  Player player() const { return player_; }
  void player(const Player& val) { player_ = val; }
  TileMap tileMap() const { return tileMap_; }
  void tileMap(const TileMap& val) { tileMap_ = val; }
  friend ostream& operator<<(ostream&, const Level&);
};

ostream& operator<<(ostream& os, const Level& rhs)
{
  os << "Level { id: " << rhs.id_
     << " player: " << rhs.player_
     << " tileMap: " << rhs.tileMap_
     << " } ";

  return os;
}

#endif

