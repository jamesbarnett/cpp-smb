#ifndef TILE_DATA_HPP__
#define TILE_DATA_HPP__

#include <iostream>
#include <vector>
#include "tile.hpp"

class TileData
{
private:
  int width_;
  int height_;
  std::vector<Tile> tileTypes_;
  std::vector<std::vector<Tile>> tileGrid_;

public:
  inline void width(int val) { width_ = val; }
  inline int width() const { return width_; }

  inline void height(int val) { height_ = val; }
  inline int height() const { return height_; }

  inline Tile tile(int x, int y) const { return tileGrid_[x][y]; }
  inline void tile(int x, int y, const Tile& tile) { tileGrid_[x][y] = tile; }

  void addTile(const Tile& tile)
  {
    // if (find(tileTypes_.begin(), tileTypes_.end(), tile) == tileTypes_.end())
    // {
      tileTypes_.push_back(tile);
    // }
  }

  friend std::ostream& operator<<(std::ostream&, const TileData&);
};

std::ostream& operator<<(std::ostream&, const TileData&);

#endif

