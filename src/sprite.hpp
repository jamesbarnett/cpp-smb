#ifndef SPRITE_HPP__
#define SPRITE_HPP__

#include <SDL2/SDL.h>

class Sprite
{
private:
  SDL_Rect textureRect_;
  SDL_Texture* texture_;

public:
  Sprite() : textureRect_({0,0,0,0}), texture_(nullptr) {}

  inline SDL_Rect textureRect() const { return textureRect_; }
  inline void textureRect(const SDL_Rect& val) { textureRect_ = val; }

  inline SDL_Texture* texture() const { return texture_; }
  inline void texture(SDL_Texture* val) { texture_ = val; }

  void draw(SDL_Renderer* renderer, const SDL_Rect* dest)
  {
    // std::cout << "Sprite#draw: " << textureRect_.x << "," << textureRect_.y << "," << textureRect_.w << "," << textureRect_.h << std::endl;
    SDL_RenderCopy(renderer, texture_, &textureRect_, dest);
  }
};

#endif
