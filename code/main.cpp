#include "game.h"
#include "menu/MainMenu.h"
#include "menu/PauseMenu.h"
#include "menu/AboutMenu.h"
#include "menu/GameoverMenu.h"
#include "menu/RecordMenu.h"
#include "menu/TutorialMenu.h"

#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    Game::game = new Game("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, false);
    MainMenu *mainM = new MainMenu;
    PauseMenu *pauseM = new PauseMenu;
    AboutMenu *aboutM = new AboutMenu;
    GameoverMenu *gameoverM = new GameoverMenu;
    RecordMenu *recordM = new RecordMenu;
    TutorialMenu *tutorialM = new TutorialMenu;
    const int targetFPS = 60;
    const chrono::duration<double, milli> frameDuration(1000.0 / targetFPS);

    while (Game::game->Running())
    {
        if (Game::game->on)
        {
            auto frameStart = chrono::high_resolution_clock::now();

            Game::game->HandleEvent();
            Game::game->Update();
            Game::game->Renderer();

            auto frameEnd = chrono::high_resolution_clock::now();
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(frameEnd - frameStart);
            if (GameState::gameOver)
            {
                GameoverMenu::audioGameoverMenu.playBackgroundMusic("audio/gameOver.mp3", 40);
                while (GameState::gameOver)
                {
                    gameoverM->HandleEvent();
                    gameoverM->Update();
                    gameoverM->Render();
                }
                GameoverMenu::audioGameoverMenu.stopBackgroundMusic();
            }
            if (elapsed < frameDuration)
            {
                this_thread::sleep_for(frameDuration - elapsed);
            }
        }
        if (mainM->on)
        {
            Game::game->on = false;
            mainM->HandleEvent();
            if (mainM->on)
            {
                mainM->Update();
                mainM->Render();
            }
        }
        if (aboutM->on)
        {
            aboutM->HandleEvent();
            if (aboutM->on)
            {
                aboutM->Update();
                aboutM->Render();
            }
        }
        if (recordM->on)
        {
            recordM->HandleEvent();
            if (recordM->on)
            {
                recordM->Update();
                recordM->Render();
            }
        }
        if (tutorialM->on)
        {
            tutorialM->HandleEvent();
            if (tutorialM->on)
            {
                tutorialM->Update();
                tutorialM->Render();
            }
        }
        if (pauseM->on)
        {
            pauseM->HandleEvent();
            if (pauseM->on)
            {
                pauseM->Update();
                pauseM->Render();
            }
        }
    }

    delete Game::game;
    delete mainM;
    delete pauseM;
    delete aboutM;
    delete gameoverM;
    delete recordM;
    delete tutorialM;
    return 0;
}