#ifndef INITIALIZER_HPP__
#define INITIALIZER_HPP__

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

class Initializer
{
public:
  Initializer()
  {
    initSDL();
    initImage();
    initSound();
    initTTF();
  }

  ~Initializer()
  {
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
  }

private:
  bool initSDL()
  {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
      cout << "SDL_Init error: " << SDL_GetError() << endl;
      return false;
    }

    return true;
  }

  bool initImage()
  {
    int FLAGS = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(FLAGS);

    if ((initted & FLAGS) != FLAGS)
    {
      cout << "Failed to initialize IMG_Init: " << IMG_GetError() << endl;
      return false;
    }

    return true;
  }

  bool initSound()
  {
    const int FLAGS = MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG;
    int initted = Mix_Init(FLAGS);

    if ((initted & FLAGS) != FLAGS)
    {
      cout << "Failed to initialize Mix_Init: " << Mix_GetError() << endl;
      return false;
    }

    const int AUDIO_RATE = 22050;
    const Uint16 AUDIO_FORMAT = AUDIO_S16SYS;
    const int AUDIO_CHANNELS = 2;
    const int AUDIO_BUFFERS = 4096;

    if (Mix_OpenAudio(AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFERS) != 0)
    {
      cout << "Failed to initialize audio: " << Mix_GetError() << endl;
      return false;
    }

    return true;
  }

  bool initTTF()
  {
    if (TTF_Init() == -1)
    {
      cout << "Failed to initialize fonts: " << TTF_GetError() << endl;
      return false;
    }

    return true;
  }
};

#endif

