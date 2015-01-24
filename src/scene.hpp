#ifndef SCENE_HPP__
#define SCENE_HPP__

#include <iostream>
#include <SDL2/SDL.h>
#include "entity.hpp"
#include "level.hpp"

using namespace std;

class Scene
{
private:
  string name_;
  vector<Entity> entities_;
  SDL_Texture* texture_;
  long currentTicks_;
  long targetTicks_;
  bool pause_;
  int pauseSeconds_;
  SDL_Color backgroundColor_;
  Level level_;

public:
  Scene() : name_(""), entities_(vector<Entity>()), texture_(nullptr)
    , currentTicks_(0L), targetTicks_(0L), pause_(false), pauseSeconds_(0)
    , backgroundColor_({0, 0, 0, 0}) {}
  
  string name() const { return name_; }
  void name(const string& val) { name_ = val; }
  vector<Entity> entities() const { return entities_; }
  SDL_Texture* texture() const { return texture_; }
  void texture(SDL_Texture* val) { texture_ = val; }
  long currentTicks() const { return currentTicks_; }
  void currentTicks(long val) { currentTicks_ = val; }
  long targetTicks() const { return targetTicks_; }
  void targetTicks(long val) { targetTicks_ = val; }
  bool pause() const { return pause_; }
  void pause(bool val) { pause_ = val; }
  int pauseSeconds() const { return pauseSeconds_; }
  void pauseSeconds(int val) { pauseSeconds_ = val; }
  SDL_Color backgroundColor() const { return backgroundColor_; }
  void backgroundColor(SDL_Color val) { backgroundColor_ = val; }
  Level level() const { return level_; }
  void level(const Level& val) { level_ = val; }

  void addEntity(const Entity& entity) { entities_.push_back(entity); }

  virtual void initialize() {}
  virtual void reset() {}
  virtual void run() {}
  virtual void update(long msecs)
  {
    cout << msecs << endl; // appease clang for now
  }

  virtual void move() {}
  virtual void draw() {}
  virtual void userPause() {}
  virtual void onPause() {}
  virtual void afterPause() {}
};

#endif
