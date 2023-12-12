#include "game.h"
int main(int argc, char* argv[]){
    Game *game = new Game("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, false);
    Game::isRunning = true;    
    while (game->Running()) {
        game->HandleEvent();
        game->Update();
        game->Renderer();
        
    }
    
    return 0;
}