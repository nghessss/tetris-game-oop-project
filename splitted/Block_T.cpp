#include "Block_T.h"
Block_T::Block_T(): Block(){
    Shape[0] = {
        {0, 0, 0},
        {1, 1, 1},
        {0, 1, 0}};
    Shape[1] = {
        {0, 1, 0},
        {1, 1, 0},
        {0, 1, 0}};
    Shape[2] = {
        {0, 0, 0},
        {0, 1, 0},
        {1, 1, 1}};
    Shape[3] = {
        {0, 1, 0},
        {0, 1, 1},
        {0, 1, 0}};
    img = IMG_LoadTexture(Game::renderer, "image/purple.png");
}
Block_T::~Block_T(){}