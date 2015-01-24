#ifndef SCENE_MANAGER_HPP__
#define SCENE_MANAGER_HPP__

#include <iostream>
#include <map>
#include "scene.hpp"

using namespace std;

class SceneManager
{
private:
  map<string, Scene> scenes_;
  Scene* currentScene_;

public:
  SceneManager() : scenes_(map<string, Scene>()), currentScene_(nullptr) {}

  Scene* currentScene() const { return currentScene_; }
  void currentScene(Scene* val) { currentScene_ = val; }

  void addScene(const string& name, const Scene& scene)
  {
    if (scenes_.find(name) != scenes_.end())
    {
      scenes_.insert(pair<string, Scene>(name, scene));
    }
    else
    {
      throw new runtime_error("Scene already exists!");
    }
  }
};

#endif
