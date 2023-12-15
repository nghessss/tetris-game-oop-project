#include "Block_I.h"
Block_I::Block_I(): Block(){
    n = 4;
    Shape.resize(4, vector<vector<int>>(n, vector<int>(n, 0)));
    Shape[0] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0}};
    Shape[1] = {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0}};
    Shape[2] = {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};
    Shape[3] = {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}};
    
    img = IMG_LoadTexture(Game::renderer, "image/green2.png");
    shadowImg = IMG_LoadTexture(Game::renderer, "image/shadow.png");
}
Block_I::~Block_I(){}