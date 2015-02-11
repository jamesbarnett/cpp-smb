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
  ResourceManager::instance()->loadSpriteSheetFromFile(
    (fs::path("./resources") / fs::path("brick1.png")), "brick", 1);
  spriteSheet(ResourceManager::instance()->getSpriteSheet("brick"));
  spriteSheet()->defineFrames(Direction::NONE, vector<int>({0}));
  ResourceManager::instance()->loadTextureFromFile("brick",
    (fs::path("./resources") / fs::path("brick1.png")));
  SDL_Texture* texture = ResourceManager::instance()->getTexture("brick");
  sprite().texture(texture);
  sprite().textureRect(SDL_Rect({0,0,64,64}));
  isPlayer(false);
  isStatic(true);
  acceleration(0);
  allowOffScreen(false);
  visible(true);
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

