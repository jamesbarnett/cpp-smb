#include <iostream>
#include <SDL2/SDL.h>
#include "sprite.hpp"

using namespace std;

ostream& operator<<(ostream& os, const SDL_Rect rect)
{
  os << "SDL_Rect { x: " << rect.x
     << " y: " << rect.y
     << " w: " << rect.w
     << " h: " << rect.h
     << " }";

  return os;
}

ostream& operator<<(ostream& os, const Sprite& rhs)
{
  os << "Sprite { texture: " << rhs.texture_
     << " rect: " << rhs.textureRect_
     << " }";

  return os;
}

