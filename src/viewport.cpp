#include "viewport.hpp"
#include "game_object.hpp"
#include "resource_manager.hpp"
#include "entities/rock.hpp"

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

vector<Entity*> Viewport::render()
{
  vector<Entity*> newEntities = vector<Entity*>();

  backSprites_.clear();

  int screenX = 0;
  int screenY = -1;

  for (int x = originXtile_; x < screenTilesPerRow_ + originXtile_ + 1; ++x)
  {
    for (int y = originYtile_; y < screenTilesPerColumn_ + originYtile_ /*+ 2*/; ++y)
    {
      Tile tile = level_->tiles(x, y);

      if (!tile.background())
      {
        if (!tile.entity().empty())
        {
          string entityName = tile.entity();

          // Create a background tile to replace the entity
          if (!tile.isStatic())
          {
            cout << "Viewport#render: trying to replace tile" << endl;
            Tile tile = Tile();
            tile.background(true);
            level_->tiles(x, y, tile);
          }

          SCREEN_LOCATION screenLocation = tileToScreen(x, y);
          cout << "Screen Location: " << screenLocation.X << "," << screenLocation.Y << endl;
          Entity* namedEntity = new Entity(gameObject_);
          namedEntity->name(entityName);
          namedEntity->x(screenLocation.X);
          namedEntity->y(screenLocation.Y);
          newEntities.push_back(namedEntity);
        }
        else
        {
          // cout << "Tile res: " << tile.res() << endl;
          // SDL_Texture* texture =
          //   ResourceManager::instance()->getTexture(tile.res());
          // int x1 = (tileHeight_ * screenY) + yOffset_;
          // int y1 = (tileWidth_ * screenX) + xOffset_;
          //
          // SDL_Rect rect;
          // rect.x = x1;
          // rect.y = y1;
          // rect.w = tileWidth_;
          // rect.h = tileHeight_;
          //
          // backgroundSprite_.texture(texture);
          // backgroundSprite_.textureRect(rect);
          // backgroundSprite_.draw(gameObject_->renderer(), &rect);
        }
      }

      ++screenY;
    }

    screenY = -1;
    ++screenX;
  }

  return newEntities;
}

