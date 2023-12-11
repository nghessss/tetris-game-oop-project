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
void Game::HandleEvent() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
    int32_t key_count;
    const uint8_t *key_states = SDL_GetKeyboardState(&key_count);
    if (key_states[SDL_SCANCODE_LEFT]) {
        cout << "left" << endl;

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