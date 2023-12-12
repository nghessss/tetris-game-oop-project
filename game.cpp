#include "game.h"


SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isRunning = false;
Game::Game(const char *title, int xPos, int yPos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        cout << "Subsystems Initialized" << endl;
        window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
        if (window) {
            cout << "Window Created" << endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 51, 0, 25, 255);
            cout << "Renderer Created" << endl;
        }

        isRunning = true;
        gameState = new GameState();

    } else {
        isRunning = false;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }
    
    
}

const int KEY_DELAY_CONSTANT = 20;

void Game::HandleEvent() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }

    static int leftKeyDelay = 0;
    static int downKeyDelay = 0;
    static int rightKeyDelay = 0;
    static int downLeftKeyDelay = 0;
    static int downRightKeyDelay = 0;
    static bool upKeyReleased = true;

    int32_t key_count;
    const uint8_t *key_states = SDL_GetKeyboardState(&key_count);

    if (key_states[SDL_SCANCODE_UP]) {
        if (upKeyReleased) {
            gameState->currentBlock->changeDirect();
            upKeyReleased = false;
        }
    } else {
        upKeyReleased = true;
    }

    if (key_states[SDL_SCANCODE_DOWN] && key_states[SDL_SCANCODE_LEFT]) {
        downLeftKeyDelay++;
        if (downLeftKeyDelay == KEY_DELAY_CONSTANT) {
            gameState->currentBlock->moveDown();
            gameState->currentBlock->moveLeft();
            downLeftKeyDelay = 0;
        }
    }
    else if (key_states[SDL_SCANCODE_DOWN] && key_states[SDL_SCANCODE_RIGHT]) {
        downRightKeyDelay++;
        if (downRightKeyDelay == KEY_DELAY_CONSTANT) {
            gameState->currentBlock->moveDown();
            gameState->currentBlock->moveRight();
            downRightKeyDelay = 0;
        }
    }
    else {
        if (key_states[SDL_SCANCODE_DOWN]) {
            downKeyDelay++;
            if (downKeyDelay == KEY_DELAY_CONSTANT) {
                gameState->currentBlock->moveDown();
                downKeyDelay = 0;
            }
        }
        else {
            if (key_states[SDL_SCANCODE_LEFT]) {
                leftKeyDelay++;
                if (leftKeyDelay == KEY_DELAY_CONSTANT) {
                    gameState->currentBlock->moveLeft();
                    leftKeyDelay = 0;
                }
            }
            
            if (key_states[SDL_SCANCODE_RIGHT]) {
                rightKeyDelay++;
                if (rightKeyDelay == KEY_DELAY_CONSTANT) {
                    gameState->currentBlock->moveRight();
                    rightKeyDelay = 0;
                }
            }
        }
    }
}

void updateTime() {
    
}
void Game::Update() {
    updateTime();
       
}
void Game::Renderer() {
    SDL_RenderClear(renderer);
    // This is where we would add stuff to render
    gameState->drawGameBorder();
    gameState->drawGameState();
    gameState->drawTime();  
    gameState->drawBlock();
    SDL_RenderPresent(renderer);
}
void Game::Clean() {
    delete gameState;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    TTF_Quit();
    cout << "Game Cleaned" << endl;
}
bool Game::Running() {
    return isRunning;
}
Game::~Game() {
    Clean();
}