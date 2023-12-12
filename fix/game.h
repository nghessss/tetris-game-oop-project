#pragma once
#ifndef GAME_H
#define GAME_H
#define screen_height 800
#define screen_width 600
#define cols  10
#define rows  20
#define blockWidth  32
#define blockHeight 32
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "SDL2/SDL_image.h"
#include "Point.h"
#include "Block.h"
#include "gameState.h"
using namespace std;

class Block;
class Block_I;
class Block_O;
class Block_T;
class Block_L;
class Block_Z;
class Block_S;
class Block_J;

class GameState;  // Forward declaration
class Game {
private:
    SDL_Window* window;

public:
    static bool isRunning;
    static SDL_Renderer* renderer;
    static SDL_Event event;
    static int timeStart;
    static int currentTime;
    
    Game(const char* title = "", int xPos = 0, int yPos = 0, int width = 0, int height = 0, bool fullscreen = false);
    ~Game();
    GameState* gameState;
    void HandleEvent();
    void Update();
    void Renderer();
    void Clean();
    static void AddTile(int srcX, int srcY, int xpos, int ypos);
    bool Running();
};

#endif