#include "AboutMenu.h"
#include "../game.h"

bool AboutMenu::on = false;

AboutMenu::AboutMenu()
{
    for (int i = 0; i < n; i++)
    {
        textBoxes[i].setX(screen_width / 2);
        textBoxes[i].setY((screen_height - ((n - 1) * 100)) / 2 + i * 100);
    }
    // Set team members' information for each text box
    textBoxes[0].setMessage("22127047: NGUYEN NGOC MANH CUONG");
    textBoxes[1].setMessage("22127166: TRIEU GIA HUY");
    textBoxes[2].setMessage("22127270: NGUYEN QUANG MINH");
    textBoxes[3].setMessage("22127295: VO THANH NGHIA");
    textBoxes[4].setMessage("BACK TO MENU");
};

AboutMenu::~AboutMenu() {}

void AboutMenu::HandleEvent()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        Game::isRunning = false;
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            pos -= 1;
            break;
        case SDLK_DOWN:
            pos += 1;
            break;

        case SDLK_RETURN:
            if (pos == 4) {
				MainMenu::audioMainMenu.stopBackgroundMusic();
				if (!MainMenu::isMuted)
					MainMenu::audioMainMenu.playBackgroundMusic("Audio/theme.mp3", 10);
				on = false;
				MainMenu::on = true;
			}
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

void AboutMenu::Update()
{
    for (int i = 0; i < n; i++)
    {
        textBoxes[i].setColor(255, 255, 255);
        textBoxes[i].setSize(15);
    }
    textBoxes[pos].setColor(0, 255, 0); // put yellow for the one selected
    textBoxes[pos].setSize(20);
}

void AboutMenu::Render()
{
    SDL_SetRenderDrawColor(Game::renderer, 20, 20, 20, 255);
    SDL_RenderClear(Game::renderer);

    SDL_Color White{255, 255, 255};
    for (int i = 0; i < n; i++)
    {
        textBoxes[i].renderText(Game::renderer, "build/FVF Fernando 08.ttf");
    }

    SDL_RenderPresent(Game::renderer);
}
