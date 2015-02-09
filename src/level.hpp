#ifndef LEVEL_HPP__
#define LEVEL_HPP__

#include <iostream>
#include <cassert>
#include "player.hpp"
#include "tile_map.hpp"
#include "tile.hpp"

class Level
{
private:
  int id_;
  Player player_;
  TileMap tileMap_;
  std::vector<std::vector<Tile>> tiles_;

public:
  Level() {}
  Level(int id, const Player& player, const TileMap& tileMap)
    : id_(id)
    , player_(player)
    , tileMap_(tileMap) {}

  Level(const Level&);

  int id() const { return id_; }
  void id(int val) { id_ = val; }

  Player player() const { return player_; }
  void player(const Player& val) { player_ = val; }

  TileMap tileMap() const { return tileMap_; }
  void tileMap(const TileMap& val) { tileMap_ = val; }

  int cols() { return tileMap_.cols(); }
  int rows() { return tileMap_.rows(); }

  std::vector<std::vector<Tile>>& tiles() { return tiles_; }

  void initTileGrid(const std::vector<Tile>& tileTypes);

  inline Tile tiles(int x, int y) const
  {
    return tiles_[x][y];
  }

  inline void tiles(int x, int y, const Tile& tile)
  {
    tiles_[x][y] = tile;
  }

  inline const vector<vector<Tile>>& tiles() const { return tiles_; }

  Level& operator=(const Level&);
  friend std::ostream& operator<<(std::ostream&, const Level&);
};

std::ostream& operator<<(std::ostream&, const Level&);

#endif

