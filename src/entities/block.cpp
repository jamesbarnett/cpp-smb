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
  spriteSheet(ResourceManager::instance()->getSpriteSheet("block"));
  spriteSheet()->defineFrames(Direction::RIGHT, vector<int>({0}));
  spriteSheet()->defineFrames(Direction::LEFT, vector<int>({0}));
  spriteSheet()->defineFrames(Direction::JUMPRIGHT, vector<int>({0}));
  spriteSheet()->defineFrames(Direction::JUMPLEFT, vector<int>({0}));
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

