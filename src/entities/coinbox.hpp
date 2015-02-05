#ifndef COINBOX_HPP__
#define COINBOX_HPP__

#include "../character_entity.hpp"

namespace Entities
{

class Coinbox : public CharacterEntity
{
private:
  bool bumping_;
  int bumpCount_;

public:
  Coinbox(GameObject*);

  virtual void update(long);
};

}

#endif

