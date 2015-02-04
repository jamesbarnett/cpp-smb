#include "block.hpp"
#include "../game_object.hpp"
#include "../resource_manager.hpp"

namespace Entities
{

Block::Block(GameObject* gameObject) : CharacterEntity(gameObject)
{
  name("block");
  spriteSheet(ResourceManager::instance()->getSpriteSheet("block"));
}

}

