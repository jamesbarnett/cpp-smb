#ifndef RESOURCE_MANAGER_HPP__
#define RESOURCE_MANAGER_HPP__

#include <iostream>
#include <map>
#include <boost/filesystem.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "sprite_sheet.hpp"

using namespace std;
namespace fs = boost::filesystem;

class ResourceManager
{
private:
  static ResourceManager* instance_;
  map<string, SDL_Texture*> textures_;
  map<string, TTF_Font*> fonts_;
  map<string, Mix_Music*> music_;
  map<string, Mix_Chunk*> sounds_;
  map<string, SpriteSheet*> spriteSheets_;
  SDL_Renderer* renderer_ = nullptr;
  ResourceManager();

public:
  static ResourceManager* instance()
  {
    if (instance_ == nullptr)
    {
      instance_ = new ResourceManager();
    }

    return instance_;
  }

  ~ResourceManager()
  {
    for (auto t : textures_)
    {
      SDL_DestroyTexture(t.second);
    }

    for (auto f : fonts_)
    {
      TTF_CloseFont(f.second);
    }

    for (auto c : sounds_)
    {
      Mix_FreeChunk(c.second);
    }

    for (auto m : music_)
    {
      Mix_FreeMusic(m.second);
    }

    for (auto s : spriteSheets_)
    {
      delete s.second;
    }
  }

  void init();

  SDL_Renderer* renderer() const { return renderer_; }
  void renderer(SDL_Renderer* renderer) { renderer_ = renderer; }

  void loadTextureFromFile(const string& name, const fs::path& path)
  {
    SDL_Texture* texture = IMG_LoadTexture(renderer_, path.string().c_str());
    if (texture == nullptr)
    {
      throw new runtime_error("Failed to load texture!");
    }

    textures_.insert(pair<string, SDL_Texture*>(name, texture));
  }

  SDL_Texture* getTexture(const string& name)
  {
    if (textures_.find(name) != textures_.end())
    {
      return textures_[name];
    }
    else
    {
      return nullptr;
    }
  }

  void loadFontFromFile(const fs::path& path, int size, const string& name)
  {
     TTF_Font* font = TTF_OpenFont(path.string().c_str(), size);
     if (font == nullptr)
     {
       throw new runtime_error("Failed to load font!");
     }

     fonts_.insert(pair<string, TTF_Font*>(name, font));
  }

  TTF_Font* getFont(const string& name)
  {
    if (fonts_.find(name) != fonts_.end())
    {
      return fonts_[name];
    }
    else
    {
      return nullptr;
    }
  }

  void loadMusicFromFile(const fs::path& path, const string& name)
  {
    Mix_Music* music = Mix_LoadMUS(path.string().c_str());
    if (music == nullptr)
    {
      throw new runtime_error("Failed to load music!");
    }

    music_.insert(pair<string, Mix_Music*>(name, music));
  }

  Mix_Music* getMusic(const string& name)
  {
    if (music_.find(name) != music_.end())
    {
      return music_[name];
    }
    else
    {
      return nullptr;
    }
  }

  void loadSoundFromFile(const fs::path& path, const string& name)
  {
    Mix_Chunk* sound = Mix_LoadWAV(path.string().c_str());
    if (sound == nullptr)
    {
      throw new runtime_error("Failed to load sound!");
    }

    sounds_.insert(pair<string, Mix_Chunk*>(name, sound));
  }

  Mix_Chunk* getSound(const string& name)
  {
    if (sounds_.find(name) != sounds_.end())
    {
      return sounds_[name];
    }
    else
    {
      return nullptr;
    }
  }

  void loadSpriteSheetFromFile(const fs::path& path, const string& name, int totalFrames)
  {
    SDL_Texture* texture = IMG_LoadTexture(renderer_, path.string().c_str());
    if (texture == nullptr)
    {
      throw new runtime_error("Failed to load texture for sprite sheet!");
    }

    SpriteSheet* spriteSheet = new SpriteSheet();

    spriteSheet->totalFrames(totalFrames);
    spriteSheet->texture(texture);
    spriteSheets_.insert(pair<string, SpriteSheet*>(name, spriteSheet));
  }

  SpriteSheet* getSpriteSheet(const string& name)
  {
    if (spriteSheets_.find(name) != spriteSheets_.end())
    {
      return spriteSheets_[name];
    }
    else
    {
      return nullptr;
    }
  }
};

#endif

