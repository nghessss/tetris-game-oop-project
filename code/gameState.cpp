#include "gameState.h"
int GameState::timeStart = SDL_GetTicks();
int GameState::currentTime = SDL_GetTicks() - timeStart;
GameState::GameState() {
    for (int i = 0; i <= rows; ++i) {
        for (int j = 0; j <= cols; j++) {
            currentGameState[i][j] = false;
        }
    }
}
SDL_Texture* loadImage(const char* filename) {
    SDL_Surface* surface = IMG_Load(filename);
    if (surface == nullptr) {
        printf("Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == nullptr) {
        printf("Unable to create texture from %s! SDL Error: %s\n", filename, SDL_GetError());
        return nullptr;
    }

    return texture;
}
void GameState::drawGameBorder(){
    SDL_Texture* borderBlock = loadImage("image/border.png");
    for (int i = 0; i <= rows + 1; ++i) {
        SDL_Rect rect1 = {0, i * blockHeight, blockWidth, blockHeight };
        SDL_Rect rect2 = {(cols + 1) * blockWidth, i * blockHeight, blockWidth, blockHeight };
        SDL_RenderCopy(Game::renderer, borderBlock, nullptr, &rect1);
        SDL_RenderCopy(Game::renderer, borderBlock, nullptr, &rect2);
    }
    for (int i = 0; i <= cols + 1; ++i) {
        SDL_Rect rect1 = {i * blockWidth, 0, blockWidth, blockHeight };
        SDL_Rect rect2 = {i * blockWidth, (rows + 1) * blockHeight, blockWidth, blockHeight };
        SDL_RenderCopy(Game::renderer, borderBlock, nullptr, &rect1);
        SDL_RenderCopy(Game::renderer, borderBlock, nullptr, &rect2);
    }
}
void GameState::drawGameState() {
    
    SDL_Texture* backgroundBlock = loadImage("image/background.png");
    
    for (int i = 1; i <= rows; ++i) {
        for (int j = 1; j <= cols; ++j) {
            if (currentGameState[i][j] == 0) {
                SDL_Rect rect = {j * blockWidth, i * blockHeight, blockWidth, blockHeight };
                SDL_RenderCopy(Game::renderer, backgroundBlock, nullptr, &rect);
            }
            
            
        }
    }
}