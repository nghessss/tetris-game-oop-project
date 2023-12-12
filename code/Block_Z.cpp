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
        {0, 0, 1},
        {0, 1, 1},
        {0, 1, 0}};
    img = IMG_LoadTexture(Game::renderer, "img/block_Z.png");
}
Block_Z::~Block_Z(){}