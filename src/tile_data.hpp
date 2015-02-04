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

public:
  TileData() {}
  TileData(const TileData&);

  inline void width(int val) { width_ = val; }
  inline int width() const { return width_; }

  inline void height(int val) { height_ = val; }
  inline int height() const { return height_; }

  void addTile(const Tile& tile)
  {
    tileTypes_.push_back(tile);
  }

  const std::vector<Tile>& tileTypes() const { return tileTypes_; }

  TileData& operator=(const TileData&);
  friend std::ostream& operator<<(std::ostream&, const TileData&);
};

std::ostream& operator<<(std::ostream&, const TileData&);

#endif

