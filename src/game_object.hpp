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
  Scene* currentScene_;

public:
  GameObject() : window_(nullptr)
                 , renderer_(nullptr)
                 , sceneManager_(nullptr)
                 , currentScene_(nullptr) {}

  inline SDL_Window* window() const { return window_; }
  inline void window(SDL_Window* val) { window_ = val; }

  inline SDL_Renderer* renderer() const { return renderer_; }
  inline void renderer(SDL_Renderer* val) { renderer_ = val; }

  inline SceneManager* sceneManager() const { return sceneManager_; }
  inline void sceneManager(SceneManager* val) { sceneManager_ = val; }

  inline Level* level() const { return level_; }
  inline void level(Level* val) { level_ = val; }

  void startScene(const std::string& name)
  {
    currentScene_ = sceneManager_->startScene(name);
    SDL_Color c = currentScene_->backgroundColor();
    cout << "Scene: " << name << ", color: " << c.r << "," << c.g << "," << c.b << endl;
    SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
  }

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

