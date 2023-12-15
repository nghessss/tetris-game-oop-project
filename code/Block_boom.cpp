#include "Block_Boom.h"
Block_Boom::Block_Boom(): Block(){
    n = 1;
    Shape.resize(4, vector<vector<int>>(n, vector<int>(n, 0)));
    Shape[0] = Shape[1] = Shape[2] = Shape[3] ={{1}};
    img = IMG_LoadTexture(Game::renderer, "image/boom.png");
    shadowImg = IMG_LoadTexture(Game::renderer, "image/boomShadow.png");
}
Block_Boom::~Block_Boom(){}