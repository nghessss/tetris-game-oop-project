#include "audio.h"

Audio::Audio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "SDL_mixer initialization failed: " << Mix_GetError() << endl;
    }

    backgroundMusic = nullptr;
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

void Audio::stopBackgroundMusic() {
    if (backgroundMusic) {
        Mix_HaltMusic();
        Mix_FreeMusic(backgroundMusic);
        backgroundMusic = nullptr;
    }
}
