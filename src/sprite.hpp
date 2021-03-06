#ifndef SPRITE_HPP__
#define SPRITE_HPP__

#include <cassert>
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
    // if (texture_ == nullptr) throw std::runtime_error("texture was null");
    assert(0 == SDL_RenderCopy(renderer, texture_, &textureRect_, dest));
  }

  friend std::ostream& operator<<(std::ostream&, const Sprite&);
};

std::ostream& operator<<(std::ostream&, const Sprite&);

#endif

