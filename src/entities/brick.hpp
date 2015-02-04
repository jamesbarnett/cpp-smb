#ifndef BRICK_HPP__
#define BRICK_HPP__

#include "../character_entity.hpp"

namespace Entities
{

class Brick : public CharacterEntity
{
public:
  Block(GameObject*);

  virtual void update(long);
};

}

#endif

