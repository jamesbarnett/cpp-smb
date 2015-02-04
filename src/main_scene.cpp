#include "main_scene.hpp"
#include "game_object.hpp"

MainScene::MainScene(GameObject* gameObject) : Scene(gameObject)
  , player_(CharacterEntity(gameObject)), viewport_(nullptr), level_(nullptr)
{
  level_ = gameObject->level();
  viewport_ =  new Viewport(gameObject, 64, 64, level_);
}
