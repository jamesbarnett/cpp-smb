#ifndef LEVEL_DATA_PARSER_HPP2__
#define LEVEL_DATA_PARSER_HPP2__

#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include "tile_data.hpp"
#include "level_data.hpp"
#include "sound.hpp"
#include "tile.hpp"

namespace fs = boost::filesystem;

class LevelDataParser
{
private:
  fs::path path_;
  xmlDocPtr doc_;
  xmlXPathContextPtr xpathContext_;
  xmlXPathObjectPtr result_;

public:
  LevelDataParser(const fs::path& path) : path_(path), doc_(nullptr)
    , xpathContext_(nullptr)
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

    levelData.sounds(sounds());
    levelData.tileData(tileData());
    levelData.player(player());
    levelData.tileMap(tileMap());

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

    xpathContext_ = xmlXPathNewContext(doc_);

    if (nullptr == xpathContext_)
    {
      cout << "Failed to create new XPath context" << endl;
    }
  }

  std::list<Sound> sounds()
  {
    result_ = xmlXPathEvalExpression((const xmlChar*)"/levelData/sounds/sound", xpathContext_);
    xmlNodeSetPtr nodeset = result_->nodesetval;

    std::list<Sound> sounds = std::list<Sound>();

    for (int i = 0; i < nodeset->nodeNr; ++i)
    {
      sounds.push_back(parseSound(result_->nodesetval->nodeTab[i]));
    }

    return sounds;
  }

  TileData tileData()
  {
    result_ = xmlXPathEvalExpression((const xmlChar*)"/levelData/tiles", xpathContext_);
    xmlNodePtr node = result_->nodesetval->nodeTab[0];

    TileData tileData;

    tileData.width(optionalIntAttr(node, "width"));
    tileData.height(optionalIntAttr(node, "height"));

    result_ = xmlXPathEvalExpression((const xmlChar*)"/levelData/tiles/tile", xpathContext_);

    for (int i = 0; i < result_->nodesetval->nodeNr; ++i)
    {
      tileData.addTile(parseTile(result_->nodesetval->nodeTab[i]));
    }

    return tileData;
  }

  Player player()
  {
    result_ = xmlXPathEvalExpression((const xmlChar*)"/levelData/levels/level/player",
      xpathContext_);

    return parsePlayer(result_->nodesetval->nodeTab[0]);
  }

  TileMap tileMap()
  {
    result_ = xmlXPathEvalExpression(
      (const xmlChar*)"/levelData/levels/level/tilemap",
      xpathContext_);

    TileMap tileMap = parseTileMap(result_->nodesetval->nodeTab[0]);

    result_ = xmlXPathEvalExpression(
      (const xmlChar*)"/levelData/levels/level/tilemap/rows/row",
      xpathContext_);

    for (int i = 0; i < result_->nodesetval->nodeNr; ++i)
    {
      tileMap.addRow(parseRow(result_->nodesetval->nodeTab[i]));
    }

    return tileMap;
  }

  Sound parseSound(xmlNodePtr node)
  {
    return Sound(attr(node, "name"), attr(node, "res"));
  }

  Tile parseTile(xmlNodePtr node)
  {
    return Tile(
      boost::lexical_cast<int>(attr(node, "id")),
      attr(node, "res"),
      optionalBoolAttr(node, "solid"),
      optionalBoolAttr(node, "breakable"),
      optionalBoolAttr(node, "background"),
      optionalBoolAttr(node, "goal"),
      attr(node, "entity"),
      optionalIntAttr(node, "frames"),
      optionalIntAttr(node, "value"),
      optionalBoolAttr(node, "static")
    );
  }

  Player parsePlayer(xmlNodePtr node)
  {
    return Player(optionalIntAttr(node, "startrow"),
                  optionalIntAttr(node, "startcol"),
                  attr(node, "facing"));
  }

  TileMap parseTileMap(xmlNodePtr node)
  {
    TileMap tileMap;

    tileMap.rows(optionalIntAttr(node, "rows"));
    tileMap.cols(optionalIntAttr(node, "cols"));
    tileMap.bgcolor(attr(node, "bgcolor"));

    return tileMap;
  }

  std::vector<int> parseRow(xmlNodePtr node)
  {
    std::vector<string> ids;
    xmlChar* text = xmlNodeGetContent(node);
    string str((char*)text);
    boost::split(ids, str,
      [](char c) { return c == ','; }, boost::token_compress_on);
    xmlFree(text);

    vector<int> row;

    for (auto id : ids)
    {
      boost::trim(id);
      row.push_back(boost::lexical_cast<int>(id));
    }

    return row;
  }

  bool optionalBoolAttr(xmlNodePtr node, const std::string& name)
  {
    static const string T("true");
    return attr(node, name).compare(T) == 0;
  }

  int optionalIntAttr(xmlNodePtr node, const std::string& name)
  {
    string val = attr(node, name);
    if (!val.empty()) return boost::lexical_cast<int>(val);
    else return -1;
  }

  std::string attr(xmlNodePtr node, const std::string& name)
  {
    const xmlChar* nameTag = (const xmlChar*)name.c_str();
    if (xmlGetProp(node, nameTag))
    {
      return string((const char*)(xmlGetProp(node, nameTag)));
    }
    else
    {
      return string("");
    }
  }
};

#endif

