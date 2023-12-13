#include "game.h"
int Block::timePos = SDL_GetTicks();
Block::Block(){
    n = 3;
    Shape.resize(4, vector<vector<int>>(n, vector<int>(n, 0)));
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                Shape[i][j][k] = 0;
            }
        }
    }
    num_rotation = 0;
    img = IMG_LoadTexture(Game::renderer, "image/ye.png");
    TopLeft.setX(5);
    TopLeft.setY(0);
}
void Block::setTopLeft(Point p){
    TopLeft = p;
}
Block::~Block(){
}
vector<vector<vector<int>>> Block::getShape(){
    return Shape;
}
SDL_Texture* Block::getImg(){
    return img;
}
SDL_Texture* Block::getShadowImg(){
    return shadowImg;
}
Point Block::getTopLeft(){
    return TopLeft;
}
int Block::getNumRotation(){
    return num_rotation;
}
int Block::getN(){
    return n;
}
void Block::moveDown(){
    TopLeft.setY(TopLeft.getY() + 1);
}
void Block::moveLeft(){
     TopLeft.setX(TopLeft.getX() - 1);
}
void Block::moveRight(){
    TopLeft.setX(TopLeft.getX() + 1);
}
void Block::changeDirect(){
    num_rotation = num_rotation + 1;
    if(num_rotation > 3){
        num_rotation = 0;
    }
}
void Block::space(Point targetPoint) {
    // Move the block down until it reaches the target point
    while (getTopLeft() != targetPoint) {
        moveDown();
    }
}
