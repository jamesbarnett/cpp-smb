#include "block.hpp"
#include "../game_object.hpp"
#include "../resource_manager.hpp"
#include "../main_scene.hpp"

namespace Entities
{
using namespace std;

Block::Block(GameObject* gameObject) : CharacterEntity(gameObject)
{
  name("block");
  ResourceManager::instance()->loadSpriteSheetFromFile(
    (fs::path("./resources") / fs::path("block1.png")), "block", 1);
  spriteSheet(ResourceManager::instance()->getSpriteSheet("block"));
  spriteSheet()->defineFrames(Direction::NONE, vector<int>({0}));
  ResourceManager::instance()->loadTextureFromFile("block",
    (fs::path("./resources") / fs::path("block1.png")));
  SDL_Texture* texture = ResourceManager::instance()->getTexture("block");
  sprite().texture(texture);
  sprite().textureRect(SDL_Rect({0,0,64,64}));
  isPlayer(false);
  isStatic(true);
  acceleration(0);
  allowOffScreen(false);
}

void Block::update(long ms)
{
  Viewport* v = ((MainScene*)CharacterEntity::gameObject()->sceneManager()->currentScene())->viewport();
  SCREEN_LOCATION sl = v->tileToScreen(originTileRow(), originTileCol());
  x(sl.X + v->yOffset());
  y(sl.Y);
}

}

