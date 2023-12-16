#include "Audio.h"
#include <stdexcept>
#include <iostream>
#include <chrono>

Audio::Audio() : backgroundMusic(nullptr), playbackThread(nullptr) {
    volume = 0;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        throw runtime_error("SDL_mixer initialization failed: " + string(Mix_GetError()));
    }
}

Audio::~Audio() {
    stopBackgroundMusic();
    Mix_CloseAudio();
}

int Audio::getVolume() 
{ 
    return volume; 
}

void Audio::playBackgroundMusic(const char *filePath, int volume) {
    stopBackgroundMusic(); // Stop previous music if playing

    backgroundMusic = Mix_LoadMUS(filePath);
    if (!backgroundMusic) {
        cerr << "Failed to load music: " << Mix_GetError() << endl;
        return;
    }
    Mix_VolumeMusic(volume); // Example: Set volume to 50%

    if (Mix_PlayMusic(backgroundMusic, -1) == -1) {
        cerr << "Failed to play music: " << Mix_GetError() << endl;
        Mix_FreeMusic(backgroundMusic);
        backgroundMusic = nullptr;
    }
}

void Audio::playBackgroundMusicEffect(const char *filePath, int volume) {
    this->volume = volume;
    effectMusic = Mix_LoadWAV(filePath);
    if (!effectMusic) {
        std::cerr << "Failed to load hit sound: " << Mix_GetError() << std::endl;
        return;
    }
    Mix_VolumeChunk(effectMusic, volume); // Adjust the volume of the hit sound as needed
    if (Mix_PlayChannel(-1, effectMusic, 0) == -1) {
        std::cerr << "Failed to play hit sound: " << Mix_GetError() << std::endl;
        Mix_FreeChunk(effectMusic);
        effectMusic = nullptr;
    }
}

void Audio::stopBackgroundMusic() {
    if (playbackThread && playbackThread->joinable()) {
        playbackThread->join(); // Wait for playback thread to finish
    }

    if (backgroundMusic) {
        Mix_HaltMusic();
        Mix_FreeMusic(backgroundMusic);
        backgroundMusic = nullptr;
    }
}

void Audio::setVolume(int volume) {
    int currentVolume = max(0, min(volume, 128)); 
    this->volume = currentVolume;
    Mix_VolumeMusic(currentVolume);
}