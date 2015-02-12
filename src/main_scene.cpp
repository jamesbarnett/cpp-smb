#include <cmath>
#include "main_scene.hpp"
#include "game_object.hpp"
#include "entities/mario.hpp"

MainScene::MainScene(GameObject* gameObject) : Scene(gameObject)
  , player_(nullptr), viewport_(nullptr), level_(nullptr)
{
  level_ = gameObject->level();
  viewport_ = new Viewport(gameObject, 64, 64, level_);
  backgroundColor(SDL_Color({0x5C, 0x94, 0xFC, 0xFF}));
}

void MainScene::reset()
{
  viewport_->reset();
  entities().clear();
  Entities::Mario* mario = new Entities::Mario(gameObject());
  player_ = mario;
  addEntity(mario);

  // Start the song over
}

void MainScene::drawBackground()
{
  vector<Entity*> entities = viewport_->render();

  CharacterEntity* c = nullptr;

  for (auto e : entities)
  {
    c = nullptr;
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

      if (newEntity != entities.end())
      {
        addEntity(c);
        c->draw();
      }
    }
  }
}

void MainScene::handleEvent(SDL_Event event)
{
  if (event.type == SDL_KEYDOWN)
  {
    if (event.key.keysym.scancode == SDL_SCANCODE_A
        || event.key.keysym.scancode == SDL_SCANCODE_LEFT)
    {
      cout << "moving left" << endl;
      player_->facing(Direction::LEFT);
      player_->isMoving(true);
    }
    else if (event.key.keysym.scancode == SDL_SCANCODE_D
        || event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
    {
      cout << "Player: " << player_ << ": moving right" << endl;
      player_->facing(Direction::RIGHT);
      player_->isMoving(true);
    }
    else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE
        && !player_->isJumping())
    {
      // play jump sound
      cout << "jumping" << endl;
      player_->isJumping(true);
      player_->velocity(-55);
    }
  }
  else if (event.type == SDL_KEYUP)
  {
    if ((event.key.keysym.scancode == SDL_SCANCODE_A
        || event.key.keysym.scancode == SDL_SCANCODE_LEFT
        || event.key.keysym.scancode == SDL_SCANCODE_D
        || event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
        && !player_->isJumping())
    {
      player_->isMoving(false);
    }
  }
}

void MainScene::scrollHandler()
{
  // Check for scroll
  int midScreen = (int)gameObject()->windowSize().y / 2;

  // cout << "midScreen: " << midScreen << ", isMoving: " << player_->isMoving()
  //      << ", facing: " << player_->facing() << endl;

  // Scroll viewport until end of level
  if (player_->isMoving() && player_->facing() == Direction::RIGHT
      && player_->x() >= midScreen && !viewport_->isEndOfLevel())
  {
    player_->x(midScreen);

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

    cout << "About to call viewport scroll" << endl;
    viewport_->scroll(Direction::RIGHT, player_->acceleration());
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

void MainScene::update(long ms)
{
  draw();

  for (auto e : entities())
  {
    e->update(ms);
    e->draw();

    if (e->velocity() > viewport_->tileHeight()) e->velocity(viewport_->tileHeight());
    if (e->velocity() < -viewport_->tileHeight()) e->velocity(-viewport_->tileHeight());

  }

  updateEntities();
  scrollHandler();
}

