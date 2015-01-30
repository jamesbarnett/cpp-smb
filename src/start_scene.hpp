#ifndef START_SCENE_HPP__
#define START_SCENE_HPP__

#include <iostream>
#include "game_object.hpp"
#include "entities/mario.hpp"
#include "scene.hpp"
#include "draw_helpers.hpp"

using namespace std;
using namespace Entities;

class StartScene : public Scene
{
private:
  TTF_Font* font_;
  SDL_Color white_;

public:
  StartScene(GameObject* gameObject) : Scene(gameObject)
    , font_(nullptr)
  {
    font_ = ResourceManager::instance()->getFont("Arial 30");
    white_.r = 0xFF;
    white_.g = 0xFF;
    white_.b = 0xFF;
    white_.a = 0xFF;
  }

  virtual void reset()
  {
    Mario mario(gameObject());
    mario.x(430);
    mario.y(360);
    mario.visible(true);
    mario.spriteSheet()->totalFrames(10);
    mario.sprite().texture(mario.spriteSheet()->texture());
    SDL_Rect rect = mario.spriteSheet()->getFirstSprite(Direction::RIGHT); 
    mario.sprite().textureRect(rect);
    this->addEntity(mario);
    Scene::reset();
  }

  virtual void update(long ms)
  {
  }

  virtual void draw()
  {
    drawString(this->gameObject()->renderer(), "MARIO", 100, 100, font_, white_);
    drawString(this->gameObject()->renderer(), "000000", 100, 130, font_, white_);
    drawString(this->gameObject()->renderer(), "x 00", 300, 130, font_, white_);
    drawString(this->gameObject()->renderer(), "WORLD", 530, 100, font_, white_);
    drawString(this->gameObject()->renderer(), "1-1", 560, 130, font_, white_);
    drawString(this->gameObject()->renderer(), "TIME", 830, 100, font_, white_);
    drawString(this->gameObject()->renderer(), "WORLD 1-1", 420, 300, font_, white_);
    drawString(this->gameObject()->renderer(), "x 3", 500, 380, font_, white_);
    drawString(this->gameObject()->renderer(), "[SPACE] To Begin", 300, 580, font_, white_);

    for (auto e : entities())
    {
      e.draw();
    }
  }

  virtual void drawBackground() {}
};

#endif

