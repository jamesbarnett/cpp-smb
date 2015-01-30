#ifndef CHARACTER_ENTITY_HPP__
#define CHARACTER_ENTITY_HPP__

#include <cmath>
#include <iostream>
#include "entity.hpp"
#include "direction.hpp"

class CharacterEntity : public Entity
{
private:
  bool isPlayer_;
  bool isJumping_;
  bool isMoving_;
  bool allowOffScreen_;
  SpriteSheet* spriteSheet_;
  Direction facing_;

public:
  CharacterEntity(GameObject* gameObject) : Entity(gameObject), isPlayer_(false)
    , isJumping_(false), isMoving_(false), allowOffScreen_(false)
    , spriteSheet_(nullptr), facing_(Direction::RIGHT) {}

  inline bool isPlayer() const { return isPlayer_; }
  inline void isPlayer(bool val) { isPlayer_ = val; }

  inline bool isJumping() const { return isJumping_; }
  inline void isJumping(bool val) { isJumping_ = val; }

  inline bool isMoving() const { return isMoving_; }
  inline void isMoving(bool val) { isMoving_ = val; }

  inline bool allowOffScreen() const { return allowOffScreen_; }
  inline void allowOffScreen(bool val) { allowOffScreen_ = val; }

  inline SpriteSheet* spriteSheet() const { return spriteSheet_; }
  inline void spriteSheet(SpriteSheet* val) { spriteSheet_ = val; }

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

  virtual void update(long ms)
  {
    if (ms % 2000 == 0) cout << "CharacterEntity#ms " << ms << endl;

    if (!visible()) return;

    if (!isStatic())
    {
      if (isJumping())
      {
        velocity(velocity() + 5);
      }
      else
      {
        velocity(0);
      }

      y(y() + velocity());
      isJumping(true);
    }

    if (isMoving())
    {
      if (facing_ == Direction::RIGHT)
      {
        x(x() + acceleration());

        // get next sprite
        SDL_Rect rect = this->spriteSheet()->getNextSprite(Direction::RIGHT);
      }

      if (facing_ == Direction::LEFT)
      {
        if (!allowOffScreen())
        {
          if (x() > 0) x(x() + acceleration());
        }
        else
        {
          x(x() + acceleration());
        }

        // get next sprite
      }
    }

    if (!isMoving())
    {
      if (facing_ == Direction::RIGHT)
      {
        // get first sprite for direction
      }

      if (facing_ == Direction::LEFT)
      {
        // get first sprite for direction
      }
    }

    if (velocity() != 0 && facing_ == Direction::RIGHT)
    {
      // get first sprite
    }

    if (velocity() != 0 && facing_ == Direction::LEFT)
    {
      // get first sprite
    }

    Entity::move();
  }
};

#endif

