#include "game.h"
int Block::timePos = SDL_GetTicks();
Block::Block()
{
    n = 3;
    Shape.resize(4, vector<vector<int>>(n, vector<int>(n, 0)));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                Shape[i][j][k] = 0;
            }
        }
    }
    num_rotation = 0;
    img = IMG_LoadTexture(Game::renderer, "image/ye.png");
    TopLeft.setX(5);
    TopLeft.setY(0);
}
Block::Block(const Block &other)
{
    n = other.n;
    Shape.resize(4, vector<vector<int>>(n, vector<int>(n, 0)));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                Shape[i][j][k] = other.Shape[i][j][k];
            }
        }
    }
    img = IMG_LoadTexture(Game::renderer, "image/background.png");
    shadowImg = IMG_LoadTexture(Game::renderer, "image/shadow.png");
    num_rotation = other.num_rotation;
    TopLeft = other.TopLeft;
}
void Block::setTopLeft(Point p)
{
    TopLeft = p;
}
void Block::setNumRotation(int num)
{
    num_rotation = num;
}
Block::~Block()
{
    if (img)
    {
        SDL_DestroyTexture(img);
        img = nullptr; // Optional: Set to nullptr to avoid accidental reuse
    }

    if (shadowImg)
    {
        SDL_DestroyTexture(shadowImg);
        shadowImg = nullptr; // Optional: Set to nullptr to avoid accidental reuse
    }
}
vector<vector<vector<int>>> Block::getShape()
{
    return Shape;
}
SDL_Texture *Block::getImg()
{
    return img;
}
SDL_Texture *Block::getShadowImg()
{
    return shadowImg;
}
Point Block::getTopLeft()
{
    return TopLeft;
}
int Block::getNumRotation()
{
    return num_rotation;
}
int Block::getN()
{
    return n;
}
void Block::moveDown()
{
    TopLeft.setY(TopLeft.getY() + 1);
}
void Block::moveLeft()
{
    TopLeft.setX(TopLeft.getX() - 1);
}
void Block::moveRight()
{
    TopLeft.setX(TopLeft.getX() + 1);
}
void Block::changeDirect()
{
    num_rotation = num_rotation + 1;
    if (num_rotation > 3)
    {
        num_rotation = 0;
    }
}
void Block::space(Point targetPoint)
{
    // Move the block down until it reaches the target point
    while (getTopLeft() != targetPoint)
    {
        moveDown();
    }
}
Block& Block::operator=(const Block& other) {
    if (this != &other) {  // Check for self-assignment
        // Deep copy the Shape
        this->Shape.clear();  // Clear existing content
        for (const auto& layer : other.Shape) {
            vector<vector<int>> newLayer;
            for (const auto& row : layer) {
                newLayer.push_back(row);  // Copy each row
            }
            this->Shape.push_back(newLayer);  // Copy each layer
        }

        // Deep copy the SDL_Texture*
        SDL_Surface* imgSurface = IMG_Load("image/your_image.png");  // Replace with the actual image path
        if (imgSurface) {
            this->img = SDL_CreateTextureFromSurface(Game::renderer, imgSurface);
            SDL_FreeSurface(imgSurface);
        } else {
            // Handle error loading the image
            this->img = nullptr;
        }

        // Copy other members
        this->shadowImg = other.shadowImg;
        this->TopLeft = other.TopLeft;
        this->num_rotation = other.num_rotation;
        this->n = other.n;
    }
    return *this;
}
