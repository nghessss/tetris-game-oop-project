#include "Block_Z.h"
Block_Z::Block_Z(): Block(){
    Shape[0] = {
        {0, 0, 0},
        {1, 1, 0},
        {0, 1, 1}};
    Shape[1] = {
        {0, 0, 1},
        {0, 1, 1},
        {0, 1, 0}};
    Shape[2] = {
        {0, 0, 0},
        {1, 1, 0},
        {0, 1, 1}};
    Shape[3] = {
        {0, 1, 0},
        {1, 1, 0},
        {1, 0, 0}};
    img = IMG_LoadTexture(Game::renderer, "image/red.png");
    shadowImg = IMG_LoadTexture(Game::renderer, "image/shadow.png");
}
Block_Z::~Block_Z(){}