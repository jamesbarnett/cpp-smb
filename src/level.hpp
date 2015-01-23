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
  Level(int id, const Player& player, const TileMap& tileMap) 
    : id_(id)
    , player_(player)
    , tileMap_(tileMap) {}

  void print()
  {
    cout << "Level { id: " << id_;
    player_.print();
    cout << " }" << endl;
  }
};

#endif

