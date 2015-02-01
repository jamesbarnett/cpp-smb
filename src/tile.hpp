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
  bool isStatic_;

public:
  Tile(int id, std::string resource, bool solid, bool breakable, bool background, 
      bool goal, std::string entity, int frames, int value, bool isStatic) :
    id_(id)
    , resource_(resource)
    , solid_(solid)
    , breakable_(breakable)
    , background_(background)
    , goal_(goal)
    , entity_(entity)
    , frames_(frames)
    , value_(value)
    , isStatic_(isStatic) {}

  Tile() : id_(0)
    , resource_("")
    , solid_(false)
    , breakable_(false)
    , background_(false)
    , goal_(false)
    , entity_("")
    , frames_(0)
    , value_(0)
    , isStatic_(false) {}

  inline int id() const { return id_; }

  inline std::string res() const { return resource_; }

  inline bool background() const { return background_; }
  inline void background(bool val) { isStatic_ = val; }

  inline std::string entity() const { return entity_; }

  inline bool isStatic() const { return isStatic_; }

  friend std::ostream& operator<<(std::ostream&, const Tile&);
};

std::ostream& operator<<(std::ostream&, const Tile&);

#endif

