#ifndef GAME_HPP__
#define GAME_HPP__

#include <iostream>
#include <boost/filesystem.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "initializer.hpp"
#include "level_data_parser.hpp"
#include "level_data_parser2.hpp"
#include "resource_manager.hpp"
#include "game_object.hpp"
#include "start_scene.hpp"
#include "main_scene.hpp"
#include "scene_manager.hpp"

using namespace std;
namespace fs = boost::filesystem;

class Game
{
private:
  GameObject* gameObject_;
  SDL_Window* mainWindow_;
  SDL_Renderer* renderer_;
  Initializer* initializer_;
  SceneManager* sceneManager_;
  bool isRunning_;

  bool createWindow()
  {
    mainWindow_ = SDL_CreateWindow("Hello World!",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      1024, 768, SDL_WINDOW_SHOWN);

    if (nullptr == mainWindow_)
    {
      cout << "SDL_CreateWindow error: " << SDL_GetError() << endl;
      SDL_Quit();
      return false;
    }

    return true;
  }

  bool createRenderer()
  {
    renderer_ = SDL_CreateRenderer(mainWindow_, -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer_ == nullptr)
    {
      cout << "SDL_CreateRenderer error: " << SDL_GetError() << endl;
      SDL_Quit();
      return false;
    }

    return true;
  }

public:
  Game() : gameObject_(nullptr)
    , mainWindow_(nullptr)
    , renderer_(nullptr)
    , initializer_(nullptr)
    , sceneManager_(nullptr)
    , isRunning_(true)
  {
    initializer_ = new Initializer;
  }

  ~Game()
  {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(mainWindow_);
    delete initializer_;
  }

  inline GameObject* gameObject() const { return gameObject_; }
  inline void gameObject(GameObject* val) { gameObject_ = val; }

  bool init()
  {
    if (!createWindow()) return false;
    if (!createRenderer()) return false;

    fs::path resources("resources");
    fs::path levelDataFile("leveldata.xml");

    LevelDataParser2 levelDataParser(resources / levelDataFile);
    levelDataParser.parse();

    // LevelDataParser levelDataParser(resources / levelDataFile);
    // auto levelData = levelDataParser.parse();
    //
    // gameObject_ = new GameObject;
    // gameObject_->window(mainWindow_);
    // gameObject_->renderer(renderer_);
    // gameObject_->levelData(&levelData);
    //
    // ResourceManager::instance()->renderer(renderer_);
    // levelData.load();
    //
    // sceneManager_ = new SceneManager;
    // gameObject_->sceneManager(sceneManager_);
    // sceneManager_->addScene("start", new StartScene(gameObject_));
    // sceneManager_->addScene("main", new MainScene(gameObject_));
    // sceneManager_->startScene("start");

    return true;
  }

  bool run()
  {
    // Game loop inspired by http://gafferongames.com/game-physics/fix-your-timestep/
    long timeDelta = 1000 / 60L;
    long timeAccumulator = 0L;
    long startTime = SDL_GetTicks();
    SDL_Event event;

    while (isRunning_)
    {
      startTime = SDL_GetTicks();

      while (timeAccumulator >= timeDelta)
      {
        update(timeDelta);
        timeAccumulator -= timeDelta;
      }

      while (SDL_PollEvent(&event))
      {
        if (event.type == SDL_QUIT) isRunning_ = false;
      }

      draw();
      timeAccumulator += SDL_GetTicks() - startTime;
    }

    return true;
  }

private:
  void update(long ms)
  {
    sceneManager_->currentScene()->update(ms);
  }

  void draw()
  {
    SDL_RenderClear(renderer_);
    sceneManager_->currentScene()->draw();
    SDL_RenderPresent(renderer_);
  }
};

#endif

