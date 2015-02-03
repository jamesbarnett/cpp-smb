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
#include "level_data.hpp"
#include "sound.hpp"
#include "tile.hpp"

using namespace std;
namespace fs = boost::filesystem;

class LevelDataParser2
{
private:
  fs::path path_;
  xmlDocPtr doc_;
  xmlXPathContextPtr xpathContext_;
  xmlXPathObjectPtr result_;

public:
  LevelDataParser2(const fs::path& path) : path_(path), doc_(nullptr)
    , xpathContext_(nullptr)
  {
    init();
  }

  ~LevelDataParser2()
  {
    xmlFreeDoc(doc_);
  }

  LevelData parse()
  {
    LevelData levelData;

    cout << "LevelDataParser2#parse called!" << endl;

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
};

#endif

