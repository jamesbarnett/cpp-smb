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

namespace fs = boost::filesystem;

class LevelData
{
private:
  list<Sound> sounds_;
  std::vector<Tile> tiles_;
  std::vector<Level> levels_;
  int id_;
  int rows_;
  int cols_;
  int tileWidth_;
  int tileHeight_;
  std::string backgroundColor_ = "000000";
  TileMap tileMap_;

public:
  LevelData() : id_(0), rows_(0), cols_(0), tileWidth_(0), tileHeight_(0) {}
  LevelData(const LevelData& d);

  std::list<Sound>& sounds() { return sounds_; }
  std::vector<Tile>& tiles() { return tiles_; }
  std::vector<Level>& levels() { return levels_; }

  int id() const { return id_; }
  void id(int val) { id_ = val; }

  int rows() const { return rows_; }
  void rows(int val) { rows_ = val; }

  int cols() const { return cols_; }
  void cols(int val) { cols_ = val; }

  void tileWidth(int value) { tileWidth_ = value; }
  int tileWidth() const { return tileWidth_; }

  void tileHeight(int value) { tileHeight_ = value; }
  int tileHeight() const { return tileHeight_; }

  void tileMap(const TileMap& value) { tileMap_ = value; }
  const TileMap& tileMap() const { return tileMap_; }

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

    ResourceManager::instance()->loadFontFromFile(
      resources / fs::path("arial.ttf"), 30, "Arial 30");

    return true;
  }

  fs::path safeResource(const string& str)
  {
    if (!str.empty() && !boost::algorithm::ends_with(str, ".png"))
    {
      return fs::path(std::string(str + ".png"));
    }
    else
    {
      return fs::path(str);
    }
  }

  LevelData& operator=(const LevelData&);

  friend std::ostream& operator<<(std::ostream&, const LevelData&);
};

std::ostream& operator<<(std::ostream&, const LevelData&);

#endif

