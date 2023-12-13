#include "game.h"

#include <chrono>
#include <thread>

int main(int argc, char* argv[]) {
    Game* game = new Game("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, false);
    Game::isRunning = true;

    const int targetFPS = 60;
    const chrono::duration<double, milli> frameDuration(1000.0 / targetFPS);

    while (game->Running()) {
        auto frameStart = chrono::high_resolution_clock::now();

        game->HandleEvent();
        game->Update();
        game->Renderer();

        auto frameEnd = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(frameEnd - frameStart);

        if (elapsed < frameDuration) {
            this_thread::sleep_for(frameDuration - elapsed);
        }
    }

    delete game;
    return 0;
}