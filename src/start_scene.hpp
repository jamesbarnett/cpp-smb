#ifndef START_SCENE_HPP__
#define START_SCENE_HPP__

#include <iostream>
#include "game_object.hpp"

using namespace std;

class StartScene : Scene
{
private:
  GameObject* gameObject_;

public:
  StartScene(GameObject* gameObject) : gameObject_(nullptr)
  {
    gameObject_ = gameObject;
  }
};

#endif

