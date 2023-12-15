#include "gameState.h"
#include "game.h"
#include "Block_I.h"
#include "Block_O.h"
#include "Block_T.h"
#include "Block_L.h"
#include "Block_Z.h"
#include "Block_S.h"
#include "Block_J.h"
#include "Block_boom.h"
int GameState::timeStart = SDL_GetTicks();
int GameState::currentTime = SDL_GetTicks() - timeStart;
int GameState::score = 0;
int GameState::clearedLines = 0;
bool GameState::checkHold = true;
bool GameState::gameOver = false;
int GameState::bestScore = 0;
int GameState::boomCount = 100;
Block *createBlock()
{
    int random = rand() % 7;
    Block *block = NULL;
    switch (random)
    {
    case 0:
        block = new Block_T();
        break;
    case 1:
        block = new Block_I();
        break;
    case 2:
        block = new Block_O();
        break;
    case 3:
        block = new Block_L();
        break;
    case 4:
        block = new Block_Z();
        break;
    case 5:
        block = new Block_S();
        break;
    case 6:
        block = new Block_J();
        break;
    }
    return block;
}
GameState::GameState()
{
    for (int i = 0; i <= rows + 1; ++i)
        for (int j = 0; j <= cols + 1; j++)
            currentGameState[i][j] = NULL;
    for (int i = 0; i < 2; i++)
    {
        Block *temp = createBlock();
        nextBlock.push(temp);
    }
    holdBlock = NULL;
    currentBlock = createBlock();
    speed = 0.2;
    speedMultiplier = 0.05;
    gameMode = 1;
    boomBlock = new Block_Boom();
    loadBestScore();
}
Block *GameState::getCurrentBlock()
{
    return currentBlock;
}
Block *GameState::getHoldBlock()
{
    return holdBlock;
}
Block *GameState::getBoomBlock()
{
    return boomBlock;
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

    for (int i = 3; i <= rows + 1; ++i)
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

    int seconds = currentTime / 1000;
    int minutes = seconds / 60;
    seconds = seconds % 60;
    int milliseconds = currentTime % 100;

    // string time = "TIME";
    stringstream ss;
    ss
        << setfill('0') << setw(2) << minutes << ":"
        << setfill('0') << setw(2) << seconds << ":"
        << setfill('0') << setw(2) << milliseconds;

    string time_update = ss.str();
    // string time_update = to_string(minutes) + ":" + to_string(seconds) + ":" + to_string(milliseconds);
    // string time_update = to_string(minutes) + ":" + to_string(seconds);

    TTF_Font *font = TTF_OpenFont("build/novem___.ttf", 22);
    TTF_Font *font_update = TTF_OpenFont("build/novem___.ttf", 40);
    if (font == nullptr && font_update == nullptr)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Delay(10000);
    }
    // DISPLAY "TIME"
    // SDL_Color color = {0, 0, 0};
    // SDL_Surface *surface = TTF_RenderText_Solid(font, time.c_str(), color);
    // SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    // SDL_Rect textRect = {(cols + 3) * 32, (rows + (-6)) * 32 - 8, surface->w, surface->h};
    // DISPLAY TIME_UPDATE
    SDL_Color color_update = {255, 255, 255};
    SDL_Surface *surface_update = TTF_RenderText_Solid(font_update, time_update.c_str(), color_update);
    SDL_Texture *texture_update = SDL_CreateTextureFromSurface(Game::renderer, surface_update);
    SDL_Rect textRect_update = {(cols + 3) * 32, (rows + (-4)) * 32 - 16, surface_update->w, surface_update->h};

    // SDL_RenderCopy(Game::renderer, texture, nullptr, &textRect);
    // SDL_DestroyTexture(texture);
    // SDL_FreeSurface(surface);
    SDL_RenderCopy(Game::renderer, texture_update, nullptr, &textRect_update);
    SDL_DestroyTexture(texture_update);
    SDL_FreeSurface(surface_update);
    // free font
    TTF_CloseFont(font);
    TTF_CloseFont(font_update);
}
void GameState::drawBlurBackground()
{
    SDL_Texture *backgroundBlurTextureContain = loadImage("image/effect/NoBlur.png");
    SDL_Texture *backgroundBlurTextureHold = loadImage("image/effect/TextHold.png");
    // HOLD
    SDL_Rect rectHold = {400, 16, 192, 128};
    SDL_RenderCopy(Game::renderer, backgroundBlurTextureContain, NULL, &rectHold);
    SDL_Rect rectHold2 = {400, 16, 192, 32};
    SDL_RenderCopy(Game::renderer, backgroundBlurTextureHold, NULL, &rectHold2);
    // NEXT
    SDL_Rect rectNext = {400, 176, 192, 288};
    SDL_RenderCopy(Game::renderer, backgroundBlurTextureContain, NULL, &rectNext);
    SDL_Rect rectNext2 = {400, 176, 192, 32};
    SDL_RenderCopy(Game::renderer, backgroundBlurTextureHold, NULL, &rectNext2);
    // SCORE TIME
    SDL_Rect rectSTL = {400, 496, 192, 272};
    SDL_RenderCopy(Game::renderer, backgroundBlurTextureContain, NULL, &rectSTL);
    SDL_Rect rectSTL2 = {400, 496, 192, 32};
    SDL_RenderCopy(Game::renderer, backgroundBlurTextureHold, NULL, &rectSTL2);

    SDL_DestroyTexture(backgroundBlurTextureContain);
    SDL_DestroyTexture(backgroundBlurTextureHold);
}
void GameState::drawLines()
{
    TTF_Font *font = TTF_OpenFont("build/novem___.ttf", 40);
    TTF_Font *font_update = TTF_OpenFont("build/novem___.ttf", 40);
    if (font == nullptr && font_update)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Delay(10000);
    }
    // DISPLAY "LINES"
    string LINES = "LINES";
    SDL_Color color = {255, 255, 0};
    SDL_Surface *surface = TTF_RenderText_Solid(font, LINES.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_Rect textRect = {(cols + 3) * 32, (rows + (-2)) * 32, surface->w, surface->h};
    // DISPLAY LINES
    string LINES_update = to_string(clearedLines);
    SDL_Color color_update = {255, 255, 255};
    SDL_Surface *surface_update = TTF_RenderText_Solid(font_update, LINES_update.c_str(), color_update);
    SDL_Texture *texture_update = SDL_CreateTextureFromSurface(Game::renderer, surface_update);
    SDL_Rect textRect_update = {(cols + 7) * 32, (rows + (-2)) * 32, surface_update->w, surface_update->h};

    SDL_RenderCopy(Game::renderer, texture, nullptr, &textRect);
    SDL_RenderCopy(Game::renderer, texture_update, nullptr, &textRect_update);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture_update);
    SDL_FreeSurface(surface_update);
    // free font
    TTF_CloseFont(font);
    TTF_CloseFont(font_update);
}

