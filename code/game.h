#pragma once
#ifndef GAME_H
#define GAME_H
#define screen_high 800
#define screen_width 600
#define cols  24
#define rows  32
#define blockWidth  (screen_width / cols)
#define blockHeight (screen_high / rows)
#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <vector>
#include "gameState.h"

using namespace std;

class GameState;  // Forward declaration
class Game {
private:
    SDL_Window* window;

public:
    static bool isRunning;
    static SDL_Renderer* renderer;
    static SDL_Event event;
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
