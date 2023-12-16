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
private:
    int volume;
    Mix_Music *backgroundMusic;
    Mix_Chunk *effectMusic;
    unique_ptr<thread> playbackThread;
public:
    Audio();
    ~Audio();

    //get
    int getVolume();

    //set
    void setVolume(int volume);

    //music
    void playBackgroundMusicEffect(const char *filePath, int volume);
    void playBackgroundMusic(const char *filePath, int volume);
    void stopBackgroundMusic();
};

#endif // AUDIO_H
