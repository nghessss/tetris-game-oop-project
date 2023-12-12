#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#include "game.h"
#include <vector>
using namespace std;

class Block{
protected:
    vector<vector<vector<int>>> Shape;
    SDL_Texture* img;
    Point TopLeft;
    int num_rotation;
    int n;
    int timePos;
public:
    Block();
    ~Block();

    vector<vector<vector<int>>> getShape();
    SDL_Texture* getImg();
    Point getTopLeft();
    int getNumRotation();
    int getN();
    int getTimePos();

    void moveDown();
    void moveLeft();
    void moveRight();
    void changeDirect();
    void space();
};
#endif