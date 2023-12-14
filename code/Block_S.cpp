#include "Block_S.h"
Block_S::Block_S(): Block(){
    Shape[0] = {
        {0, 0, 0},
        {0, 1, 1},
        {1, 1, 0}};
    Shape[1] = {
        {0, 1, 0},
        {0, 1, 1},
        {0, 0, 1}};
    Shape[2] = {
        {0, 0, 0},
        {0, 1, 1},
        {1, 1, 0}};
    Shape[3] = {
        {1, 0, 0},
        {1, 1, 0},
        {0, 1, 0}};
    img = IMG_LoadTexture(Game::renderer, "image/green1.png");
    shadowImg = IMG_LoadTexture(Game::renderer, "image/shadow.png");
}
Block_S::~Block_S(){}
