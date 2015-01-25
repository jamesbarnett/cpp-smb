#ifndef ENTITY_HPP__
#define ENTITY_HPP__

#include <iostream>
#include <SDL2/SDL.h>

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

public:
  Entity(GameObject* gameObject) : name_(""), x_(0), y_(0), visible_(false)
    , velocity_(0), acceleration_(0), delete_(false)
    , texture_(nullptr), gameObject_(nullptr)
  {
    gameObject_ = gameObject; 
  }


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
  inline void accelaration(int val) { acceleration_ = val; }

  inline bool del() const { return delete_; }
  inline void del(bool val) { delete_ = val; }

  inline SDL_Texture* texture() const { return texture_; }
  inline void texture(SDL_Texture* val) { texture_ = val; }

  // maybe make these pure virtual functions?
  virtual void initialize() {}
  virtual void draw() {}
  virtual void udpate(long msecs)
  {
    cout << msecs << endl; // temporary to silence clang warnings
  }

  virtual void move() {}
};

#endif

