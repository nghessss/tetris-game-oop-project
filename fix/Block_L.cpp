#include "Block_L.h"
Block_L::Block_L(): Block(){
    Shape[0] = {
        {0, 0, 0},
        {1, 1, 1},
        {1, 0, 0}};
    Shape[1] = {
        {1, 1, 0},
        {0, 1, 0},
        {0, 1, 0}};
    Shape[2] = {
        {0, 0, 0},
        {0, 0, 1},
        {1, 1, 1}};
    Shape[3] = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 1}};
    img = IMG_LoadTexture(Game::renderer, "image/orange.png");
}
Block_L::~Block_L(){}