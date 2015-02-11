#include <iostream>
#include "scene.hpp"
#include "game_object.hpp"

using namespace std;

void Scene::drawBackground()
{
  // cout << "Scene#drawBackground called!" << endl;
  // cout << "Back Sprite: " << backSprite_ << endl;
  backSprite_.draw(gameObject_->renderer(), nullptr);
}

void Scene::updateEntities()
{
  remove_if(entities_.begin(), entities_.end(),
    [](Entity* e) -> bool { return e->del(); });
}

ostream& operator<<(ostream& os, const Scene& rhs)
{
  os << "Scene { name: " << rhs.name()
     << " }";

  return os;
}

void silence(long ms)
{
  static long count = 0;

  count += ms;

  if (count % 4096 == 0)
  {
    cout << "count is " << count << endl;
  }
}

