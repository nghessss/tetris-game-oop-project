#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <vector>
#include <queue>
#include <iomanip>
#include <sstream>
#include "game.h"
#include "Block.h"
using namespace std;
class Block;
class Point;
class GameState {
    SDL_Texture *currentGameState[rows+2][cols+2];
    static int timeStart;
    static int currentTime;
    static int score;
    static int clearedLines;
    static bool checkHold;
    double speed;
    double speedMultiplier;
    Block* currentBlock;
    Block* holdBlock;
    queue<Block*> nextBlock;
    int gameMode;
public:
    GameState();
    ~GameState();
    //update
    bool checkCollapse(Block *block,Point point);
    bool checkCanChangeDirect(Block *block);
    Point getCollapsablePoint();
    void updateGameState();
    void updateBlock();
    void clearLines();
    void updateMode();
    void updateScore(int line);
    //draw
    void drawGameState();
    void drawGameBorder();
    void drawTime();
    void drawBlock();
    void drawShadowBlock();
    void drawScore();
    void drawLines();
    void drawNextBlocks();
    void drawHold();
    void drawHoldBlock();
    void drawBlurBackground();
    //get
    Block* getCurrentBlock();
    Block* getHoldBlock();
    
    void holdCurrentBlock();
};

#endif