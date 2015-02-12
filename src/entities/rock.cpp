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
  spriteSheet()->defineFrames(Direction::NONE, vector<int>({0}));
  ResourceManager::instance()->loadTextureFromFile("rock",
    (fs::path("./resources") / fs::path("rock1.png")));
  SDL_Texture* texture = ResourceManager::instance()->getTexture("rock");
  sprite().texture(texture);
  sprite().textureRect(SDL_Rect({0,0,64,64}));
  facing(Direction::NONE);
  visible(true);
  isPlayer(false);
  isStatic(true);
  acceleration(0);
  allowOffScreen(false);
}

}

