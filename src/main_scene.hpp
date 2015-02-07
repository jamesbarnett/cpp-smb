#ifndef MAIN_SCENE_HPP_
#define MAIN_SCENE_HPP_

#include "character_entity.hpp"
#include "viewport.hpp"
#include "scene.hpp"
#include "entities/block.hpp"
#include "entities/brick.hpp"
#include "entities/coin_box.hpp"
#include "entities/empty_coin_box.hpp"
#include "entities/rock.hpp"

class MainScene : public Scene
{
private:
  CharacterEntity player_;
  Viewport* viewport_;
  Level* level_;

public:
  MainScene(GameObject* gameObject);

  Viewport* viewport() const { return viewport_; }

  virtual void initialize()
  {
  }

  virtual void update(long ms)
  {
    std::cout << "MainScene#update called! " << std::endl;
    silence(ms);

    for (auto e : entities())
    {
      e.update(ms);
      e.draw();
    }
  }

  virtual void draw()
  {
    drawBackground();
  }

  virtual void drawBackground()
  {
    vector<Entity> entities = viewport_->render();

    CharacterEntity* c = nullptr;

    for (auto e : entities)
    {
      c = nullptr;
      std::cout << "In main scene draw background entity loop" << std::endl;
      if (e.name().compare("goomba") == 0) {}
      else if (e.name().compare("koopatroopa") == 0) {}
      else if (e.name().compare("coinbox") == 0) c = new Entities::CoinBox(gameObject());
      else if (e.name().compare("emptycoinbox") == 0) c = new Entities::EmptyCoinBox(gameObject());
      else if (e.name().compare("rock") == 0) c = new Entities::Rock(gameObject());
      else if (e.name().compare("brick") == 0) c = new Entities::Brick(gameObject());
      else if (e.name().compare("block") == 0) c = new Entities::Block(gameObject());
      else if (e.name().compare("goal") == 0) {}
      else if (e.name().compare("pipetopleft") == 0) {}
      else if (e.name().compare("pipetopright") == 0) {}
      else if (e.name().compare("pipeleft") == 0) {}
      else if (e.name().compare("piperight") == 0) {}

      if (c != nullptr) // this condition should be removed when all entities are implemented
      {
        c->x(e.x());
        c->y(e.y());
        c->originTileCol(e.originTileCol());
        c->originTileRow(e.originTileRow());

        entities.push_back(*c);
      }
    }
  }
};

#endif