void GameState::drawScore()
{
    TTF_Font *font = TTF_OpenFont("build/novem___.ttf", 40);
    TTF_Font *font_update = TTF_OpenFont("build/novem___.ttf", 40);
    if (font == nullptr && font_update)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Delay(10000);
    }
    // DISPLAY "SCORE"
    string SCORE = "SCORE";
    SDL_Color color = {255, 255, 0};
    SDL_Surface *surface = TTF_RenderText_Solid(font, SCORE.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_Rect textRect = {(cols + 3) * 32, (rows) * 32, surface->w, surface->h};
    // DISPLAY SCORE
    string SCORE_update = to_string(score);
    SDL_Color color_update = {255, 255, 255};
    SDL_Surface *surface_update = TTF_RenderText_Solid(font_update, SCORE_update.c_str(), color_update);
    SDL_Texture *texture_update = SDL_CreateTextureFromSurface(Game::renderer, surface_update);
    SDL_Rect textRect_update = {(cols + 7) * 32, (rows) * 32, surface_update->w, surface_update->h};

    SDL_RenderCopy(Game::renderer, texture, nullptr, &textRect);
    SDL_RenderCopy(Game::renderer, texture_update, nullptr, &textRect_update);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture_update);
    SDL_FreeSurface(surface_update);
    // free font
    TTF_CloseFont(font);
    TTF_CloseFont(font_update);
}
void GameState::updateScore(int linesCleared)
{
    if (linesCleared == 1)
    {
        score += 10;
    }
    else if (linesCleared == 2)
    {
        score += 30;
    }
    else if (linesCleared == 3)
    {
        score += 50;
    }
    else if (linesCleared > 0)
    {
        score += 80;
    }
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
bool GameState::checkCanChangeDirect(Block *block)
{

    if (!block)
    {
        std::cerr << "Error: Null pointer passed to checkCanChangeDirect." << std::endl;
        return false;
    }
    block->changeDirect();

    if (checkCollapse(block, block->getTopLeft()) == 1)
    {
        while (block->getTopLeft().getX() <= 0)
            block->moveRight();

        while (block->getTopLeft().getX() + block->getN() - 1 > cols)
            block->moveLeft();

        if (checkCollapse(block, block->getTopLeft()) == 1)
        {
            std::cerr << "Error: Check collapse failed after adjustments." << std::endl;
            return false;
        }
    }

    return true;
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
            // cout << currentBlock->getTopLeft().getX() << " " << currentBlock->getTopLeft().getY() << endl;
        }
        else
        {
            for (int j = 0; j < currentBlock->getN(); j++)
            {
                for (int k = 0; k < currentBlock->getN(); k++)
                {
                    if (currentBlock->getShape()[currentBlock->getNumRotation()][j][k] == 1)
                    {
                        currentGameState[currentBlock->getTopLeft().getY() + j][currentBlock->getTopLeft().getX() + k] = currentBlock->getImg();
                        checkHold = true;
                        if (typeid(*currentBlock) == typeid(Block_Boom))
                        {
                            // delete all the block around it
                            SDL_Texture *tempColor = loadImage("image/explosion.png");
                            for (int i = -1; i <= 1; i++)
                            {
                                for (int j = -1; j <= 1; j++)
                                {
                                    if (currentGameState[currentBlock->getTopLeft().getY() + i][currentBlock->getTopLeft().getX() + j] != NULL && currentGameState[currentBlock->getTopLeft().getY() + i][currentBlock->getTopLeft().getX() + j] != currentGameState[rows + 1][cols + 1])
                                    {
                                        currentGameState[currentBlock->getTopLeft().getY() + i][currentBlock->getTopLeft().getX() + j] = NULL;
                                        SDL_Rect rect = {(currentBlock->getTopLeft().getX() + j) * blockWidth, (currentBlock->getTopLeft().getY() + i) * blockHeight, blockWidth, blockHeight};
                                        SDL_RenderCopy(Game::renderer, tempColor, nullptr, &rect);
                                    }
                                }
                            }
                            for (int i = -1; i <= 1; i++){
                                for (int ii = k; ii >= 1; ii--){
                                    currentGameState[currentBlock->getTopLeft().getY() + i][ii] = currentGameState[currentBlock->getTopLeft().getY() + i][ii - 1];
                                }
                            }
                            SDL_RenderPresent(Game::renderer);
                            SDL_DestroyTexture(tempColor);
                            SDL_Delay(50);
                            updateGameStateAfterBoom();
                        }
                    }
                }
            }

            Audio hitSound;
            hitSound.playBackgroundMusicEffect("audio/BlockHit.mp3", 128);
            // SDL_Delay(100);
            currentBlock->setTopLeft(Point(5, 0));
            currentBlock->setNumRotation(0);
            // cout << currentBlock->getTopLeft().getX() << " " << currentBlock->getTopLeft().getY() << endl;
            currentBlock = nextBlock.front();
            nextBlock.pop();
            nextBlock.push(createBlock());
        }
        updateMode();
    }
}
void GameState::drawBlock()
{
    Point point = currentBlock->getTopLeft();
    if (point.getY() == 0)
        return;
    for (int j = 0; j < currentBlock->getN(); j++)
    {
        for (int k = 0; k < currentBlock->getN(); k++)
        {
            if (currentBlock->getShape()[currentBlock->getNumRotation()][j][k] == 1 && currentGameState[j + point.getY()][k + point.getX()] == NULL)
            {
                SDL_Rect rect = {(currentBlock->getTopLeft().getX() + k) * blockWidth, (currentBlock->getTopLeft().getY() + j) * blockHeight, blockWidth, blockHeight};
                SDL_RenderCopy(Game::renderer, currentBlock->getImg(), nullptr, &rect);
            }
        }
    }
}
void GameState::drawShadowBlock()
{
    Point shadowPoint = getCollapsablePoint(); // Get the collapsable point
    if (shadowPoint.getY() <= 1)
        return;
    for (int j = 0; j < currentBlock->getN(); j++)
    {
        for (int k = 0; k < currentBlock->getN(); k++)
        {
            if (currentBlock->getShape()[currentBlock->getNumRotation()][j][k] == 1 && currentGameState[shadowPoint.getY() + j][shadowPoint.getX() + k] == NULL)
            {
                SDL_Rect rect = {(shadowPoint.getX() + k) * blockWidth, (shadowPoint.getY() + j) * blockHeight, blockWidth, blockHeight};
                SDL_RenderCopy(Game::renderer, currentBlock->getShadowImg(), nullptr, &rect);
            }
        }
    }
}
void GameState::drawNext()
{
    int xOffset = cols + 3;
    int yOffset = 6;

    TTF_Font *font = TTF_OpenFont("build/novem___.ttf", 22);
    if (font == nullptr)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Delay(10000);
        return;
    }

    SDL_Color color = {0, 0, 0};

    // Display "NEXT BLOCKS"
    string nextBlocksTitle = "NEXT";
    SDL_Surface *surfaceTitle = TTF_RenderText_Solid(font, nextBlocksTitle.c_str(), color);
    SDL_Texture *textureTitle = SDL_CreateTextureFromSurface(Game::renderer, surfaceTitle);
    SDL_Rect textRectTitle = {xOffset * blockWidth, yOffset * blockWidth - 8, surfaceTitle->w, surfaceTitle->h};

    SDL_RenderCopy(Game::renderer, textureTitle, nullptr, &textRectTitle);
    SDL_DestroyTexture(textureTitle);
    SDL_FreeSurface(surfaceTitle);

    TTF_CloseFont(font);
}
void GameState::drawNextBlocks()
{
    int xOffset = cols + 3;
    int yOffset = 6;

    TTF_Font *font = TTF_OpenFont("build/novem___.ttf", 22);
    if (font == nullptr)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Delay(10000);
        return;
    }

    SDL_Color color = {0, 0, 0};

    // Display the next blocks
    int blockSpacing = 0;
    queue<Block *> tempQueue = nextBlock;
    while (!tempQueue.empty())
    {
        Block *nextBlock = tempQueue.front();

        Point point = nextBlock->getTopLeft();
        for (int i = 0; i < nextBlock->getShape()[nextBlock->getNumRotation()].size(); i++)
        {
            for (int j = 0; j < nextBlock->getShape()[nextBlock->getNumRotation()][i].size(); j++)
            {
                if (nextBlock->getShape()[nextBlock->getNumRotation()][i][j] == 1 && currentGameState[i + point.getY()][j + point.getX()] == NULL)
                {
                    SDL_Rect rect;
                    if (dynamic_cast<Block_O *>(nextBlock) != nullptr)
                        rect = {(xOffset + 1 + j) * blockWidth + 16, (yOffset + 2 + i) * blockHeight - 16, blockWidth, blockHeight};
                    else if (dynamic_cast<Block_I *>(nextBlock) != nullptr)
                        rect = {(xOffset + 1 + j) * blockWidth - 16, (yOffset + i) * blockHeight, blockWidth, blockHeight};
                    else
                        rect = {(xOffset + 1 + j) * blockWidth, (yOffset + 1 + i) * blockHeight - 16, blockWidth, blockHeight};
                    SDL_RenderCopy(Game::renderer, nextBlock->getImg(), nullptr, &rect);
                }
            }
        }
        // Move to the next position
        if (dynamic_cast<Block_O *>(nextBlock) != nullptr)
            blockSpacing = 2;
        else if (dynamic_cast<Block_I *>(nextBlock) != nullptr)
            blockSpacing = 0;
        else
            blockSpacing = 1;
        yOffset += blockSpacing + nextBlock->getN();
        tempQueue.pop();
    }
    TTF_CloseFont(font);
}
void GameState::drawHold()
{
    int xOffset = cols + 3;
    int yOffset = 1;

    TTF_Font *font = TTF_OpenFont("build/novem___.ttf", 22);
    if (font == nullptr)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Delay(10000);
        return;
    }

    SDL_Color color = {0, 0, 0};

    // Display "NEXT BLOCKS"
    string nextBlocksTitle = "HOLD";
    SDL_Surface *surfaceTitle = TTF_RenderText_Solid(font, nextBlocksTitle.c_str(), color);
    SDL_Texture *textureTitle = SDL_CreateTextureFromSurface(Game::renderer, surfaceTitle);
    SDL_Rect textRectTitle = {xOffset * blockWidth, yOffset * blockWidth - 8, surfaceTitle->w, surfaceTitle->h};

    SDL_RenderCopy(Game::renderer, textureTitle, nullptr, &textRectTitle);
    SDL_DestroyTexture(textureTitle);
    SDL_FreeSurface(surfaceTitle);

    TTF_CloseFont(font);
}
void GameState::drawHoldBlock()
{
    int xOffset = cols + 3;
    int yOffset = 1;

    TTF_Font *font = TTF_OpenFont("build/novem___.ttf", 24);
    if (font == nullptr)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Delay(10000);
        return;
    }
    // Display the hold blocks
    Point point = holdBlock->getTopLeft();
    for (int i = 0; i < holdBlock->getShape()[holdBlock->getNumRotation()].size(); i++)
    {
        for (int j = 0; j < holdBlock->getShape()[holdBlock->getNumRotation()][i].size(); j++)
        {
            if (holdBlock->getShape()[holdBlock->getNumRotation()][i][j] == 1 && currentGameState[i + point.getY()][j + point.getX()] == NULL)
            {
                SDL_Rect rect;
                if (dynamic_cast<Block_O *>(holdBlock) != nullptr)
                    rect = {(xOffset + 1 + j) * blockWidth + 16, (yOffset + 2 + i) * blockHeight - 32, blockWidth, blockHeight};
                else if (dynamic_cast<Block_I *>(holdBlock) != nullptr)
                    rect = {(xOffset + 1 + j) * blockWidth - 16, (yOffset + i) * blockHeight - 16, blockWidth, blockHeight};
                else
                    rect = {(xOffset + 1 + j) * blockWidth, (yOffset + i) * blockHeight, blockWidth, blockHeight};
                SDL_RenderCopy(Game::renderer, holdBlock->getImg(), nullptr, &rect);
            }
        }
    }
    TTF_CloseFont(font);
}
void GameState::clearLines()
{
    int linesCleared = 0;

    // Tạo một vector để lưu trữ các chỉ số của các dòng cần xóa
    vector<int> linesToClear;
    for (int i = rows; i >= 1;)
    {
        bool isLineComplete = true;
        for (int j = 1; j <= cols; ++j)
        {
            if (currentGameState[i][j] == NULL)
            {
                isLineComplete = false;
                break;
            }
        }
        if (isLineComplete)
        {
            linesToClear.push_back(i);
            ++linesCleared;
        }
        --i;
    }

    // Hiệu ứng cho từng dòng được xóa
    for (int i : linesToClear)
    {
        SDL_Texture *tempColor = loadImage("image/clear.png");
        for (int k = 1; k <= cols; ++k)
        {
            SDL_Rect rect = {k * blockWidth, i * blockHeight, blockWidth, blockHeight};
            SDL_RenderCopy(Game::renderer, tempColor, nullptr, &rect);
        }
        SDL_RenderPresent(Game::renderer);
        SDL_DestroyTexture(tempColor);
        SDL_Delay(50);

        // Di chuyển các dòng phía trên xuống
        for (int k = i; k > 1; --k)
        {
            copy(currentGameState[k - 1] + 1, currentGameState[k - 1] + cols + 1, currentGameState[k] + 1);
        }

        // Set cleared line to NULL using memset
        memset(currentGameState[1] + 1, 0, cols * sizeof(Block *));

        Audio clearLineAudio;
        clearLineAudio.playBackgroundMusicEffect("audio/ClearLine.mp3", 128);
    }

    clearedLines += linesCleared;
    updateScore(linesCleared);
}
void GameState::holdCurrentBlock()
{
    if (typeid(*currentBlock) == typeid(Block_Boom))
        return;
    if (holdBlock == nullptr)
    {
        holdBlock = currentBlock;
        holdBlock->setTopLeft(Point(5, 0));
        holdBlock->setNumRotation(0);

        currentBlock = nextBlock.front();
        nextBlock.pop();
        nextBlock.push(createBlock());
        checkHold = false;
    }
    else if (typeid(*holdBlock) != typeid(*currentBlock) && checkHold)
    {
        Block *temp = currentBlock;
        currentBlock = holdBlock;
        currentBlock->setTopLeft(Point(5, 0));

        holdBlock = temp;
        holdBlock->setTopLeft(Point(5, 0));
        holdBlock->setNumRotation(0);
        checkHold = false;
    }
}
GameState::~GameState()
{
    delete currentBlock;
    delete holdBlock;
}
void GameState::updateMode()
{
    if (gameMode == 1)
    {
        int elapsedSeconds = currentTime / 1000.0;
        elapsedSeconds = elapsedSeconds % 60;
        if ((elapsedSeconds % 10 == 0) && (speed > 0.15))
        {
            speed = speed - speedMultiplier * elapsedSeconds / 1000;
        }
    }
    if (gameMode == 2)
    {
        if (clearedLines >= 10)
        {
            Game::isRunning = false;
        }
    }
}
void GameState::freeTheBoard()
{
    for (int i = 1; i <= rows; ++i)
        for (int j = 1; j <= cols; j++)
        {
            if (currentGameState[i][j] != NULL)
                currentGameState[i][j] = loadImage("image/ice.png");
        }
}
void GameState::checkGameOver()
{
    for (int i = 1; i <= cols; ++i)
        if (currentGameState[2][i] != NULL || currentGameState[1][i] != NULL)
        {
            gameOver = true;
            cout << "GAME OVER" << endl;
            freeTheBoard();
            updateBestScore();
            saveBestScore();
            return;
        }
}
void GameState::loadBestScore()
{
    ifstream file;
    file.open("bestScore.txt");
    if (file.is_open())
    {
        file >> bestScore;
    }
    file.close();
}
void GameState::saveBestScore()
{
    ofstream file;
    file.open("bestScore.txt");
    if (file.is_open())
    {
        file << bestScore;
    }
    file.close();
}
void GameState::updateBestScore()
{
    if (score > bestScore)
    {
        bestScore = score;
    }
}
void GameState::setCurrentBlock(Block *block)
{
    currentBlock = block;
}
void GameState::drawBoomBlockLeft()
{
    for(int i = 0; i < boomCount; i ++)
    {
        SDL_Texture *boomBlockLeft = loadImage("image/boom.png");
        SDL_Rect rect = {(cols + 3 + i) * 32, (rows + (-6)) * 32 - 16, 32, 32};
        SDL_RenderCopy(Game::renderer, boomBlockLeft, nullptr, &rect);
        SDL_DestroyTexture(boomBlockLeft);
    }
}
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
void DFS(int d[][cols+2],int color,int x,int y,SDL_Texture *currentGameState[rows+2][cols+2]){
    if (x < 1 || x > rows + 1 || y < 1 || y > cols) return;
    d[x][y] = color;
    for(int i=0;i<4;i++){
        int u = x + dx[i];
        int v = y + dy[i];
        if(d[u][v] == 0 && (currentGameState[u][v] != NULL || u == rows + 1)){
            DFS(d,color,u,v,currentGameState);
        }
    }
}

void GameState::updateGameStateAfterBoom(){
    int color = 1;
    do{
        int d[rows+2][cols+2];
        memset(d,0,sizeof(d));
        color = 1;
        for (int i = rows+1; i >= 1; i--)
            for (int j = 1; j <= cols; j++)
                if ((i == rows + 1 || currentGameState[i][j] != NULL) && d[i][j] == 0){
                    DFS(d,color,i,j,currentGameState);
                    color++;
                }
        for (int i = 1; i <= rows + 1; i++){
            for (int j = 1; j <= cols; j++)
                cout << d[i][j] << " ";
            cout << endl;
        }
        for (int i = rows; i >= 1; i--)
            for (int j = 1; j <= cols; j++)
                if (d[i][j] == 0 && d[i][j-1] != 1){
                    d[i][j] = d[i][j-1];
                    currentGameState[i][j] = currentGameState[i-1][j];
                }else if (d[i][j] != 0 && d[i][j-1] == 0){
                    d[i][j-1] = d[i][j];
                    currentGameState[i-1][j] = currentGameState[i][j];
                }
    }while(color > 2);
}