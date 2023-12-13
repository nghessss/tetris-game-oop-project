#include "game.h"

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isRunning = false;
Game::Game(const char *title, int xPos, int yPos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "Subsystems Initialized" << endl;
        window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
        if (window)
        {
            cout << "Window Created" << endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 51, 0, 25, 255);
            cout << "Renderer Created" << endl;
        }

        isRunning = true;
        gameState = new GameState();
    }
    else
    {
        isRunning = false;
    }

    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }
}
void Game::HandleEvent()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }

    static int leftKeyDelay = 0;
    static int downKeyDelay = 0;
    static int rightKeyDelay = 0;
    static int downLeftKeyDelay = 0;
    static int downRightKeyDelay = 0;
    static bool upKeyReleased = true;
    static bool isFallingFromSpace = false;

    int32_t key_count;
    const uint8_t *key_states = SDL_GetKeyboardState(&key_count);
    Point point = gameState->getCurrentBlock()->getTopLeft();
    if (key_states[SDL_SCANCODE_UP])
    {
        if (upKeyReleased)
        {
            gameState->getCurrentBlock()->changeDirect();
            upKeyReleased = false;
        }
    }
    else
    {
        upKeyReleased = true;
    }

    if (key_states[SDL_SCANCODE_SPACE]) {
        if (!isFallingFromSpace) {
            Point targetPoint = gameState->getCollapsablePoint();

            while (gameState->getCurrentBlock()->getTopLeft() != targetPoint) {
                gameState->getCurrentBlock()->moveDown();
            }

            isFallingFromSpace = true;
        }
    }
    else {
        isFallingFromSpace = false;
    }

    if (key_states[SDL_SCANCODE_DOWN] && key_states[SDL_SCANCODE_LEFT])
    {
        downLeftKeyDelay++;
        if (downLeftKeyDelay == key_delay_constant)
        {
            point.setY(point.getY() + 1);
            point.setX(point.getX() - 1);
            if (gameState->checkCollapse(gameState->getCurrentBlock(), point) == 0)
            {
                gameState->getCurrentBlock()->moveDown();
                gameState->getCurrentBlock()->moveLeft();
            }
            downLeftKeyDelay = 0;
        }
    }
    else if (key_states[SDL_SCANCODE_DOWN] && key_states[SDL_SCANCODE_RIGHT])
    {
        downRightKeyDelay++;
        if (downRightKeyDelay == key_delay_constant)
        {
            point.setY(point.getY() + 1);
            point.setX(point.getX() + 1);
            if (gameState->checkCollapse(gameState->getCurrentBlock(), point) == 0)
            {
                gameState->getCurrentBlock()->moveDown();
                gameState->getCurrentBlock()->moveRight();
            }

            downRightKeyDelay = 0;
        }
    }
    else
    {
        if (key_states[SDL_SCANCODE_DOWN])
        {
            downKeyDelay++;
            if (downKeyDelay == key_delay_constant)
            {
                point.setY(point.getY() + 1);
                if (gameState->checkCollapse(gameState->getCurrentBlock(), point) == 0)
                    gameState->getCurrentBlock()->moveDown();
                downKeyDelay = 0;
            }
        }
        else
        {
            if (key_states[SDL_SCANCODE_LEFT])
            {
                leftKeyDelay++;
                if (leftKeyDelay == key_delay_constant)
                {
                    
                    point.setX(point.getX() - 1);
                    if (gameState->checkCollapse(gameState->getCurrentBlock(), point) == 0)
                        gameState->getCurrentBlock()->moveLeft();
                    leftKeyDelay = 0;
                }
            }

            if (key_states[SDL_SCANCODE_RIGHT])
            {
                rightKeyDelay++;
                if (rightKeyDelay == key_delay_constant)
                {
                    point.setX(point.getX() + 1);
                    if (gameState->checkCollapse(gameState->getCurrentBlock(), point) == 0)
                        gameState->getCurrentBlock()->moveRight();
                    rightKeyDelay = 0;
                }
            }
        }
    }
}
void updateTime()
{
}
void Game::Update()
{
    updateTime();
    gameState->updateBlock();
    gameState->clearLines();
}
void Game::Renderer()
{
    SDL_RenderClear(renderer);
    // This is where we would add stuff to render
    gameState->drawGameBorder();
    gameState->drawGameState();
    gameState->drawTime();
    gameState->drawBlock();
    SDL_RenderPresent(renderer);
}
void Game::Clean()
{
    delete gameState;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    TTF_Quit();
    cout << "Game Cleaned" << endl;
}
bool Game::Running()
{
    return isRunning;
}
Game::~Game()
{
    Clean();
}