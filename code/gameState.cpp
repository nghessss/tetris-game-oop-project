#include "gameState.h"
GameState::GameState() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; j++) {
            currentGameState[i][j] = false;
        }
    }
}
void GameState::drawGameState() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            SDL_SetRenderDrawColor(Game::renderer, rand() % 255, rand() % 255, 0, 255);
            SDL_Rect rect = { j * blockWidth, i * blockHeight, blockWidth, blockHeight };
            SDL_RenderFillRect(Game::renderer, &rect);
        }
    }
}