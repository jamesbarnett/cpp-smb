#ifndef VIEWPORT_HPP__
#define VIEWPORT_HPP__

#include <iostream>
#include <SDL2/SDL.h>
#include "direction.hpp"
#include "level.hpp"
#include "entity.hpp"

using namespace std;

typedef struct tagSCREEN_LOCATION
{
  int X;
  int Y;
} SCREEN_LOCATION;

typedef struct tagTILE_LOCATION
{
  int row;
  int col;
} TILE_LOCATION;

class Viewport
{
private:
  GameObject* gameObject_;
  int tileWidth_;
  int tileHeight_;
  int screenWidth_;
  int screenHeight_;
  int scrollSpeed_;
  int screenTilesPerColumn_;
  int screenTilesPerRow_;
  int originXtile_;
  int originYtile_;
  int xOffset_;
  int yOffset_;

  Level* level_;

  vector<Entity> backSprites_;

public:
  Viewport(GameObject* gameObject, int tileWidth, int tileHeight, Level* level) :
    gameObject_(nullptr), tileWidth_(tileWidth), tileHeight_(tileHeight)
    , level_(level)
  {
    gameObject_ = gameObject;

    int w, h;

    SDL_GetWindowSize(gameObject_->window(), &w, &h);

    screenWidth_ = w;
    screenHeight_ = h;
    screenTilesPerRow_ = screenWidth_ / tileWidth_;
    screenTilesPerColumn_ = screenHeight_ / tileHeight_;
  }

  inline int tileWidth() const { return tileWidth_; }
  inline void tileWidth(int val) { tileWidth_ = val; }

  inline int tileHeight() const { return tileHeight_; }
  inline void tileHeight(int val) { tileHeight_ = val; }

  inline int screenWidth() const { return screenWidth_; }
  inline void screenWidth(int val) { tileWidth_ = val; }

  inline int screenHeight() const { return screenHeight_; }
  inline void screenHeight(int val) { screenHeight_ = val; }

  inline int scrollSpeed() const { return scrollSpeed_; }
  inline void scrollSpeed(int val) { scrollSpeed_ = val; }

  inline int screenTilesPerColumn() const { return screenTilesPerColumn_; }
  inline void screenTilesPerColumn(int val) { screenTilesPerColumn_ = val; }

  inline int screenTilesPerRow() const { return screenTilesPerRow_; }
  inline void screenTilesPerRow(int val) { screenTilesPerRow_ = val; }

  inline int originXtile() const { return originXtile_; }
  inline void originXtile(int val) { originXtile_ = val; }

  inline int xOffset() const { return xOffset_; }
  inline void xOffset(int val) { xOffset_ = val; }

  inline int yOffset() const { return yOffset_; }
  inline void yOffset(int val) { yOffset_ = val; }

  bool isEndOfLevel() const
  {
    return screenTilesPerColumn_ + originYtile_ >= level_->cols() - 1;
  }

  bool isStartOfLevel() const { return originYtile_ == 0; }

  bool scroll(Direction d, int speed)
  {
    scrollSpeed_ = speed;
    return scroll(d);
  }

  bool scroll(Direction d)
  {
    if (d == Direction::RIGHT)
    {
      if (!isEndOfLevel())
      {
        yOffset_ -= scrollSpeed_;

        if (yOffset_ <= -tileWidth_)
        {
          yOffset_ = 0;
          ++originYtile_;
        }

        return true;
      }
      else
      {
        return false;
      }
    }
    else if (d == Direction::LEFT)
    {
      if (!isStartOfLevel())
      {
        yOffset_ += scrollSpeed_;

        if (yOffset_ > tileWidth_)
        {
          yOffset_ = 0;
          --originYtile_;
        }

        return true;
      }
      else
      {
        return false;
      }
    }

    return false;
  }

  void render()
  {
    backSprites_.clear();

    int screenX = 0;
    int screenY = -1;

    for (int x = originXtile_; screenTilesPerRow_ + originXtile_; ++x)
    {
      for (int y = originYtile_; screenTilesPerColumn_ + originYtile_ + 2; ++y)
      {
        if (!level_->tiles(x, y).background())
        {
          if (!level_->tiles(x, y).entity().empty())
          {
            string entityName = level_->tiles(x, y).entity();

            // Create a background tile to replace the entity
            // TODO: implement

            SCREEN_LOCATION screenLocation = tileToScreen(x, y);

            // TODO: Let's implment the entity crap later
          }
          else
          {
            SDL_Texture* texture =
              ResourceManager::instance()->getTexture(level_->tiles(x, y).id());
            int x1 = (tileHeight_ * screenY) + yOffset_;
            int y1 = (tileWidth_ * screenX) + xOffset_;

            SDL_Rect rect;
            rect.x = x1;
            rect.y = y1;
            rect.w = 64;
            rect.h = 64;

            // Get position and draw tile
            SDL_RenderCopy(gameObject_->renderer(), texture, nullptr, &rect);
          }
        }

        ++screenY;
      }
    }

    screenY = -1;
    ++screenX;
  }

  TILE_LOCATION screenToTile(int x, int y) const
  {
    TILE_LOCATION t;

    t.row = ((y - xOffset_) / tileHeight_) + originXtile_;
    t.col = ((x - yOffset_) / tileWidth_) + originYtile_ + 1;

    return t;
  }

  SCREEN_LOCATION tileToScreen(int row, int col) const
  {
    SCREEN_LOCATION s;

    s.Y = (row * tileHeight_) * (originXtile_ + 1);
    s.X = (col * tileWidth_) - (originYtile_ * tileWidth_);

    return s;
  }

  void reset()
  {
    originXtile_ = 0;
    originYtile_ = 0;
    xOffset_ = 0;
    yOffset_ = 0;
  }
};

#endif

