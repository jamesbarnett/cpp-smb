#include <cmath>
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
  vector<Entity*> entities = viewport_->render();

  cout << "drawBackground: Entity count: " << entities.size() << endl;
  CharacterEntity* c = nullptr;

  // cout << "entities.size(): " << entities.size() << endl;

  // auto rock = Entities::Rock(gameObject());
  // SDL_Rect src({0,0,64,64});
  // SDL_Rect dst({0,704,64,64});
  // SDL_RenderCopy(gameObject()->renderer(), rock.sprite().texture(), &src, &dst);
  //
  // dst.x = 64;
  // SDL_RenderCopy(gameObject()->renderer(), rock.sprite().texture(), &src, &dst);
  SDL_Rect s = SDL_Rect({0, 0, 64, 64});
  SDL_Rect d = SDL_Rect({0, 704, 64, 64});

  SDL_RenderCopy(gameObject()->renderer(), entities[0]->sprite().texture(),
    &s, &d);

  for (auto e : entities)
  {
    c = nullptr;
    // cout << "Entity: " << e << endl;
    // std::cout << "In main scene draw background entity loop" << std::endl;
    if (e->name().compare("goomba") == 0) {}
    else if (e->name().compare("koopatroopa") == 0) {}
    else if (e->name().compare("coinbox") == 0) c = new Entities::CoinBox(gameObject());
    else if (e->name().compare("emptycoinbox") == 0) c = new Entities::EmptyCoinBox(gameObject());
    else if (e->name().compare("rock") == 0) c = new Entities::Rock(gameObject());
    else if (e->name().compare("brick") == 0) c = new Entities::Brick(gameObject());
    else if (e->name().compare("block") == 0) c = new Entities::Block(gameObject());
    else if (e->name().compare("goal") == 0) {}
    else if (e->name().compare("pipetopleft") == 0) {}
    else if (e->name().compare("pipetopright") == 0) {}
    else if (e->name().compare("pipeleft") == 0) {}
    else if (e->name().compare("piperight") == 0) {}

    if (c != nullptr) // this condition should be removed when all entities are implemented
    {
      c->x(e->x());
      c->y(e->y());
      c->originTileCol(e->originTileCol());
      c->originTileRow(e->originTileRow());

      auto newEntity = find_if(entities.begin(), entities.end(),
        [c](Entity* e1) -> bool { return !(e1->x() == c->x()
          && e1->y() == c->y()
          && e1->originTileRow() == c->originTileRow()
          && e1->originTileCol() == c->originTileCol()); });

      // cout << "newEntity: " << *newEntity << endl;
      if (newEntity != entities.end())
      {
        // cout << "newEntity: " << newEntity << ", entities.end(): " << entities.end() << endl;
        // cout << "MainScene: calling addEntity: " << *c << endl;
        addEntity(c);
        c->draw(); // fucking hell, we are finally drawing something in the background
      }
    }
  }
}

void MainScene::scrollHandler()
{
  // Check for scroll
  int midScreen = (int)gameObject()->windowSize().y / 2;

  // Scroll viewport until end of level
  if (player_.isMoving() && player_.facing() == Direction::RIGHT
      && player_.x() >= midScreen && !viewport_->isEndOfLevel())
  {
    player_.x(midScreen);

    for (Entity* character : gameObject()->sceneManager()->currentScene()->entities())
    {
      CharacterEntity c = *((CharacterEntity*)character);

      if (!c.isPlayer() && c.facing() == Direction::RIGHT)
      {
          c.acceleration(0);
      }
      if (!c.isPlayer() && c.facing() == Direction::LEFT)
      {
          c.acceleration(-20);
      }
    }

    viewport_->scroll(Direction::RIGHT, player_.acceleration());
  }
  else
  {
    // If player is not moving, reset the acceleration of visibile entities to normal values
    for (Entity* character : gameObject()->sceneManager()->currentScene()->entities())
    {
      CharacterEntity c = *((CharacterEntity*)character);

      if (!c.isPlayer() && !c.isStatic())
      {
        if (c.acceleration() == 0) c.acceleration(1);
        c.acceleration(signbit(c.acceleration()) * 10);
      }
    }
  }
}

