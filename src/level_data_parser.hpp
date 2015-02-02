#ifndef LEVEL_DATA_PARSER_HPP__
#define LEVEL_DATA_PARSER_HPP__

#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include "level_data.hpp"
#include "sound.hpp"
#include "tile.hpp"

using namespace std;
namespace fs = boost::filesystem;

class LevelDataParser
{
private:
  fs::path path_;
  xmlDocPtr doc_;
  xmlNodePtr root_;

public:
  LevelDataParser(const fs::path& path) : path_(path), doc_(nullptr), root_(nullptr)
  {
    init();
  }

  ~LevelDataParser()
  {
    xmlFreeDoc(doc_);
  }

  LevelData parse()
  {
    LevelData levelData;
    processFile(levelData);

    return levelData;
  }

private:
  void init()
  {
    doc_ = xmlParseFile(path_.c_str());

    if (nullptr == doc_)
    {
      cout << "Failed to open file: " << path_ << endl;
    }

    root_ = xmlDocGetRootElement(doc_);

    if (root_ == nullptr)
    {
      cout << "Failed to get xml root element!" << endl;
    }
  }

  bool processFile(LevelData& levelData)
  {
    xmlNodePtr cur = root_;
    cur = cur->xmlChildrenNode;

    while (cur != nullptr)
    {
      if (nodeFound(cur, "sounds"))
      {
        if (!parseSounds(cur->xmlChildrenNode, levelData)) return false;
      }
      else if (nodeFound(cur, "tiles"))
      {
        levelData.tileWidth(optionalIntAttr(cur, "width"));
        levelData.tileHeight(optionalIntAttr(cur, "height"));

        if (!parseTiles(cur->xmlChildrenNode, levelData)) return false;
      }
      else if (nodeFound(cur, "levels"))
      {
        if (!parseLevels(cur->xmlChildrenNode, levelData)) return false;
      }

      cur = cur->next;
    }

    if (!buildTileGrid(levelData)) return false;

    return true;
  }

  bool buildTileGrid(LevelData& levelData)
  {
    Level* level = &levelData.levels().at(0);

    levelData.id(level->id());
    levelData.rows(level->rows());
    levelData.cols(level->cols());
    levelData.tileMap(level->tileMap());

    vector<vector<int>> grid(level->tileMap().grid().size());

    int i = 0;
    for (vector<vector<int>>::iterator it = level->tileMap().grid().begin();
         it != level->tileMap().grid().end(); ++it)
    {
      int j = 0;
      grid.push_back(vector<int>(level->tileMap().grid()[0].size()));
      for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
      {
        cout << "pushing back: " << *it2 << endl;
        grid[i].push_back(*it2);
        ++j;
      }
      ++i;
    }

    i = 0;

    for (auto row : levelData.levels()[0].tileMap().grid())
    {
      copy(row.begin(), row.end(), back_inserter(grid[i]));
      ++i;
    }

    vector<Tile> tiles;
    copy(levelData.tiles().begin(), levelData.tiles().end(), back_inserter(tiles));

    for (size_t x = 0; x < grid.size(); ++x)
    {
      level->tiles().push_back(vector<Tile>(grid.size()));

      for (size_t y = 0; y < grid[x].size(); ++y)
      {
        vector<Tile>::iterator tile = find_if(tiles.begin(), tiles.end(),
          [x,y,&level,&grid](Tile t) -> bool { return t.id() == grid[x][y]; });

        if (tile == levelData.tiles().end())
        {
          stringstream err;
          err << "Failed to find tile: " << x << "!";
          throw runtime_error(err.str());
        }

        level->tiles()[x].push_back(*tile);
      }
    }

    return true;
  }

  bool parseSounds(xmlNodePtr cur, LevelData& levelData)
  {
    while (cur != nullptr)
    {
      if (nodeFound(cur, "sound"))
      {
        levelData.sounds().push_back(parseSound(cur));
      }

      cur = cur->next;
    }

    return true;
  }

  bool parseTiles(xmlNodePtr cur, LevelData& levelData)
  {
    while (cur != nullptr)
    {
      if (nodeFound(cur, "tile"))
      {
        levelData.tiles().push_back(parseTile(cur));
      }

      cur = cur->next;
    }

    return true;
  }

