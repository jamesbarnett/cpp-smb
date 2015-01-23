#ifndef TILE_HPP__
#define TILE_HPP__

#include <iostream>

using namespace std;

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

  friend ostream& operator<<(ostream&, const Tile&);
};

ostream& operator<<(ostream& os, const Tile& rhs)
{
  os << "Tile { id: "
     << rhs.id_ << " resource: " << rhs.resource_
     << " solid: " << rhs.solid_
     << " breakable: " << rhs.breakable_
     << " background: " << rhs.background_
     << " goal: " << rhs.goal_
     << " entity: " << rhs.entity_
     << " frames: " << rhs.frames_
     << " value: " << rhs.value_
     << " }";
  return os;
}

#endif

