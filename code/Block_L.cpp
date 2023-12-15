#include "Block_L.h"
Block_L::Block_L(): Block(){
    Shape[0] = {
        {0, 0, 0},
        {0, 0, 1},
        {1, 1, 1}};
    Shape[1] = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 1}};
    Shape[2] = {
        {0, 0, 0},
        {1, 1, 1},
        {1, 0, 0}};
    Shape[3] = {
        {1, 1, 0},
        {0, 1, 0},
        {0, 1, 0}};
    img = IMG_LoadTexture(Game::renderer, "image/orange.png");
    shadowImg = IMG_LoadTexture(Game::renderer, "image/shadow.png");
}
Block_L::~Block_L(){}