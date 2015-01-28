#ifndef SPRITE_SHEET_HPP__
#define SPRITE_SHEET_HPP__

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include "direction.hpp"

using namespace std;

typedef struct tagSPRITEFRAME
{
  int currentFramePointer;
  vector<int> frames;
} SPRITEFRAME;

class SpriteSheet
{
private:
  SDL_Texture* texture_;
  int totalFrames_;
  map<Direction, SPRITEFRAME> spriteFrames_;
  int frameWidth_;
  int frameHeight_;

public:
  SpriteSheet() : texture_(nullptr), totalFrames_(1) {}
  
  ~SpriteSheet()
  {
    if (texture_ != nullptr) SDL_DestroyTexture(texture_);
  }

  int frameWidth() const { return frameWidth_; }
  int totalFrames() const { return totalFrames_; }
  void totalFrames(int val) { totalFrames_ = val; }

  void texture(SDL_Texture* texture)
  {
    if (texture_ != nullptr) SDL_DestroyTexture(texture);

    texture_ = texture;
    int w;
    SDL_QueryTexture(texture_, nullptr, nullptr, &w, &frameHeight_);
    frameWidth_ = w / totalFrames_;
  }
 
  SDL_Texture* texture() const { return texture_; }

  void defineFrames(Direction d, const vector<int>& frames)
  {
    cout << "spriteFrames_find: " << (spriteFrames_.find(d) == spriteFrames_.end()) << endl;

    if (spriteFrames_.find(d) != spriteFrames_.end()) return;

    SPRITEFRAME sf;

    sf.currentFramePointer = 0;
    sf.frames = vector<int>(frames.size());
    copy(frames.begin(), frames.end(), sf.frames.begin());
    spriteFrames_.insert(pair<Direction, SPRITEFRAME>(d, sf));
  }

  SDL_Rect getSprite(Direction d, int index)
  {
    SPRITEFRAME sf = spriteFrames_[d];
    sf.currentFramePointer = index;
    spriteFrames_[d] = sf;

    SDL_Rect rect;

    rect.x = frameWidth_ * sf.frames[sf.currentFramePointer];
    rect.y = 0;
    rect.w = frameWidth_;
    rect.h = frameHeight_;

    return rect;
  }

  SDL_Rect getFirstSprite(Direction d)
  {
    SPRITEFRAME sf = spriteFrames_[d];
    sf.currentFramePointer = 0;
    spriteFrames_[d] = sf;

    SDL_Rect rect;

    rect.x = frameWidth_ * sf.frames[sf.currentFramePointer];
    rect.y = 0;
    rect.w = frameWidth_;
    rect.h = frameHeight_;

    return rect;
  }

  SDL_Rect getNextSprite(Direction d)
  {
    SPRITEFRAME sf = spriteFrames_[d];
    sf.currentFramePointer++;
    spriteFrames_[d] = sf;

    SDL_Rect rect;

    rect.x = frameWidth_ * sf.frames[sf.currentFramePointer];
    rect.y = 0;
    rect.w = frameWidth_;
    rect.h = frameHeight_;

    return rect;
  }
};

#endif

