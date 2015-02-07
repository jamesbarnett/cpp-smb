#ifndef ENTITY_HPP__
#define ENTITY_HPP__

#include <iostream>
#include <SDL2/SDL.h>
#include "sprite.hpp"

using namespace std;

class GameObject;

class Entity
{
private:
  string name_;
  int x_;
  int y_;
  bool visible_;
  int velocity_;
  int acceleration_;
  bool delete_;
  SDL_Texture* texture_;
  GameObject* gameObject_;
  bool isStatic_;
  Sprite sprite_;
  int originTileRow_;
  int originTileCol_;

public:
  Entity(GameObject* gameObject);

  inline string name() const { return name_; }
  inline void name(const string& val) { name_ = val; }

  inline int x() const { return x_; }
  inline void x(int val) { x_ = val; }

  inline int y() const { return y_; }
  inline void y(int val) { y_ = val; }

  inline bool visible() const { return visible_; }
  inline void visible(bool val) { visible_ = val; }

  inline int velocity() const { return velocity_; }
  inline void velocity(int val) { velocity_ = val; }

  inline int acceleration() const { return acceleration_; }
  inline void acceleration(int val) { acceleration_ = val; }

  inline bool del() const { return delete_; }
  inline void del(bool val) { delete_ = val; }

  inline SDL_Texture* texture() const { return texture_; }
  inline void texture(SDL_Texture* val) { texture_ = val; }

  inline GameObject* gameObject() const { return gameObject_; }
  inline void gameObject(GameObject* val) { gameObject_ = val; }

  inline bool isStatic() const { return isStatic_; }
  inline void isStatic(bool val) { isStatic_ = val; }

  inline Sprite& sprite() { return sprite_; }

  inline int originTileRow() const { return originTileRow_; }
  inline void originTileRow(int val) { originTileRow_ = val; }

  inline int originTileCol() const { return originTileCol_; }
  inline void originTileCol(int val) { originTileCol_ = val; }

  // maybe make these pure virtual functions?
  virtual void initialize() {}

  virtual void draw();

  virtual void update(long ms)
  {
    if (ms % 2000 == 0) cout << "Entity#ms " << ms << endl;
  }

  virtual void move() {}

  friend ostream& operator<<(ostream&, const Entity&);
};

extern ostream& operator<<(ostream&, const Entity&);

#endif

