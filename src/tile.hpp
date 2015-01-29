#ifndef TILE_HPP__
#define TILE_HPP__

#include <iostream>

class Tile
{
private:
  int id_;
  std::string resource_;
  bool solid_;
  bool breakable_;
  bool background_;
  bool goal_;
  std::string entity_;
  int frames_;
  int value_;

public:
  Tile(int id, std::string resource, bool solid, bool breakable, bool background, 
      bool goal, std::string entity, int frames, int value) :
    id_(id)
    , resource_(resource)
    , solid_(solid)
    , breakable_(breakable)
    , background_(background)
    , goal_(goal)
    , entity_(entity)
    , frames_(frames)
    , value_(value) {}

  inline int id() const { return id_; }
  inline std::string res() const { return resource_; }

  inline bool background() const { return background_; }

  inline std::string entity() const { return entity_; }

  friend ostream& operator<<(ostream&, const Tile&);
};

std::ostream& operator<<(std::ostream&, const Tile&);

#endif

