#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <vector>
#include <queue>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "game.h"
#include "Block.h"
using namespace std;
class Block;
class Point;
class GameState {
    SDL_Texture *currentGameState[rows+2][cols+2];
    
    static int score;
    static int clearedLines;
    static bool checkHold;
    static int bestScore;
    double speed;
    double speedMultiplier;
    Block* currentBlock;
    Block* holdBlock;
    Block* boomBlock;
    queue<Block*> nextBlock;
    int gameMode;
public:
    static int boomCount;
    static int timeStart;
    static int currentTime;
    static bool gameOver;
    GameState();
    ~GameState();
    //update
    void checkGameOver();
    bool checkCollapse(Block *block,Point point);
    bool checkCanChangeDirect(Block *block);
    Point getCollapsablePoint();
    void updateGameState();
    void updateBlock();
    void clearLines();
    void updateMode();
    void updateScore(int line);
    void freeTheBoard();
    void updateBestScore();
    void loadBestScore();
    void saveBestScore();
    //draw
    
    void drawGameState();
    void drawGameBorder();
    void drawTime();
    void drawBlock();
    void drawShadowBlock();
    void drawScore();
    void drawLines();
    void drawNext();
    void drawNextBlocks();
    void drawHold();
    void drawHoldBlock();
    void drawBlurBackground();
    //get
    Block* getCurrentBlock();
    Block* getHoldBlock();
    Block* getBoomBlock();
    void holdCurrentBlock();
    //set
    void setCurrentBlock(Block* block);
};

#endif