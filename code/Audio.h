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

    void playBackgroundMusicEffect(const char *filePath, int volume);
    void playBackgroundMusic(const char *filePath, int volume);
    void stopBackgroundMusic();
    void setVolume(int volume);
    int getVolume() { return volume; }

private:
    int volume;
    Mix_Music *backgroundMusic;
    Mix_Chunk *effectMusic;
    std::unique_ptr<std::thread> playbackThread;
};

#endif // AUDIO_H
