#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem.hpp>
#include "level_data_parser.hpp"

using namespace std;
namespace fs = boost::filesystem;

class Game
{
private:
  SDL_Window* mainWindow_;
  bool isRunning_;
  
public:
  Game() : mainWindow_(0), isRunning_(true) { }

  ~Game()
  {
    SDL_DestroyWindow(mainWindow_);
    SDL_Quit();
  }

  bool init()
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

    fs::path resources("resources");
    fs::path levelDataFile("leveldata.xml");

    // auto levelDataOld = LevelData::load("./resources/leveldata.xml");
    // auto levelData = LevelDataParser::parse(resources / levelDataFile);
    LevelDataParser levelDataParser(resources / levelDataFile);
    cout << "About to parse Level data!" << endl;
    auto levelData = levelDataParser.parse();

    cout << "Level data parsed!" << endl;

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
        // update(timeDelta);
        timeAccumulator -= timeDelta;
      }

      while (SDL_PollEvent(&event))
      {
        if (event.type == SDL_QUIT) isRunning_ = false;

        // process user input here
      }

      draw();
      timeAccumulator += SDL_GetTicks() - startTime;
    }

    return true;
  }

private:
  // void update(long msecs)
  // {
  // }

  void draw()
  {

  }
};

