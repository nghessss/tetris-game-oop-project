#include "game.h"
#include "menu/MainMenu.h"
#include "menu/PauseMenu.h"
#include "menu/AboutMenu.h"

#include <chrono>
#include <thread>

int main(int argc, char* argv[]) {
    Game* game = new Game("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, false);
    MainMenu *mainM = new MainMenu;
    PauseMenu *pauseM = new PauseMenu;
    AboutMenu *aboutM = new AboutMenu;
    Game::isRunning = true;

    const int targetFPS = 60;
    const chrono::duration<double, milli> frameDuration(1000.0 / targetFPS);


    while (game->Running()) {
        if (game->on) {
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
        if (mainM->on) {
            mainM->HandleEvent();
            mainM->Update();
            mainM->Render();
        }
        if (aboutM->on) {
            aboutM->HandleEvent();
            aboutM->Update();
            aboutM->Render();            
        }
        if (pauseM->on) {
            pauseM->HandleEvent();
            pauseM->Update();
            pauseM->Render();
        }
    }

    delete game;
    delete mainM;
    delete pauseM;
    delete aboutM;
    return 0;
}