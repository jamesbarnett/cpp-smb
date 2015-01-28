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
  MainScene(GameObject* gameObject, Level* level) : Scene(gameObject)
    , player_(CharacterEntity(gameObject)), viewport_(nullptr), level_(nullptr)
  {
     
    level_ = level;
    viewport_ =  new Viewport(gameObject, 64, 64, level);
  }
};

#endif

