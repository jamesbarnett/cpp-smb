#include <iostream>
#include "entity.hpp"
#include "game_object.hpp"

using namespace std;

Entity::Entity(GameObject* gameObject) : name_(""), x_(0), y_(0), visible_(false)
  , velocity_(0), acceleration_(0), delete_(false)
  , texture_(nullptr), gameObject_(nullptr), isStatic_(false)
{
  gameObject_ = gameObject;
}

void Entity::draw()
{
  cout << "Entity#draw called" << endl;
  if (visible_)
  {
    SDL_Rect src = {0, 0, 64, 64};
    SDL_Rect dest = {x(), y(), 64, 64};
    SDL_RenderCopy(gameObject_->renderer(), texture_, &src, &dest);
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

