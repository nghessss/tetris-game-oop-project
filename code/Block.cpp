#include "game.h"
Point::Point(int x, int y){
    this->x = x;
    this->y = y;
}
int Point::getX(){
    return x;
}
int Point::getY(){
    return y;
}
void Point::setX(int x){
    this->x = x;
}
void Point::setY(int y){
    this->y = y;
}
int Block::timePos = SDL_GetTicks();
Block::Block(){
    Shape.resize(4);
    for(int i = 0; i < 4; i++){
        Shape[i].resize(3);
        for(int j = 0; j < 3; j++){
            Shape[i][j].resize(3);
        }
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                Shape[i][j][k] = 0;
            }
        }
    }
    num_rotation = 0;
    speed = 0.5;
    TopLeft.setX(5);
    TopLeft.setY(0);
    srand(time(NULL));
    int random = rand() % 7;
    switch(random){
        case 0:
            img = IMG_LoadTexture(Game::renderer, "image/pink.png");
            break;
        case 1:
            img = IMG_LoadTexture(Game::renderer, "image/green1.png");
            break;
        case 2:
            img = IMG_LoadTexture(Game::renderer, "image/green2.png");
            break;
        case 3:
            img = IMG_LoadTexture(Game::renderer, "image/orange.png");
            break;
        case 4:
            img = IMG_LoadTexture(Game::renderer, "image/purple.png");
            break;
        case 5:
            img = IMG_LoadTexture(Game::renderer, "image/red.png");
            break;
        case 6:
            img = IMG_LoadTexture(Game::renderer, "image/yellow.png");
            break;
    }
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
float Block::getSpeed(){
    return speed;
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
Block_I::Block_I(): Block(){
    Shape[0] = {
        {0, 0, 0},
        {1, 1, 1},
        {0, 0, 0}};
    Shape[1] = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0}};
    Shape[2] = {
        {0, 0, 0},
        {1, 1, 1},
        {0, 0, 0}};
    Shape[3] = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0}};
    //chua xu ly point list
}
Block_I::~Block_I(){
}
Block_O::Block_O(): Block(){
    Shape[0] = Shape[1] = Shape[2] = Shape[3] ={{1, 1, 0},
                                                {1, 1, 0},
                                                {0, 0, 0}};
    //chua xu ly point list
}
Block_O::~Block_O(){}
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
    //chua xu ly point list
}
Block_T::~Block_T(){}
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
    //chua xu ly point list
}
Block_L::~Block_L(){}
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
    //chua xu ly point list
}
Block_Z::~Block_Z(){}
Block_S::Block_S(): Block(){
    Shape[0] = {
        {0, 0, 0},
        {0, 1, 1},
        {1, 1, 0}};
    Shape[1] = {
        {1, 0, 0},
        {1, 1, 0},
        {0, 1, 0}};
    Shape[2] = {
        {0, 0, 0},
        {0, 1, 1},
        {1, 1, 0}};
    Shape[3] = {
        {1, 0, 0},
        {1, 1, 0},
        {0, 1, 0}};
    //chua xu ly point list
}
Block_S::~Block_S(){}
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
    //chua xu ly point list
}
Block_J::~Block_J(){}


