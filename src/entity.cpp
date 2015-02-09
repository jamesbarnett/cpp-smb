#include <iostream>
#include "entity.hpp"
#include "game_object.hpp"

using namespace std;

Entity::Entity(GameObject* gameObject) : name_(""), x_(0), y_(0), visible_(false)
  , velocity_(0), acceleration_(0), delete_(false)
  , /*texture_(nullptr),*/ gameObject_(nullptr), isStatic_(false), originTileRow_(0)
  , originTileCol_(0)
{
  gameObject_ = gameObject;
}

void Entity::draw()
{
  if (visible_)
  {
    SDL_Rect dest;
    dest.x = x();
    dest.y = y();
    dest.w = this->sprite().textureRect().w;
    dest.h = this->sprite().textureRect().h;

    // cout << "Entity#draw called!" << endl;
    // TODO: put some more thought into sprite renderering
    // cout << "Entity#draw: sprite: " << sprite() << endl;
    this->sprite().draw(gameObject_->renderer(), &dest);
  }
}

ostream& operator<<(ostream& os, const Entity& rhs)
{
  os << "Entity { name: " << rhs.name()
     << " x: " << rhs.x()
     << " y: " << rhs.y()
     << " }";

  return os;
}

