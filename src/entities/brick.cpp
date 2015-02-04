#include "brick.hpp"
#include "../game_object.hpp"
#include "../resource_manager.hpp"
#include "../main_scene.hpp"

namespace Entities
{
using namespace std;

Brick::Brick(GameObject* gameObject) : CharacterEntity(gameObject), bumping_(false)
{
  name("brick");
  spriteSheet(ResourceManager::instance()->getSpriteSheet("brick"));
  spriteSheet()->defineFrames(Direction::RIGHT, vector<int>({0}));
  spriteSheet()->defineFrames(Direction::LEFT, vector<int>({0}));
  spriteSheet()->defineFrames(Direction::JUMPRIGHT, vector<int>({0}));
  spriteSheet()->defineFrames(Direction::JUMPLEFT, vector<int>({0}));
  isPlayer(false);
  isStatic(true);
  acceleration(0);
  allowOffScreen(false);
}

void Brick::update(long ms)
{
  Viewport* v = ((MainScene*)CharacterEntity::gameObject()->sceneManager()->currentScene())->viewport();
  SCREEN_LOCATION sl = v->tileToScreen(originTileRow(), originTileCol());
  x(sl.X + v->yOffset());
  y(sl.Y + velocity());

  if (bumping_)
  {
    velocity(velocity() + 5);

    if (velocity() == 0) bumping_ = false;
  }
  else
    velocity(0);
}

}

