#ifndef GAME_OBJECT_HPP__
#define GAME_OBJECT_HPP__

#include <iostream>
#include <SDL2/SDL.h>
#include "scene_manager.hpp"
#include "level.hpp"

using namespace std;

typedef struct tagSIZE
{
  int x;
  int y;
} SIZE;

class GameObject
{
private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
  SceneManager* sceneManager_;
  Level* level_;

public:
  GameObject() : window_(nullptr)
                 , renderer_(nullptr)
                 , sceneManager_(nullptr) {}

  inline SDL_Window* window() const { return window_; }
  inline void window(SDL_Window* val) { window_ = val; }

  inline SDL_Renderer* renderer() const { return renderer_; }
  inline void renderer(SDL_Renderer* val) { renderer_ = val; }

  inline SceneManager* sceneManager() const { return sceneManager_; }
  inline void sceneManager(SceneManager* val) { sceneManager_ = val; }

  inline Level* level() const { return level_; }
  inline void level(Level* val) { level_ = val; }

  SIZE windowSize()
  {
    static int w, h;
    SIZE size;

    SDL_GetWindowSize(window_, &w, &h);

    size.x = w;
    size.y = h;

    return size;
  }
};

#endif

