#include "viewport.hpp"
#include "game_object.hpp"

Viewport::Viewport(GameObject* gameObject, int tileWidth, int tileHeight, Level* level) :
  gameObject_(nullptr), tileWidth_(tileWidth), tileHeight_(tileHeight)
  , originXtile_(0), originYtile_(0), xOffset_(0), yOffset_(0), level_(level)
{
  gameObject_ = gameObject;

  int w, h;

  SDL_GetWindowSize(gameObject_->window(), &w, &h);

  screenWidth_ = w;
  screenHeight_ = h;
  screenTilesPerRow_ = screenWidth_ / tileWidth_;
  screenTilesPerColumn_ = screenHeight_ / tileHeight_;
}

vector<Entity> Viewport::render()
{
  vector<Entity> newEntities = vector<Entity>();

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
          if (!level_->tiles(x, y).isStatic())
          {
            Tile tile;
            tile.background(true);
            level_->tiles(x, y, tile);
          }

          SCREEN_LOCATION screenLocation = tileToScreen(x, y);
          Entity e2(gameObject_);
          e2.name(entityName);
          e2.x(screenLocation.X);
          e2.y(screenLocation.Y);
          newEntities.push_back(e2);
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

          backgroundSprite_.texture(texture);
          backgroundSprite_.textureRect(rect);
          cout << "Drawing background sprite!" << endl;
          backgroundSprite_.draw(gameObject_->renderer(), &rect);
        }
      }

      ++screenY;
    }

    screenY = -1;
    ++screenX;
  }

  return newEntities;
}
