#ifndef DRAW_HELPERS_HPP__
#define DRAW_HELPERS_HPP__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "game_object.hpp"

using namespace std;

void drawString(SDL_Renderer* renderer, const string& str, int x, int y,
  TTF_Font* font, SDL_Color color)
{
  static int w, h;

  if (0 != TTF_SizeText(font, str.c_str(), &w, &h))
  {
    throw runtime_error("Failed to get text size!");
  }

  SDL_Surface* surface = TTF_RenderText_Solid(font, str.c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  static SDL_Rect rect;

  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;

  SDL_RenderCopy(renderer, texture, nullptr, &rect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

void drawStringRight(SDL_Renderer* renderer, const string& str, int x,
  int y, TTF_Font* font, const SDL_Color& color, GameObject* gameObject)
{
  static int w, h;

  if (0 != TTF_SizeText(font, str.c_str(), &w, &h))
  {
    throw runtime_error("Failed to get text size!");
  }

  SDL_Surface* surface = TTF_RenderText_Solid(font, str.c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SIZE size = gameObject->windowSize();

  static SDL_Rect rect;

  rect.x = size.x - w - x;
  rect.y = y;
  rect.w = w;
  rect.h = h;

  SDL_RenderCopy(renderer, texture, nullptr, &rect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

void drawStringCentered(SDL_Renderer* renderer, const string& str, int y,
  TTF_Font* font, const SDL_Color& color, GameObject* gameObject)
{
  static int w, h;

  if (0 != TTF_SizeText(font, str.c_str(), &w, &h))
  {
    throw runtime_error("Failed to get text size!");
  }

  SDL_Surface* surface = TTF_RenderText_Solid(font, str.c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SIZE size = gameObject->windowSize();

  static SDL_Rect rect;

  rect.x = size.x / 2 - w / 2;
  rect.y = y;
  rect.w = w;
  rect.h = h;

  SDL_RenderCopy(renderer, texture, nullptr, &rect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

void drawStringBottom(SDL_Renderer* renderer, const string& str, int x, int y,
  TTF_Font* font, const SDL_Color& color, GameObject* gameObject)
{
  static int w, h;

  if (0 != TTF_SizeText(font, str.c_str(), &w, &h))
  {
    throw runtime_error("Failed to get text size!");
  }

  SDL_Surface* surface = TTF_RenderText_Solid(font, str.c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SIZE size = gameObject->windowSize();

  static SDL_Rect rect;

  rect.x = x;
  rect.y = size.y - h - y;
  rect.w = w;
  rect.h = h;

  SDL_RenderCopy(renderer, texture, nullptr, &rect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

void drawStringBottomRight(SDL_Renderer* renderer, const string& str, int x, 
  int y, TTF_Font* font, const SDL_Color& color, GameObject* gameObject)
{
  static int w, h;

  if (0 != TTF_SizeText(font, str.c_str(), &w, &h))
  {
    throw runtime_error("Failed to get text size!");
  }

  SDL_Surface* surface = TTF_RenderText_Solid(font, str.c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SIZE size = gameObject->windowSize();

  static SDL_Rect rect;

  rect.x = size.x - w - x;
  rect.y = size.y - h - y;
  rect.w = w;
  rect.h = h;

  SDL_RenderCopy(renderer, texture, nullptr, &rect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

#endif

