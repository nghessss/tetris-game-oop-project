#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "game.h"

SDL_Texture* loadImage(const char* filename);
class GameState {
    bool currentGameState[rows+1][cols+1];
    static int timeStart;
    static int currentTime;
public:
    GameState();
    void drawGameState();
    void drawGameBorder();
    void drawTime();
    void drawBlock(Block* &block);
};

#endif
