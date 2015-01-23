#ifndef LEVEL_DATA_HPP__
#define LEVEL_DATA_HPP__

#include <iostream>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "sound.hpp"
#include "tile.hpp"
#include "level.hpp"
#include "tile_map.hpp"

using namespace std;

class LevelData
{
private:
  vector<Sound> sounds_;
  vector<Tile> tiles_;
  vector<Level> levels_;
  int id_;
  int rows_;
  int columns_;
  int tileWidth_;
  int tileHeight_;
  string backgroundColor_ = "000000";
  TileMap tileMap_;

public:
  LevelData() { }
  vector<Sound>& sounds() { return sounds_; }
  vector<Tile>& tiles() { return tiles_; }
  vector<Level>& levels() { return levels_; }
  void tileWidth(int value) { tileWidth_ = value; }
  int tileWidth() { return tileWidth_; } 
  void tileHeight(int value) { tileHeight_ = value; }
  int tileHeight() { return tileHeight_; }
  void tileMap(const TileMap& value) { tileMap_ = value; }
  TileMap& tileMap() { return tileMap_; }
};

#endif
