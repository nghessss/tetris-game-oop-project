#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#include "game.h"
#include <vector>
using namespace std;
class Point{
    int x;
    int y;
public:
    Point(): x(0), y(0){};
    Point(int x, int y);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
};
class Block{
protected:
    vector<vector<vector<int>>> Shape;
    SDL_Texture* img;
    Point TopLeft;
    float speed;
    int num_rotation;
    int n;
    //vector<Point> pointLists; 
public:
    Block();
    ~Block();
    static int timePos;
    vector<vector<vector<int>>> getShape();
    SDL_Texture* getImg();
    Point getTopLeft();
    int getNumRotation();
    float getSpeed();

    void moveDown();
    void moveLeft();
    void moveRight();
    void changeDirect();
    void space();
};
class Block_I: public Block{
public:
    Block_I();
    ~Block_I(); 
};
class Block_O: public Block{
public:
    Block_O();
    ~Block_O(); 
};
class Block_T: public Block{
public:
    Block_T();
    ~Block_T(); 
};
class Block_L: public Block{
public:
    Block_L();
    ~Block_L(); 
};
class Block_Z: public Block{
public:
    Block_Z();
    ~Block_Z(); 
};
class Block_S: public Block{
public:
    Block_S();
    ~Block_S(); 
};
class Block_J: public Block{
public:
    Block_J();
    ~Block_J(); 
};
#endif



