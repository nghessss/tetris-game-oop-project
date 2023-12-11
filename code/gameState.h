#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "game.h"


class GameState {
    bool currentGameState[rows][cols];

public:
    GameState();
    void drawGameState();
};

#endif
