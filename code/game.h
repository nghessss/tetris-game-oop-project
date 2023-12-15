#pragma once
#ifndef GAME_H
#define GAME_H
#define screen_height 800
#define screen_width 600
#define cols  10
#define rows  22
#define blockWidth  32
#define blockHeight 32
#define key_delay_constant 5
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "SDL2/SDL_image.h"
#include "Point.h"
#include "Audio.h"
#include "gameState.h"
#include "menu/MainMenu.h"
#include "menu/PauseMenu.h"
#include "BackgroundManager.h"

using namespace std;

class Block;

class GameState;  // Forward declaration

class Game {
private:
    SDL_Window* window;

public:
    Audio audioManager;
    static bool isRunning;
    static bool on;  // menu
    static SDL_Renderer* renderer;
    static SDL_Event event;
    static SDL_Texture* backgroundTexture;  
    
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