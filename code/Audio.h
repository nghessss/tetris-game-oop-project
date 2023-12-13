#ifndef AUDIO_H
#define AUDIO_H

#include "SDL2/SDL_mixer.h"
#include <iostream>
using namespace std;

class Audio {
public:
    Audio();
    ~Audio();

    void playBackgroundMusic(const char *filePath);
    void stopBackgroundMusic();

private:
    Mix_Music *backgroundMusic;
};

#endif // AUDIO_H