  bool parseLevels(xmlNodePtr cur, LevelData& levelData)
  {
    while (cur != nullptr)
    {
      if (nodeFound(cur, "level"))
      {
        levelData.levels().push_back(parseLevel(cur));
      }

      cur = cur->next;
    }

    return true;
  }

  Sound parseSound(xmlNodePtr cur)
  {
    return Sound(attr(cur, "name"), attr(cur, "res"));
  }

  Tile parseTile(xmlNodePtr& cur)
  {
    return Tile(
      boost::lexical_cast<int>(attr(cur, "id")),
      attr(cur, "res"),
      optionalBoolAttr(cur, "solid"),
      optionalBoolAttr(cur, "breakable"),
      optionalBoolAttr(cur, "background"),
      optionalBoolAttr(cur, "goal"),
      attr(cur, "entity"),
      optionalIntAttr(cur, "frames"),
      optionalIntAttr(cur, "value"),
      optionalBoolAttr(cur, "static")
    );
  }

  Level parseLevel(xmlNodePtr cur)
  {
    auto level = Level(optionalIntAttr(cur, "id"),
                       parsePlayer(cur->xmlChildrenNode),
                       parseTileMap(cur->xmlChildrenNode));

    return level;
  }

  Player parsePlayer(xmlNodePtr cur)
  {
    cur = cur->next;

    auto player = Player(optionalIntAttr(cur, "startrow"),
                         optionalIntAttr(cur, "startcol"),
                         attr(cur, "facing"));

    return player;
  }

  TileMap parseTileMap(xmlNodePtr cur)
  {
    cur = cur->next;
    cur = cur->next; // player to text
    cur = cur->next; // text to tilemap

    auto tileMap = TileMap(optionalIntAttr(cur, "rows"),
                           optionalIntAttr(cur, "cols"),
                           attr(cur, "bgcolor"),
                           parseRows(cur));
    return tileMap;
  }

  vector<vector<int>> parseRows(xmlNodePtr cur)
  {
    vector<vector<int>> rows;
    int rowIndex = 0;

    while (cur != nullptr)
    {
      if (nodeFound(cur, "tilemap"))
      {
        cur = cur->xmlChildrenNode;
        cur = cur->next;

        if (nodeFound(cur, "rows"))
        {
          cur = cur->xmlChildrenNode;
          cur = cur->next;

          while (cur != nullptr)
          {
            if (nodeFound(cur, "row"))
            {
              rows.push_back(vector<int>());
              parseRow(cur, rows[rowIndex]);
              ++rowIndex;
            }

            if (cur != nullptr) cur = cur->next;
          }
        }
      }

      if (cur != nullptr) cur = cur->next;
    }

    return rows;
  }

  void parseRow(xmlNodePtr cur, vector<int>& row)
  {
    vector<string> ids;
    xmlChar* text = xmlNodeGetContent(cur);
    string str((char*)text);
    boost::split(ids, str,
      [](char c) { return c == ','; }, boost::token_compress_on);
    xmlFree(text);

    for (auto id : ids)
    {
      boost::trim(id);
      row.push_back(boost::lexical_cast<int>(id));
    }
  }

  string attr(xmlNodePtr& cur, const string& name)
  {
    const xmlChar* nameTag = (const xmlChar*)name.c_str();
    if (xmlGetProp(cur, nameTag))
    {
      return string((const char*)(xmlGetProp(cur, nameTag)));
    }
    else
    {
      return string("");
    }
  }

  bool optionalBoolAttr(xmlNodePtr& cur, const string& name)
  {
    static const string T("true");
    return attr(cur, name).compare(T) == 0;
  }

  int optionalIntAttr(xmlNodePtr& cur, const string& name)
  {
    string val = attr(cur, name);
    if (!val.empty()) return boost::lexical_cast<int>(val);
    else return -1;
  }

  bool nodeFound(xmlNodePtr& cur, const char* name)
  {
    return !xmlStrcmp(cur->name, reinterpret_cast<const xmlChar*>(name));
  }
};

#endif

