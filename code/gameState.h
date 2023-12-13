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
    static int score;
    double speed;
    Block* currentBlock;
    queue<Block*> nextBlock;
    vector<Block*> blockList;
    int lineCount;
public:
    GameState();
    ~GameState();
    //update
    bool checkCollapse(Block *block,Point point);
    Point getCollapsablePoint();
    void updateGameState();
    void updateBlock();
    void clearLines();
    //draw
    void drawGameState();
    void drawGameBorder();
    void drawTime();
    void drawBlock();
    void drawShadowBlock();
    void drawScore();
    //get
    Block* getCurrentBlock();
};

#endif