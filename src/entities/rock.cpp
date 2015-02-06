#include "rock.hpp"
#include "../resource_manager.hpp"
#include "../game_object.hpp"

namespace Entities
{

Rock::Rock(GameObject* gameObject) : CharacterEntity(gameObject)
{
  name("rock");
  ResourceManager::instance()->loadSpriteSheetFromFile(
    (fs::path("./resources") / fs::path("rock1.png")), "rock", 1);
  spriteSheet(ResourceManager::instance()->getSpriteSheet("rock"));

}

}

