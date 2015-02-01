#ifndef MAIN_SCENE_HPP_
#define MAIN_SCENE_HPP_

#include "character_entity.hpp"
#include "viewport.hpp"
#include "scene.hpp"

class MainScene : public Scene
{
private:
  CharacterEntity player_;
  Viewport* viewport_;
  Level* level_;

public:
  MainScene(GameObject* gameObject);

  virtual void initialize()
  {
  }

  virtual void update(long ms)
  {
    silence(ms);

    for (auto e : entities())
    {

    }
  }

  virtual void draw()
  {
  }

  virtual void drawBackground()
  {
    vector<Entity> entities = viewport_->render();
    CharacterEntity* c = nullptr;

    for (auto e : entities)
    {
      if (e.name().compare("goomba") == 0) {}
      else if (e.name().compare("koopatroopa") == 0) {}
      else if (e.name().compare("coinbox") == 0) {}
      else if (e.name().compare("emptycoinbox") == 0) {}
      else if (e.name().compare("rock") == 0) {}
      else if (e.name().compare("brick") == 0) {}
      else if (e.name().compare("block") == 0) {}
      else if (e.name().compare("goal") == 0) {}
      else if (e.name().compare("pipetopleft") == 0) {}
      else if (e.name().compare("pipetopright") == 0) {}
      else if (e.name().compare("pipeleft") == 0) {}
      else if (e.name().compare("piperight") == 0) {}

      c->x(e.x());
      c->y(e.y());
      c->originTileCol(e.originTileCol());
      c->originTileRow(e.originTileRow());
    }

  }
};

#endif

