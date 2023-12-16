#include "PauseMenu.h"

bool PauseMenu::on = false;
Audio PauseMenu::audioPauseMenu;
bool PauseMenu::isMuted = false;

PauseMenu::PauseMenu()
{
	const char *imagePath = BackgroundManager::GetCurrentBackground();
	SDL_Surface *pauseMenuSurface = IMG_Load(imagePath);
	pauseMenuTexture = SDL_CreateTextureFromSurface(Game::renderer, pauseMenuSurface);
	SDL_FreeSurface(pauseMenuSurface);
	for (int i = 0; i < n; i++)
	{
		textBoxes[i].setX(screen_width / 2);
		textBoxes[i].setY((screen_height - ((n - 1) * 100)) / 2 + i * 100);
		textBoxes[0].setMessage("CONTINUE");
		textBoxes[1].setMessage("MAIN MENU");
		textBoxes[2].setMessage("QUIT");
	}
};
PauseMenu::~PauseMenu()
{
	audioPauseMenu.stopBackgroundMusic();
	SDL_DestroyTexture(pauseMenuTexture);
};
void PauseMenu::HandleEvent()
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
			audioPauseMenu.playBackgroundMusicEffect("audio/ButtonMove.mp3", VOLBM);
			pos -= 1;
			break;
		case SDLK_DOWN:
			audioPauseMenu.playBackgroundMusicEffect("audio/ButtonMove.mp3", VOLBM);
			pos += 1;
			break;

		case SDLK_RETURN:
			audioPauseMenu.playBackgroundMusicEffect("audio/ButtonPick.mp3", VOLBP);
			if (pos == 0)
			{
				on = false;
				audioPauseMenu.stopBackgroundMusic();
				Game::audioManager.playBackgroundMusic("audio/gameTheme.mp3", VOLGT);
				Game::on = true;
			}
			if (pos == 1)
			{
				// delete Game::game;
				GameState::saveBestScore();
				on = false;
				audioPauseMenu.stopBackgroundMusic();
				if (!MainMenu::isMuted)
					MainMenu::audioMainMenu.playBackgroundMusic("audio/Theme.mp3", VOLT);
				MainMenu::on = true;
			}
			if (pos == 2)
			{
				GameState::saveBestScore();
				Game::isRunning = false;
			}
			break;
		case SDLK_q:
            // Toggle mute
            isMuted = !isMuted;
            if (isMuted)
            {
                audioPauseMenu.setVolume(0);
            }
            else
            {
                audioPauseMenu.setVolume(VOLT); // Set your desired volume level
            }
            break;
        case SDLK_w:
            // Increase volume
            audioPauseMenu.setVolume(audioPauseMenu.getVolume() + 5); // Increase by 5
            break;

        case SDLK_e:
            // Decrease volume
            audioPauseMenu.setVolume(audioPauseMenu.getVolume() - 5); // Decrease by 5
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
};
void PauseMenu::Update()
{
	for (int i = 0; i < n; i++)
	{ // reset all to default
		textBoxes[i].setColor(255, 255, 255);
		textBoxes[i].setSize(80);
	}
	textBoxes[pos].setColor(255, 255, 0); // put yellow for the one selected
	textBoxes[pos].setSize(100);
};
void PauseMenu::Render()
{
	SDL_SetRenderDrawColor(Game::renderer, 20, 20, 20, 255);
	SDL_RenderClear(Game::renderer);
	SDL_RenderCopy(Game::renderer, pauseMenuTexture, NULL, NULL);
	for (int i = 0; i < n; i++)
	{
		textBoxes[i].renderText(Game::renderer, "build/8bit.ttf");
	}

	SDL_RenderPresent(Game::renderer);
};