#ifndef TILE_HPP__
#define TILE_HPP__

#include <iostream>
#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace std;

template<typename T>
boost::optional<T>
convert(boost::property_tree::ptree::value_type value,
        const string& key)
{
  return value.second.get_optional<T>(key);
}

class Tile
{
private:
  int id_;
  string resource_;
  bool solid_;
  bool breakable_;
  bool background_;
  bool goal_;
  string entity_;
  int frames_;
  int value_;

public:
  Tile(int id, string resource, bool solid, bool breakable, bool background, 
      bool goal, string entity, int frames, int value) :
    id_(id)
    , resource_(resource)
    , solid_(solid)
    , breakable_(breakable)
    , background_(background)
    , goal_(goal)
    , entity_(entity)
    , frames_(frames)
    , value_(value) {}

  static Tile parse(boost::property_tree::ptree::value_type value)
  {
    return Tile(
      convert<int>(value, "<xmlattr>.id").value_or(-1),
      convert<string>(value, "<xmlattr>.res").value_or(""),
      convert<bool>(value, "<xmlattr>.solid").value_or(false),
      convert<bool>(value, "<xmlattr>.breakable").value_or(false),
      convert<bool>(value, "<xmlattr>.background").value_or(false),
      convert<bool>(value, "<xmlattr>.goal").value_or(false),
      convert<string>(value, "<xmlattr>.entity").value_or(""),
      convert<int>(value, "<xmlattr>.frames").value_or(-1),
      convert<int>(value, "<xmlattr>.value").value_or(-1)
    );
  }

  void print()
  {
    cout << 
      "Tile { id: " << id_ << 
      ", resource: " << resource_ << 
      ", solid: " << solid_ <<
      ", breakable: " << breakable_ <<
      ", background: " << background_ <<
      ", goal: " << goal_ <<
      ", entity: " << entity_ <<
      ", frames: " << frames_ <<
      ", value: " << value_ <<
      " }" << endl;
  }
};

#endif

