#include "MainMenu.h"

bool MainMenu::on = true;
bool MainMenu::isMuted = false;
Audio MainMenu::audioMainMenu;

MainMenu::MainMenu()
{
	const char* imagePath = BackgroundManager::GetCurrentBackground();
	SDL_Surface* mainMenuSurface = IMG_Load(imagePath);
	mainMenuTexture = SDL_CreateTextureFromSurface(Game::renderer, mainMenuSurface);
	SDL_FreeSurface(mainMenuSurface);
	for (int i = 0; i < n - 1; i++)
	{
		textBoxes[i];
		textBoxes[i].setX(screen_width / 2);
		textBoxes[i].setY((screen_height - ((n - 1) * 100)) / 2 + i * 100);
	}
	textBoxes[4];
	textBoxes[4].setX(500);
	textBoxes[4].setY(750);

	textBoxes[0].setMessage("PLAY");
	textBoxes[1].setMessage("RECORD");
	textBoxes[2].setMessage("ABOUT");
	textBoxes[3].setMessage("QUIT");
	textBoxes[4].setMessage("MUTED");
	audioMainMenu.playBackgroundMusic("audio/Theme.mp3", 10);
	musicPaths[0] = "audio/gameTheme.mp3";
	musicPaths[1] = "audio/Theme.mp3";
	musicPaths[2] = "audio/About.mp3";
	musicPaths[3] = "";
	musicPaths[4] = "";
}
MainMenu::~MainMenu() {
	audioMainMenu.stopBackgroundMusic();
	SDL_DestroyTexture(mainMenuTexture);
}
void MainMenu::HandleEvent()
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
			if (pos == 0)
			{
				cout << "GAME START" << endl;
				audioMainMenu.stopBackgroundMusic();
				audioMainMenu.playBackgroundMusic(musicPaths[0].c_str(), 40);
				SDL_RenderClear(Game::renderer);
				on = false;
				Game::on = true;
			}
			if (pos == 1)
			{
				cout << "RECORD" << endl;
				audioMainMenu.playBackgroundMusic(musicPaths[1].c_str(), 10);
			}

			if (pos == 2)
			{
				on = false;
				AboutMenu::on = true;
				cout << "ABOUT" << endl;
				audioMainMenu.playBackgroundMusic(musicPaths[2].c_str(), 10);
			}
			if (pos == 3)
				Game::isRunning = false;
			if (pos == 4)
			{
				// isMuted = !isMuted;
				if (!isMuted) {
					cout << "STOP MUSIC" << endl;
					audioMainMenu.stopBackgroundMusic();
				} else {
					cout << "PLAY MUSIC" << endl;
					audioMainMenu.playBackgroundMusic("audio/Theme.mp3", 10);
				}
				isMuted = !isMuted;
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
void MainMenu::Update()
{ // animate the option selected (change the size)
	for (int i = 0; i < n; i++)
	{ // reset all to default
		if (i != 4) {
			textBoxes[i].setColor(255, 255, 255);
			textBoxes[i].setSize(80);
		} else {
			textBoxes[4].setColor(255, 255, 255);
			textBoxes[4].setSize(50);
		}
	}
	if (pos != 4) {
		textBoxes[pos].setSize(100);
		textBoxes[pos].setColor(255, 255, 0); // put yellow for the one selected
	} else {
		textBoxes[pos].setSize(55);
		textBoxes[pos].setColor(255, 255, 0); // put yellow for the one selected
	}
}
void MainMenu::Render()
{
	SDL_SetRenderDrawColor(Game::renderer, 20, 20, 20, 255);
	SDL_RenderClear(Game::renderer);
	SDL_RenderCopy(Game::renderer, mainMenuTexture, NULL, NULL);

	SDL_Color White = {255, 255, 255};
	for (int i = 0; i < n - 1; i++)
	{
		textBoxes[i].renderText(Game::renderer, "build/8bit.ttf");
	}
	textBoxes[4].renderText(Game::renderer, textBoxes[4].getX(), textBoxes[4].getY(), "build/8bit.ttf");
	SDL_RenderPresent(Game::renderer);
}
