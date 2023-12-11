#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "game.h"


class GameState {
    bool currentGameState[rows+1][cols+1];
    static int timeStart;
    static int currentTime;
public:
    GameState();
    void drawGameState();
    void drawGameBorder();
    void drawTime();
};

#endif
