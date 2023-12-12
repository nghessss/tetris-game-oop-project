#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <vector>
#include <queue>
#include "game.h"
#include "Block.h"
using namespace std;
class Block;
class Point;
class GameState {
    SDL_Texture *currentGameState[rows+2][cols+2];
    static int timeStart;
    static int currentTime;
    double speed;
    Block* currentBlock;
    queue<Block*> nextBlock;
    vector<Block*> blockList;
public:
    GameState();
    ~GameState();
    //update
    bool checkCollapse(Block* block);
    Point getCollapsablePoint();
    void updateGameState();
    void updateBlock();
    //draw
    void drawGameState();
    void drawGameBorder();
    void drawTime();
    void drawBlock();
};

#endif