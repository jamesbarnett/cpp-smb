#ifndef BRICK_HPP__
#define BRICK_HPP__

#include "../character_entity.hpp"

namespace Entities
{

class Brick : public CharacterEntity
{
private:
  bool bumping_;

public:
  Brick(GameObject*);

  virtual void update(long);
};

}

#endif

