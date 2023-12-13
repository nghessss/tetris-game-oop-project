#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "game.h"
using namespace std;
class Game;
class Block{
protected:
    vector<vector<vector<int>>> Shape;
    SDL_Texture* img;
    SDL_Texture* shadowImg;
    Point TopLeft;
    int num_rotation;
    int n;
    
public:
    Block();
    ~Block();
    static int timePos;
    vector<vector<vector<int>>> getShape();
    SDL_Texture* getImg();
    SDL_Texture* getShadowImg();
    Point getTopLeft();

    int getNumRotation();
    int getN();
    void setTopLeft(Point p);
    void moveDown();
    void moveLeft();
    void moveRight();
    void changeDirect();
    void space(Point targetPoint);
};
#endif
