#include "gameState.h"
#include "game.h"
#include "Block_I.h"
#include "Block_O.h"
#include "Block_T.h"
#include "Block_L.h"
#include "Block_Z.h"
#include "Block_S.h"
#include "Block_J.h"
int GameState::timeStart = SDL_GetTicks();
int GameState::currentTime = SDL_GetTicks() - timeStart;

GameState::GameState()
{
    for (int i = 0; i <= rows + 1; ++i)
        for (int j = 0; j <= cols + 1; j++)
            currentGameState[i][j] = NULL;
    blockList.push_back(new Block_T());
    blockList.push_back(new Block_I());
    blockList.push_back(new Block_O());
    blockList.push_back(new Block_L());
    blockList.push_back(new Block_Z());
    blockList.push_back(new Block_S());
    blockList.push_back(new Block_J());
    for (int i = 0; i < 5; i++)
        nextBlock.push(blockList[rand() % 7]);
    currentBlock = blockList[rand() % 7];
    speed = 0.2;
}
Block *GameState::getCurrentBlock()
{
    return currentBlock;
}
SDL_Texture *loadImage(const char *filename)
{
    SDL_Surface *surface = IMG_Load(filename);
    if (surface == nullptr)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError());
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == nullptr)
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", filename, SDL_GetError());
        return nullptr;
    }

    return texture;
}
void GameState::drawGameBorder()
{
    SDL_Texture *borderBlock = loadImage("image/border.png");
    for (int i = 0; i <= cols + 1; ++i)
        currentGameState[rows + 1][i] = borderBlock;
        

    for (int i = 0; i <= rows + 1; ++i)
    {
        currentGameState[i][0] = borderBlock;
        currentGameState[i][cols + 1] = borderBlock;
    }
}
void GameState::drawGameState()
{

    SDL_Texture *backgroundBlock = loadImage("image/background.png");

    for (int i = 0; i <= rows + 1; ++i)
    {
        for (int j = 0; j <= cols + 1; ++j)
        {
            if (currentGameState[i][j] == NULL)
            {
                SDL_Rect rect = {j * blockWidth, i * blockHeight, blockWidth, blockHeight};
                SDL_RenderCopy(Game::renderer, backgroundBlock, nullptr, &rect);
            }
            else
            {
                SDL_Rect rect = {j * blockWidth, i * blockHeight, blockWidth, blockHeight};
                SDL_RenderCopy(Game::renderer, currentGameState[i][j], nullptr, &rect);
            }
        }
    }
}

TTF_Font *loadFont(const char *fontPath, int fontSize)
{
    TTF_Font *font = TTF_OpenFont(fontPath, fontSize);
    if (font == nullptr)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    return font;
}
void GameState::drawTime()
{
    currentTime = SDL_GetTicks() - timeStart;
    int seconds = currentTime / 1000;
    int minutes = seconds / 60;
    seconds = seconds % 60;
    int milliseconds = currentTime % 1000;
    string time = to_string(minutes) + ":" + to_string(seconds) + ":" + to_string(milliseconds);
    cout << time << endl;
    TTF_Font *font = TTF_OpenFont("build/novem___.ttf", 24);
    if (font == nullptr)
    {

        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Delay(10000);
    }
    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, time.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

    SDL_Rect textRect = {(cols + 3) * 32, (rows + 2) * 32, surface->w, surface->h};
    SDL_RenderCopy(Game::renderer, texture, nullptr, &textRect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    // free font
    TTF_CloseFont(font);
}
bool GameState::checkCollapse(Block *block, Point point)
{
    for (int col = 1; col <= cols; col++)
    {
        for (int i = 0; i < block->getN(); i++)
            for (int j = 0; j < block->getN(); j++)
            {
                if (block->getShape()[block->getNumRotation()][i][j] == 1 && currentGameState[point.getY() + i][point.getX() + j] != NULL)
                    return true;
            }
    }
    return false;
}
Point GameState::getCollapsablePoint()
{
    Point point = currentBlock->getTopLeft();
    while (!checkCollapse(currentBlock, Point(point.getX(), point.getY() + 1)))
    {
        point.setY(point.getY() + 1);
    }
    return point;
}
void GameState::updateBlock()
{
    if (SDL_GetTicks() - Block::timePos >= 1000 * speed)
    {
        Block::timePos = SDL_GetTicks();
        Point point = currentBlock->getTopLeft();
        point.setY(point.getY() + 1);
        if (checkCollapse(currentBlock, point) == 0)
        {
            currentBlock->moveDown();
            cout << currentBlock->getTopLeft().getX() << " " << currentBlock->getTopLeft().getY() << endl;
        }
        else
        {
            for (int j = 0; j < currentBlock->getN(); j++)
            {
                for (int k = 0; k < currentBlock->getN(); k++)
                {
                    if (currentBlock->getShape()[currentBlock->getNumRotation()][j][k] == 1)
                        currentGameState[currentBlock->getTopLeft().getY() + j][currentBlock->getTopLeft().getX() + k] = currentBlock->getImg();
                }
            }
            currentBlock->setTopLeft(Point(5, 0));
            cout << currentBlock->getTopLeft().getX() << " " << currentBlock->getTopLeft().getY() << endl;
            currentBlock = nextBlock.front();
            nextBlock.pop();
            nextBlock.push(blockList[rand() % 7]);
        }
    }
}
void GameState::drawBlock()
{
    Point point = currentBlock->getTopLeft();
    for (int j = 0; j < currentBlock->getN(); j++)
    {
        for (int k = 0; k < currentBlock->getN(); k++)
        {
            if (currentBlock->getShape()[currentBlock->getNumRotation()][j][k] == 1 && currentGameState[j+point.getY()][k+point.getX()] == NULL)
            {
                SDL_Rect rect = {(currentBlock->getTopLeft().getX() + k) * blockWidth, (currentBlock->getTopLeft().getY() + j) * blockHeight, blockWidth, blockHeight};
                SDL_RenderCopy(Game::renderer, currentBlock->getImg(), nullptr, &rect);
            }
        }
    }
}
GameState::~GameState()
{
    for (int i = 0; i < blockList.size(); i++)
    {
        delete blockList[i];
    }
}