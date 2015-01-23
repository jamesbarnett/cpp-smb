#ifndef RESOURCE_MANAGER_HPP__
#define RESOURCE_MANAGER_HPP__

#include <iostream>
#include <map>
#include <boost/filesystem.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

using namespace std;
namespace fs = boost::filesystem;

class ResourceManager
{
private:  
  map<string, SDL_Texture*> textures_;
  map<string, TTF_Font*> fonts_;
  map<string, Mix_Music*> music_;
  map<string, Mix_Chunk*> sounds_;
  SDL_Renderer* renderer_;

public:
  ResourceManager(SDL_Renderer* renderer) : renderer_(renderer) {}
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
  }

  void loadTextureFromFile(const fs::path& path, const string& name)
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
};

#endif
