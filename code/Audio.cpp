#include "Audio.h"
#include <stdexcept>
#include <iostream>
#include <chrono>

Audio::Audio() : backgroundMusic(nullptr), playbackThread(nullptr) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        throw runtime_error("SDL_mixer initialization failed: " + string(Mix_GetError()));
    }
}

Audio::~Audio() {
    stopBackgroundMusic();
    Mix_CloseAudio();
}

void Audio::playBackgroundMusic(const char *filePath) {
    stopBackgroundMusic(); // Stop previous music if playing

    backgroundMusic = Mix_LoadMUS(filePath);
    if (!backgroundMusic) {
        cerr << "Failed to load music: " << Mix_GetError() << endl;
        return;
    }

    if (Mix_PlayMusic(backgroundMusic, -1) == -1) {
        cerr << "Failed to play music: " << Mix_GetError() << endl;
        Mix_FreeMusic(backgroundMusic);
        backgroundMusic = nullptr;
    }
}

void Audio::playBackgroundMusicAsync(const char *filePath) {
    stopBackgroundMusic(); // Stop previous music if playing

    backgroundMusic = Mix_LoadMUS(filePath);
    if (!backgroundMusic) {
        cerr << "Failed to load music: " << Mix_GetError() << endl;
        return;
    }

    // Asynchronously play music and wait for 500 milliseconds
    future<void> result = async(launch::async, &Audio::playBackgroundMusicThread, this);
    result.wait_for(chrono::milliseconds(450));

    // Cleanup after playback
    stopBackgroundMusic();
}

void Audio::playBackgroundMusicThread() {
    if (Mix_PlayMusic(backgroundMusic, 0) == -1) {
        cerr << "Failed to play music: " << Mix_GetError() << endl;
        return;
    }

    // Allow the music to play indefinitely
    while (Mix_PlayingMusic()) {
        this_thread::sleep_for(chrono::milliseconds(10));
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

