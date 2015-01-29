#include <iostream>
#include "src/tile.hpp"

using namespace std;

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
