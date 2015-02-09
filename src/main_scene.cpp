#include "main_scene.hpp"
#include "game_object.hpp"

MainScene::MainScene(GameObject* gameObject) : Scene(gameObject)
  , player_(CharacterEntity(gameObject)), viewport_(nullptr), level_(nullptr)
{
  level_ = gameObject->level();
  viewport_ = new Viewport(gameObject, 64, 64, level_);
}

void MainScene::drawBackground()
{
  vector<Entity> entities = viewport_->render();

  CharacterEntity* c = nullptr;

  // cout << "entities.size(): " << entities.size() << endl;

  auto rock = Entities::Rock(gameObject());
  SDL_Rect src({0,0,64,64});
  SDL_Rect dst({0,704,64,64});
  SDL_RenderCopy(gameObject()->renderer(), rock.sprite().texture(), &src, &dst);

  for (auto e : entities)
  {
    c = nullptr;
    // cout << "Entity: " << e << endl;
    // std::cout << "In main scene draw background entity loop" << std::endl;
    if (e.name().compare("goomba") == 0) {}
    else if (e.name().compare("koopatroopa") == 0) {}
    else if (e.name().compare("coinbox") == 0) c = new Entities::CoinBox(gameObject());
    else if (e.name().compare("emptycoinbox") == 0) c = new Entities::EmptyCoinBox(gameObject());
    else if (e.name().compare("rock") == 0) c = new Entities::Rock(gameObject());
    else if (e.name().compare("brick") == 0) c = new Entities::Brick(gameObject());
    else if (e.name().compare("block") == 0) c = new Entities::Block(gameObject());
    else if (e.name().compare("goal") == 0) {}
    else if (e.name().compare("pipetopleft") == 0) {}
    else if (e.name().compare("pipetopright") == 0) {}
    else if (e.name().compare("pipeleft") == 0) {}
    else if (e.name().compare("piperight") == 0) {}

    if (c != nullptr) // this condition should be removed when all entities are implemented
    {
      c->x(e.x());
      c->y(e.y());
      c->originTileCol(e.originTileCol());
      c->originTileRow(e.originTileRow());

      addEntity(*c);
    }
  }
}
