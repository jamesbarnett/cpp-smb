#ifndef LEVEL_DATA_HPP__
#define LEVEL_DATA_HPP__

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include "sound.hpp"
#include "tile.hpp"
#include "level.hpp"
#include "resource_manager.hpp"
#include "tile_map.hpp"

using namespace std;
namespace fs = boost::filesystem;

class LevelData
{
private:
  list<Sound> sounds_;
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
  LevelData() {}
  list<Sound>& sounds() { return sounds_; }
  vector<Tile>& tiles() { return tiles_; }
  vector<Level>& levels() { return levels_; }

  void tileWidth(int value) { tileWidth_ = value; }
  int tileWidth() { return tileWidth_; }
  void tileHeight(int value) { tileHeight_ = value; }

  int tileHeight() { return tileHeight_; }
  void tileMap(const TileMap& value) { tileMap_ = value; }

  TileMap& tileMap() { return tileMap_; }

  bool load()
  {
    Sound song = sounds_.front();
    sounds_.pop_front();

    fs::path resources("./resources");

    ResourceManager::instance()->loadMusicFromFile(
      resources / fs::path(song.res()), song.name());

    for (auto s : sounds_)
    {
      ResourceManager::instance()->loadSoundFromFile(
        resources / fs::path(s.res()), s.name());
    }

    for (auto t : tiles_)
    {
      if (!t.res().empty())
      {
        ResourceManager::instance()->loadTextureFromFile(
          t.id(), resources / safeResource(t.res()));
      }
    }

    return true;
  }

  fs::path safeResource(const string& str)
  {
    if (!str.empty() && !boost::algorithm::ends_with(str, ".png"))
    {
      return fs::path(string(str + ".png"));
    }
    else
    {
      return fs::path(str);
    }
  }
};

#endif

