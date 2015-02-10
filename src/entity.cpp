#include <iostream>
#include "entity.hpp"
#include "game_object.hpp"

using namespace std;

Entity::Entity(GameObject* gameObject) : name_(""), x_(0), y_(0), visible_(false)
  , velocity_(0), acceleration_(0), delete_(false), gameObject_(nullptr)
  , isStatic_(false), originTileRow_(0), originTileCol_(0)
{
  gameObject_ = gameObject;
}

ostream& operator<<(ostream&, const SDL_Rect&);

void Entity::draw()
{
  if (visible_)
  {
    SDL_Rect dest;
    dest.x = x();
    dest.y = y();
    dest.w = this->sprite().textureRect().w;
    dest.h = this->sprite().textureRect().h;

    // cout << "Entity#draw: sprite: " << sprite() << " dest: " << dest << endl;
    if (name().compare("rock") == 0)
    {
      // cout << "Sprite: " << this->sprite() << endl;
    }
    this->sprite().draw(gameObject_->renderer(), &dest);
  }
}

ostream& operator<<(ostream& os, const Entity& rhs)
{
  os << "Entity { name: " << rhs.name()
     << " x: " << rhs.x()
     << " y: " << rhs.y()
     << " originTileCol: " << rhs.originTileCol()
     << " originTileRow: " << rhs.originTileRow()
     << " }";

  return os;
}

ostream& operator<<(ostream& os, const SDL_Rect& rect)
{
  os << "SDL_Rect: {"
     << rect.x << ","
     << rect.y << ","
     << rect.w << ","
     << rect.h << "} ";

  return os;
}
