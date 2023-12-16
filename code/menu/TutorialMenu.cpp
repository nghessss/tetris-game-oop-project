#include "TutorialMenu.h"

bool TutorialMenu::on = false;
bool  TutorialMenu::isMuted = false;
Audio TutorialMenu::audioTutorialMenu;

TutorialMenu::TutorialMenu()
{
	// const char* imagePath = BackgroundManager::GetCurrentBackground();
	SDL_Surface* tutorialMenuSurface = IMG_Load("image/effect/Tutorial.png");
	tutorialMenuTexture = SDL_CreateTextureFromSurface(Game::renderer, tutorialMenuSurface);
	SDL_FreeSurface(tutorialMenuSurface);

	SDL_Surface* TutorialLayout = IMG_Load("image/effect/blur.png");
	tutorialMenuTextureLayout = SDL_CreateTextureFromSurface(Game::renderer, TutorialLayout);
	SDL_FreeSurface(TutorialLayout);

    textBoxes[0].setX(screen_width / 2);
    textBoxes[0].setY((screen_height - ((n - 1) * 100)) / 2 + 2 * 100 + 32 + 32 + 16 + 32);
    textBoxes[0].setMessage("PRESS ENTER");
};
TutorialMenu::~TutorialMenu() {}
void TutorialMenu::HandleEvent()
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
            audioTutorialMenu.playBackgroundMusicEffect("audio/ButtonMove.mp3", VOLBM);
            pos -= 1;
            break;
        case SDLK_DOWN:
            audioTutorialMenu.playBackgroundMusicEffect("audio/ButtonMove.mp3", VOLBM);
            pos += 1;
            break;
        case SDLK_RETURN:
            audioTutorialMenu.playBackgroundMusicEffect("audio/ButtonPick.mp3", VOLBP);
            if (pos == 0) {
				audioTutorialMenu.stopBackgroundMusic();
				if (!MainMenu::isMuted)
					MainMenu::audioMainMenu.playBackgroundMusic("Audio/theme.mp3", VOLT);
				on = false;
				MainMenu::on = true;
			}
            break;
        case SDLK_q:
            // Toggle mute
            isMuted = !isMuted;
            if (isMuted)
            {
                audioTutorialMenu.setVolume(0);
            }
            else
            {
                audioTutorialMenu.setVolume(VOLT); // Set your desired volume level
            }
            break;

        case SDLK_w:
            // Increase volume
            audioTutorialMenu.setVolume(audioTutorialMenu.getVolume() + 5); // Increase by 5
            break;

        case SDLK_e:
            // Decrease volume
            audioTutorialMenu.setVolume(audioTutorialMenu.getVolume() - 5); // Decrease by 5
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
void TutorialMenu::Update()
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
        textBoxes[pos].setColor(255, 0, 0); // put yellow for the one selected
        textBoxes[pos].setSize(35);
    }
}
void TutorialMenu::Render()
{

    SDL_SetRenderDrawColor(Game::renderer, 20, 20, 20, 255);
    SDL_RenderClear(Game::renderer);
    SDL_RenderCopy(Game::renderer, tutorialMenuTextureLayout, NULL, NULL);
    SDL_Rect img = {0, 0, 600, 684};
    SDL_RenderCopy(Game::renderer, tutorialMenuTexture, NULL, &img);
    for (int i = 0; i < n; i++)
    {
        textBoxes[i].renderText(Game::renderer, "build/FVF Fernando 08.ttf");
    }

    SDL_RenderPresent(Game::renderer);
}
