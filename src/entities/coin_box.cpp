#include "coin_box.hpp"
#include "../game_object.hpp"
#include "../resource_manager.hpp"
#include "../main_scene.hpp"

namespace Entities
{
using namespace std;

CoinBox::CoinBox(GameObject* gameObject) : CharacterEntity(gameObject), bumping_(false), bumpCount_(5)
{
  name("coinbox");
  spriteSheet(ResourceManager::instance()->getSpriteSheet("coinbox"));
  spriteSheet()->defineFrames(Direction::NONE, vector<int>({0, 0, 0, 1, 2}));
  facing(Direction::NONE);
  isPlayer(false);
  isStatic(true);
  acceleration(0);
  allowOffScreen(false);
  // TODO: auto cycle spritesheet stuff
}

void CoinBox::update(long ms)
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

