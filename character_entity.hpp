#ifndef CHARACTER_ENTITY_HPP__
#define CHARACTER_ENTITY_HPP__

#include <iostream>
#include "entity.hpp"

class CharacterEntity : Entity
{
private:
  bool isPlayer_;
  bool isJumping_;
  bool isMoving_;
  bool allowOffScreen_;

public:
  CharacterEntity() : isPlayer_(false), isJumping_(false), isMoving_(false)
                      , allowOffScreen_(false) {}

  bool isPlayer() const { return isPlayer_; }
  void isPlayer(bool val) { isPlayer_ = val; }

  bool isJumping() const { return isJumping_; }
  void isJumping(bool val) { isJumping_ = val; }

  bool isMoving() const { return isMoving_; }
  void isJumping(bool val) { isMoving_ = val; }

  bool allowOffScreen() const { return allowOffScreen_; }
  void allowOffScreen(bool val) { allowOffScreen_ = val; }
};

#endif

