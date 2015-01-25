#ifndef GAME_OBJECT_HPP__
#define GAME_OBJECT_HPP__

#include <iostream>
#include <SDL2/SDL.h>
#include "scene_manager.hpp"

using namespace std;

class GameObject
{
private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
  SceneManager* sceneManager_;
  string title_;

public:
  GameObject(const string& title) : window_(nullptr)
                                    , renderer_(nullptr)
                                    , sceneManager_(nullptr)
  {
    title_ = title;
  }
  
  inline SDL_Window* window() const { return window_; }
  inline void window(SDL_Window* val) { window_ = val; }

  inline SDL_Renderer* renderer() const { return renderer_; }
  inline void renderer(SDL_Renderer* val) { renderer_ = val; }
 
  inline SceneManager* sceneManager() const { return sceneManager_; }
  inline void sceneManager(SceneManager* val) { sceneManager_ = val; }
};

#endif
