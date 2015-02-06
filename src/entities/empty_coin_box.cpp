#include "empty_coin_box.hpp"
#include "../resource_manager.hpp"
#include "../game_object.hpp"

namespace Entities
{

EmptyCoinBox::EmptyCoinBox(GameObject* gameObject) : CharacterEntity(gameObject)
{
  name("emptycoinbox");
  spriteSheet(ResourceManager::instance()->getSpriteSheet("emptycoinbox"));
  spriteSheet()->defineFrames(Direction::NONE, vector<int>({0}));
  isPlayer(false);
  isStatic(true);
  acceleration(0);
  allowOffScreen(false);
}

}

