#include "RecordMenu.h"
#include "../game.h"
#include <fstream>
#include <sstream>
#include <algorithm>

bool RecordMenu::on = false;
vector<pair<string, int>> RecordMenu::players;
vector<string> RecordMenu::messages(5);
textBox RecordMenu::textBoxes[];

Audio RecordMenu::audioRecordMenu;
bool RecordMenu::isMuted = false;
RecordMenu::RecordMenu()
{
    const char *imagePath = BackgroundManager::GetCurrentBackground();
    SDL_Surface *gameoverMenuSurface = IMG_Load(imagePath);
    gameoverMenuTexture = SDL_CreateTextureFromSurface(Game::renderer, gameoverMenuSurface);
    SDL_FreeSurface(gameoverMenuSurface);

    SDL_Surface *gameoverLayout = IMG_Load("image/effect/Blur.png");
    gameoverMenuTextureLayout = SDL_CreateTextureFromSurface(Game::renderer, gameoverLayout);
    SDL_FreeSurface(gameoverLayout);

    for (int i = 0; i < n; i++)
    {
        textBoxes[i].setX(screen_width / 2);
        textBoxes[i].setY((screen_height - ((n - 1) * 100)) / 2 + i * 100);
    }
    for (int i = 0; i < n - 1; i++)
    {
        textBoxes[i].setMessage("--");
    }
    textBoxes[n - 1].setMessage("BACK TO MENU");
}
RecordMenu::~RecordMenu() {}
void RecordMenu::HandleEvent()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            MainMenu::audioMainMenu.playBackgroundMusicEffect("audio/ButtonMove.mp3", VOLBM);
            pos -= 1;
            break;
        case SDLK_DOWN:
            MainMenu::audioMainMenu.playBackgroundMusicEffect("audio/ButtonMove.mp3", VOLBM);
            pos += 1;
            break;
        case SDLK_RETURN:
            MainMenu::audioMainMenu.playBackgroundMusicEffect("audio/ButtonPick.mp3", VOLBP);
            if (pos == 5)
            {
                MainMenu::audioMainMenu.stopBackgroundMusic();
                if (!MainMenu::isMuted)
                    MainMenu::audioMainMenu.playBackgroundMusic("Audio/theme.mp3", 30);
                on = false;
                MainMenu::on = true;
            }
            break;
        case SDLK_q:
            // Toggle mute
            isMuted = !isMuted;
            if (RecordMenu::isMuted)
            {
                RecordMenu::audioRecordMenu.setVolume(0);
            }
            else
            {
                RecordMenu::audioRecordMenu.setVolume(VOLT); // Set your desired volume level
            }
            break;
        case SDLK_w:
            // Increase volume
            RecordMenu::audioRecordMenu.setVolume(RecordMenu::audioRecordMenu.getVolume() + 5); // Increase by 5
            break;

        case SDLK_e:
            // Decrease volume
            RecordMenu::audioRecordMenu.setVolume(RecordMenu::audioRecordMenu.getVolume() - 5); // Decrease by 5
            break;
        default:
            break;
        }
        if (pos == n)
            pos = 0;
        if (pos < 0)
            pos = n - 1;
        break;
    default:
        break;
    }
}
void RecordMenu::Update()
{
    textBoxes[0].setColor(255, 153, 0);
    textBoxes[0].setSize(30);

    for (int i = 1; i < n; i++)
    {
        textBoxes[i].setColor(255, 255, 255);
        textBoxes[i].setSize(15);
    }
    if (pos != 0 && pos != n - 1) {
        textBoxes[pos].setColor(153, 204, 0); // put yellow for the one selected
        textBoxes[pos].setSize(20);
    } 
    else if (pos == 0) {
        textBoxes[pos].setColor(255, 102, 0);
        textBoxes[pos].setSize(35);
    }
    else if (pos == n - 1) {
        textBoxes[pos].setColor(0, 255, 0);
        textBoxes[pos].setSize(35);
    }

}
void RecordMenu::Render()
{
    SDL_SetRenderDrawColor(Game::renderer, 20, 20, 20, 255);
    SDL_RenderClear(Game::renderer);
    SDL_RenderCopy(Game::renderer, gameoverMenuTexture, NULL, NULL);
    SDL_Rect layout = {0, 96, 600, 608};
    SDL_RenderCopy(Game::renderer, gameoverMenuTextureLayout, NULL, &layout);

    for (int i = 0; i < n; i++)
    {
        textBoxes[i].renderText(Game::renderer, "build/Pixel Sans Serif.ttf");
    }
    SDL_RenderPresent(Game::renderer);
    // SDL_DestroyTexture(gameoverMenuTexture);
    // SDL_DestroyTexture(gameoverMenuTextureLayout);
}
