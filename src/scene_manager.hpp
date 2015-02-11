#ifndef SCENE_MANAGER_HPP__
#define SCENE_MANAGER_HPP__

#include <iostream>
#include <map>
#include <boost/format.hpp>
#include "scene.hpp"

using namespace std;

class SceneManager
{
private:
  map<string, Scene*> scenes_;
  Scene* currentScene_;
  string currentSceneName_;

public:
  SceneManager() : scenes_(map<string, Scene*>()), currentScene_(nullptr) {}

  Scene* currentScene() const { return currentScene_; }
  void currentScene(Scene* val) { currentScene_ = val; }

  string currentSceneName() const { return currentSceneName_; }

  void addScene(const string& name, Scene* scene)
  {
    if (scenes_.find(name) == scenes_.end())
    {
      scene->initialize();
      scenes_.insert(pair<string, Scene*>(name, scene));
    }
    else
    {
      throw new runtime_error("Scene already exists!");
    }
  }

  /*
   * Maybe startScene and gotoScene should return a Scene object, and currentScene should be readonly
   */
  Scene* startScene(const string& name)
  {
    currentSceneName_ = name;
    currentScene_ = scenes_[name];
    currentScene_->reset();
    currentScene_->run();

    return currentScene_;
  }

  Scene* gotoScene(const string& name)
  {
    currentSceneName_ = name;
    currentScene_ = scenes_[name];
    currentScene_->run();

    return currentScene_;
  }
};

#endif

