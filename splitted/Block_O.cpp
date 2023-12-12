#include "Block_O.h"
Block_O::Block_O(): Block(){
    n = 2;
    Shape.resize(4, vector<vector<int>>(n, vector<int>(n, 0)));
    Shape[0] = Shape[1] = Shape[2] = Shape[3] ={{1 ,1},
                                                {1, 1}};
    img = IMG_LoadTexture(Game::renderer, "image/ye.png");
}
Block_O::~Block_O(){}