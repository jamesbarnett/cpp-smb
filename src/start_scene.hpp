#ifndef START_SCENE_HPP__
#define START_SCENE_HPP__

#include <iostream>
#include "game_object.hpp"
#include "entities/mario.hpp"
#include "scene.hpp"

using namespace std;

class StartScene : public Scene
{
private:
  TTF_Font* font_;

public:
  StartScene(GameObject* gameObject) : Scene(gameObject)
    , font_(nullptr)
  {
    font_ = ResourceManager::instance()->getFont("Arial 30");
  }

  virtual void reset()
  {
    Entities::Mario mario = Entities::Mario(gameObject());
    mario.x(430);
    mario.y(360);

    // TODO: Deal with sprite/SpriteSheet stuff
    Scene::reset();
  }

  virtual void update(long ms)
  {
    // TODO: add update logic
    if (ms % 4 == 0) cout << "StartScene#update: ms = " << ms << endl;
  }

  virtual void draw()
  {
    for (auto e : entities())
      e.draw();
  }

  virtual void drawBackground() {}
};

#endif

