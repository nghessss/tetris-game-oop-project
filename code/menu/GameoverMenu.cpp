#include "GameoverMenu.h"

bool GameoverMenu::on = false;
bool GameoverMenu::isMuted = false;
Audio GameoverMenu::audioGameoverMenu;

GameoverMenu::GameoverMenu()
{
	// DISPLAY "GAMEOVER"
	SDL_Surface* surfaceGameOver = IMG_Load("image/effect/gameover.png");
	backgoundGameOver = SDL_CreateTextureFromSurface(Game::renderer, surfaceGameOver);
	SDL_FreeSurface(surfaceGameOver);
	// PLAY GAMEOVER MUSIC
	for (int i = 0; i < n; i++)
	{
		textBoxes[i].setX(screen_width / 2);
		textBoxes[i].setY((screen_height - ((n - 1) * 100)) / 2 + i * 100);
		textBoxes[0].setMessage("PLAY AGAIN");
		textBoxes[1].setMessage("MAIN MENU");
		textBoxes[2].setMessage("QUIT");
	}
};
GameoverMenu::~GameoverMenu(){
	audioGameoverMenu.stopBackgroundMusic();
	SDL_DestroyTexture(backgoundGameOver);
	// SDL_RenderClear(Game::renderer);
};
void GameoverMenu::HandleEvent()
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
			audioGameoverMenu.playBackgroundMusicEffect("audio/ButtonMove.mp3", VOLBM);
			pos -= 1;
			break;
		case SDLK_DOWN:
			audioGameoverMenu.playBackgroundMusicEffect("audio/ButtonMove.mp3", VOLBM);
			pos += 1;
			break;

		case SDLK_RETURN:
			audioGameoverMenu.playBackgroundMusicEffect("audio/ButtonPick.mp3", VOLBP);
			if (pos == 0)
			{ 
				Game::gameState->Reset();
				audioGameoverMenu.stopBackgroundMusic();
				Game::audioManager.playBackgroundMusic("audio/gameTheme.mp3", VOLGT);
				on = false;
				Game::on = true;
				GameState::gameOver = false;
			}
			if (pos == 1)
			{
				on = false;
				audioGameoverMenu.stopBackgroundMusic();
				if (!MainMenu::isMuted)
					MainMenu::audioMainMenu.playBackgroundMusic("audio/Theme.mp3", VOLT);
				GameState::gameOver = false;
				MainMenu::on = true;
			}
			if (pos == 2) {
				GameState::gameOver = false;
				Game::isRunning = false;
			}
			break;
		case SDLK_q:
            // Toggle mute
            isMuted = !isMuted;
            if (isMuted)
            {
                audioGameoverMenu.setVolume(0);
            }
            else
            {
                audioGameoverMenu.setVolume(VOLT); // Set your desired volume level
            }
            break;

        case SDLK_w:
            // Increase volume
            audioGameoverMenu.setVolume(audioGameoverMenu.getVolume() + 5); // Increase by 5
            break;

        case SDLK_e:
            // Decrease volume
            audioGameoverMenu.setVolume(audioGameoverMenu.getVolume() - 5); // Decrease by 5
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
void GameoverMenu::Update()
{
	for (int i = 0; i < n; i++)
	{ // reset all to default
		textBoxes[i].setColor(255, 255, 255);
		textBoxes[i].setSize(20);
	}
	textBoxes[pos].setColor(255, 255, 0); // put yellow for the one selected
	textBoxes[pos].setSize(25);
};
void GameoverMenu::Render()
{
	// // DISPLAY "GAMEOVER"
	TTF_Font *font = TTF_OpenFont("build/novem___.ttf", 100);
    if (font == nullptr)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Delay(10000);
    }
    string GAMEOVER = "GAME OVER";
    SDL_Color color = {0, 255, 0};
    SDL_Surface *surface = TTF_RenderText_Solid(font, GAMEOVER.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_Rect textRect = {80, 180, surface->w, surface->h};
    SDL_FreeSurface(surface);
	// // DISPLAY BACKGROUND
    SDL_Rect rect = {0, 148, 600, 416};
	// // RENDERCOPY
	SDL_RenderCopy(Game::renderer, backgoundGameOver, NULL, &rect);
	SDL_RenderCopy(Game::renderer, texture, NULL, &textRect);
	// // RENDERPRESENT
	SDL_Color White{255, 255, 255};
	for (int i = 0; i < n; i++)
	{
		textBoxes[i].renderText(Game::renderer, "build/Pixel Sans Serif.ttf");
	}

	SDL_RenderPresent(Game::renderer);
};