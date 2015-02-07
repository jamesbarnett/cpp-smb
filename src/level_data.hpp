#ifndef LEVEL_DATA_HPP__
#define LEVEL_DATA_HPP__

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include "sound.hpp"
#include "tile.hpp"
#include "level.hpp"
#include "player.hpp"
#include "resource_manager.hpp"
#include "tile_data.hpp"
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
  Player player_;
  TileData tileData_;
  TileMap tileMap_;

public:
  LevelData() : id_(0), rows_(0), cols_(0), tileWidth_(0), tileHeight_(0) {}
  LevelData(const LevelData& d);

  inline std::list<Sound>& sounds() { return sounds_; }
  inline void sounds(const std::list<Sound>& val) { sounds_ = val; }

  inline std::vector<Tile>& tiles() { return tiles_; }
  inline std::vector<Level>& levels() { return levels_; }

  inline int id() const { return id_; }
  inline void id(int val) { id_ = val; }

  inline int rows() const { return rows_; }
  inline void rows(int val) { rows_ = val; }

  inline int cols() const { return cols_; }
  inline void cols(int val) { cols_ = val; }

  inline void tileWidth(int value) { tileWidth_ = value; }
  inline int tileWidth() const { return tileWidth_; }

  inline void tileHeight(int value) { tileHeight_ = value; }
  inline int tileHeight() const { return tileHeight_; }

  inline Player player() const { return player_; }
  inline void player(const Player& val) { player_ = val; }

  inline const TileData& tileData() const { return tileData_; }
  inline void tileData(const TileData& val) { tileData_ = val; }

  inline void tileMap(const TileMap& val) { tileMap_ = val; }
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
          t.res(), resources / safeResource(t.res()));
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

