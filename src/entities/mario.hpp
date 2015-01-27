#ifndef MARIO_HPP__
#define MARIO_HPP__

#include <iostream>
#include "../character_entity.hpp"

namespace Entities
{
using namespace std;

class Mario : public CharacterEntity
{
private:
  Mix_Chunk* stompSound_;
  Mix_Chunk* dieSound_;

public:
  Mario(GameObject* gameObject) : CharacterEntity(gameObject)
    , stompSound_(nullptr), dieSound_(nullptr)
  {
    stompSound_ = ResourceManager::instance()->getSound("stomp");
    dieSound_ = ResourceManager::instance()->getSound("mariodie");
    this->spriteSheet(ResourceManager::instance()->getSpriteSheet("sm-mario-sprites"));
    this->spriteSheet()->defineFrames(Direction::RIGHT, vector<int>{0, 1, 2, 3 });
    this->spriteSheet()->defineFrames(Direction::LEFT, vector<int>{5, 6, 7, 8});
    this->spriteSheet()->defineFrames(Direction::JUMPRIGHT, vector<int>{4});
    this->spriteSheet()->defineFrames(Direction::JUMPLEFT, vector<int>{9});
    this->isPlayer(true);
    this->facing(Direction::RIGHT);
    this->x(192);
    this->y(640);
    this->acceleration(10);
    this->allowOffScreen(false);
  }

  virtual void update(long ms)
  {
    // implement falling death

    CharacterEntity::update(ms);
  }

private:
  void marioDies()
  {
    // stop music
  }
};

}

#endif

