#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <thread>
#include <memory>
#include <iostream>
#include <future>
using namespace std;
class Audio {
public:
    Audio();
    ~Audio();

    void playBackgroundMusicAsync(const char *filePath);
    void playBackgroundMusic(const char *filePath);
    void stopBackgroundMusic();

private:
    Mix_Music *backgroundMusic;
    std::unique_ptr<std::thread> playbackThread;

    void playBackgroundMusicThread();
};

#endif // AUDIO_H
