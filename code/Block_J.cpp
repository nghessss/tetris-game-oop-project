#include"Block_J.h"
Block_J::Block_J(): Block(){
    Shape[0] = {
        {0, 0, 0},
        {1, 1, 1},
        {0, 0, 1}};
    Shape[1] = {
        {0, 1, 0},
        {0, 1, 0},
        {1, 1, 0}};
    Shape[2] = {
        {0, 0, 0},
        {1, 0, 0},
        {1, 1, 1}};
    Shape[3] = {
        {0, 1, 1},
        {0, 1, 0},
        {0, 1, 0}};
    img = IMG_LoadTexture(Game::renderer, "image/pink.png");
    shadowImg = IMG_LoadTexture(Game::renderer, "image/shadow.png");
}
Block_J::~Block_J(){}