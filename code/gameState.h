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
    static long long score;
    static int clearedLines;
    static int combo;
    static bool checkHold;
    double speed;
    Block* currentBlock;
    Block* holdBlock;
    queue<Block*> nextBlock;
    int lineCount;
public:
    GameState();
    ~GameState();
    //update
    bool checkCollapse(Block *block,Point point);
    bool checkCanChangeDirect(Block *block);
    Point getCollapsablePoint();
    void updateGameState();
    void updateBlock();
    void updateScore(int line);
    void clearLines();
    //draw
    void drawGameState();
    void drawGameBorder();
    void drawTime();
    void drawBlock();
    void drawShadowBlock();
    void drawLines();
    void drawScore();
    void drawNextBlocks();
    void drawHold();
    void drawHoldBlock();
    //get
    Block* getCurrentBlock();
    Block* getHoldBlock();
    
    void holdCurrentBlock();
};

#endif