#include "game.h"
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
    TopLeft.setX(5);
    TopLeft.setY(0);
}
Block::~Block(){
}
vector<vector<vector<int>>> Block::getShape(){
    return Shape;
}
SDL_Texture* Block::getImg(){
    return img;
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
int Block::getTimePos(){
    return timePos;
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
void Block::space(){
    while(true){
        moveDown();
    }
}