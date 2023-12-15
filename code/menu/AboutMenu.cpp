#include "AboutMenu.h"
#include "../game.h"

bool AboutMenu::on = false;

AboutMenu::AboutMenu()
{
	const char* imagePath = BackgroundManager::GetCurrentBackground();
	SDL_Surface* aboutMenuSurface = IMG_Load(imagePath);
	aboutMenuTexture = SDL_CreateTextureFromSurface(Game::renderer, aboutMenuSurface);
	SDL_FreeSurface(aboutMenuSurface);

	SDL_Surface* aboutLayout = IMG_Load("image/effect/Blur.png");
	aboutMenuTextureLayout = SDL_CreateTextureFromSurface(Game::renderer, aboutLayout);
	SDL_FreeSurface(aboutLayout);

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
            MainMenu::audioMainMenu.playBackgroundMusicEffect("audio/ButtonMove.mp3", VOLBM);
            pos -= 1;
            break;
        case SDLK_DOWN:
            MainMenu::audioMainMenu.playBackgroundMusicEffect("audio/ButtonMove.mp3", VOLBM);
            pos += 1;
            break;

        case SDLK_RETURN:
            MainMenu::audioMainMenu.playBackgroundMusicEffect("audio/ButtonPick.mp3", VOLBP);
            if (pos == 4) {
				MainMenu::audioMainMenu.stopBackgroundMusic();
				if (!MainMenu::isMuted)
					MainMenu::audioMainMenu.playBackgroundMusic("Audio/theme.mp3", VOLT);
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
    if (pos != n - 1) {
        textBoxes[pos].setColor(253, 204, 0); // put yellow for the one selected
        textBoxes[pos].setSize(20);
    } else {
        textBoxes[pos].setColor(0, 255, 0); // put yellow for the one selected
        textBoxes[pos].setSize(35);
    }
}

void AboutMenu::Render()
{
    SDL_SetRenderDrawColor(Game::renderer, 20, 20, 20, 255);
    SDL_RenderClear(Game::renderer);
    SDL_SetRenderDrawColor(Game::renderer, 20, 20, 20, 255);
    SDL_RenderClear(Game::renderer);
    SDL_RenderCopy(Game::renderer, aboutMenuTexture, NULL, NULL);
    SDL_Rect layout = {0, 96, 600, 608};
    SDL_RenderCopy(Game::renderer, aboutMenuTextureLayout, NULL, &layout);

    for (int i = 0; i < n; i++)
    {
        textBoxes[i].renderText(Game::renderer, "build/FVF Fernando 08.ttf");
    }

    SDL_RenderPresent(Game::renderer);
}
