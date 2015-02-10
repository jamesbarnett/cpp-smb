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
    // cout << "MainScene#update called!" << endl;

    draw();

    for (auto e : entities())
    {
      e.update(ms);
      if (e.name().compare("rock") == 0)
      {
        e.update(ms);
        e.draw();
      }
    }
  }

  virtual void draw()
  {
    // cout << "MainScene#draw called" << endl;
    drawBackground();
  }

  virtual void drawBackground();
};

#endif

