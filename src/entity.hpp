#ifndef ENTITY_HPP__
#define ENTITY_HPP__

#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

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

public:
  Entity() : name_(""), x_(0), y_(0), visible_(false)
    , velocity_(0), accelaration_(0), delete_(false)
    , texture_(nullptr) {}

  string name() const { return name_; }
  void name(const string& val) { name_ = val; }
  int x() const { return x_; }
  void x(int val) { x_ = val; }
  int y() const { return y_; }
  void y(int val) { y_ = val }
  bool visible() const { return visible_; }
  void visible(bool val) { visible_ = val; }
  int velocity() const { return velocity_; }
  void velocity(int val) { velocity_ = val; }
  bool del() const { return delete_; }
  void del(bool val) { delete_ = val; }
  SDL_Texture* texture() const { return texture_; }
  void texture(SDL_Texture* val) { texture_ = val; }

  virtual void initialize() = 0;
  virtual void draw() = 0;
  virtual void udpate(long msecs) = 0;
  virtual void move() = 0;
};

#endif
