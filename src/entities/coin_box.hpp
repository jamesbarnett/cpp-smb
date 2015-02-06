#ifndef COIN_BOX_HPP__
#define COIN_BOX_HPP__

#include "../character_entity.hpp"

namespace Entities
{

class CoinBox : public CharacterEntity
{
private:
  bool bumping_;
  int bumpCount_;

public:
  CoinBox(GameObject*);

  virtual void update(long);
};

}

#endif

