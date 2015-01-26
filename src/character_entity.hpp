#ifndef CHARACTER_ENTITY_HPP__
#define CHARACTER_ENTITY_HPP__

#include <cmath>
#include <iostream>
#include "entity.hpp"
#include "direction.hpp"

class CharacterEntity : Entity
{
private:
  bool isPlayer_;
  bool isJumping_;
  bool isMoving_;
  bool allowOffScreen_;
  GameObject* gameObject_;
  SpriteSheet spriteSheet_;
  Direction facing_;

public:
  CharacterEntity(GameObject* gameObject) : isPlayer_(false), isJumping_(false)
    , isMoving_(false), allowOffScreen_(false), gameObject_(nullptr)
  , facing_(Direction::RIGHT)
  {
    gameObject(gameObject_);
  }

  inline bool isPlayer() const { return isPlayer_; }
  inline void isPlayer(bool val) { isPlayer_ = val; }

  inline bool isJumping() const { return isJumping_; }
  inline void isJumping(bool val) { isJumping_ = val; }

  inline bool isMoving() const { return isMoving_; }
  inline void isJumping(bool val) { isMoving_ = val; }

  inline bool allowOffScreen() const { return allowOffScreen_; }
  inline void allowOffScreen(bool val) { allowOffScreen_ = val; }

  inline SpriteSheet spriteSheet() { return spriteSheet_; }
  inline void spriteSheet(const SpriteSheet& val) { spriteSheet_ = val; }

  Direction facing() const { return facing_; }

  void facing(Direction d)
  {
    if (d == Direction::RIGHT)
    {
      acceleration(abs(acceleration()));
    }
    else if (d == Direction::LEFT)
    {
      acceleration(-acceleration());
    }
  }
};

#endif

