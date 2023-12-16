#include "MainMenu.h"

bool MainMenu::on = true;
bool MainMenu::isMuted = false;
Audio MainMenu::audioMainMenu;
string MainMenu::playerName = "";

MainMenu::MainMenu()
{
	const char* imagePath = BackgroundManager::GetCurrentBackground();
	SDL_Surface* mainMenuSurface = IMG_Load(imagePath);
	mainMenuTexture = SDL_CreateTextureFromSurface(Game::renderer, mainMenuSurface);
	SDL_FreeSurface(mainMenuSurface);
	for (int i = 0; i < n; i++)
	{
		textBoxes[i];
		textBoxes[i].setX(screen_width / 2);
		textBoxes[i].setY((screen_height - ((n - 1) * 100)) / 2 + i * 100);
	}

	textBoxes[0].setMessage("PLAY");
	textBoxes[1].setMessage("RECORD");
	textBoxes[2].setMessage("ABOUT");
	textBoxes[3].setMessage("TUTORIAL");
	textBoxes[4].setMessage("QUIT");
	audioMainMenu.playBackgroundMusic("audio/Theme.mp3", 30);
	musicPaths[0] = "audio/gameTheme.mp3";
	musicPaths[1] = "audio/Record.mp3";
	musicPaths[2] = "audio/About.mp3";
	musicPaths[3] = "audio/Tutorial.mp3";
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
			audioMainMenu.playBackgroundMusicEffect("audio/ButtonMove.mp3", VOLBM);
			pos -= 1;
			break;
		case SDLK_DOWN:
			audioMainMenu.playBackgroundMusicEffect("audio/ButtonMove.mp3", VOLBM);
			pos += 1;
			break;

		case SDLK_RETURN:
			audioMainMenu.playBackgroundMusicEffect("audio/ButtonPick.mp3", VOLBP);
			if (pos == 0)
			{
				SDL_RenderClear(Game::renderer);
				cout << "INPUT NAME" << endl;
				GetNameInput();
				cout << "GAME START" << endl;
				Game::gameState->Reset();
				audioMainMenu.stopBackgroundMusic();
				Game::audioManager.playBackgroundMusic(musicPaths[0].c_str(), VOLGT);
				on = false;
				Game::on = true;
				SDL_RenderClear(Game::renderer);
			}
			if (pos == 1)
			{
				on = false;
				RecordMenu::on = true;
				ifstream file("Record.txt");
				if (file.is_open())
				{
					RecordMenu::players.clear();
					string line;
					while (getline(file, line))
					{
						istringstream iss(line);
						string playerName;
						int score;

						if (iss >> playerName >> score)
						{
							RecordMenu::players.push_back(make_pair(playerName, score));
						}
					}
					file.close();
					sort(RecordMenu::players.begin(), RecordMenu::players.end(), [](const auto &a, const auto &b) {
						return a.second > b.second;
					});
				}
				int maxPlayers = min(static_cast<int>(RecordMenu::players.size()), 5);
				for (int i = 0; i <= 4; i++)
				{
					if (i < maxPlayers)
					{
						string message = RecordMenu::players[i].first + "   " +to_string(RecordMenu::players[i].second);
						RecordMenu::messages.push_back(message);
						RecordMenu::textBoxes[i].setMessage(RecordMenu::messages[RecordMenu::messages.size() - 1].c_str());
					}
					else
					{
						RecordMenu::textBoxes[i].setMessage("--"); // Set an empty message if there's no player for this position
					}
				}
				cout << RecordMenu::players.size() << " ";
				cout << "RECORD" << endl;
				audioMainMenu.stopBackgroundMusic();
				RecordMenu::audioRecordMenu.playBackgroundMusic(musicPaths[1].c_str(), 30);
			}
			if (pos == 2)
			{
				on = false;
				AboutMenu::on = true;
				cout << "ABOUT" << endl;
				audioMainMenu.stopBackgroundMusic();
				AboutMenu::audioAboutMenu.playBackgroundMusic(musicPaths[2].c_str(), 30);
			}
			if (pos == 3) {
				cout << "TUTORIAL" << endl;
				audioMainMenu.stopBackgroundMusic();
				TutorialMenu::audioTutorialMenu.playBackgroundMusic(musicPaths[3].c_str(), VOLT);
				on = false;
				TutorialMenu::on = true;
			}
			if (pos == 4)
			{
				Game::isRunning = false;
			}
			break;
        case SDLK_q:
            // Toggle mute
            isMuted = !isMuted;
            if (isMuted)
            {
                audioMainMenu.setVolume(0);
            }
            else
            {
                audioMainMenu.setVolume(VOLT); // Set your desired volume level
            }
            break;
        case SDLK_w:
            // Increase volume
            audioMainMenu.setVolume(audioMainMenu.getVolume() + 5); // Increase by 5
            break;

        case SDLK_e:
            // Decrease volume
            audioMainMenu.setVolume(audioMainMenu.getVolume() - 5); // Decrease by 5
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
{ 
	// animate the option selected (change the size)
	for (int i = 0; i < n; i++)
	{ 

		textBoxes[i].setColor(255, 255, 255);
		textBoxes[i].setSize(80);

	}
	textBoxes[pos].setSize(100);
	textBoxes[pos].setColor(255, 255, 0); // put yellow for the one selected
}
void MainMenu::Render()
{
	SDL_SetRenderDrawColor(Game::renderer, 20, 20, 20, 255);
	SDL_RenderClear(Game::renderer);
	SDL_RenderCopy(Game::renderer, mainMenuTexture, NULL, NULL);

	for (int i = 0; i < n; i++)
	{
		textBoxes[i].renderText(Game::renderer, "build/8bit.ttf");
	}
	SDL_RenderPresent(Game::renderer);
}
void MainMenu::GetNameInput()
{
    SDL_StartTextInput();
    bool inputFinished = false;
    string playerName = ""; // Default empty name
    bool showDefaultText = true; // Flag to control showing "ANONYMOUS"

    while (!inputFinished)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    inputFinished = true;
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE && !playerName.empty())
                {
                    playerName.pop_back();
                }
            }
            else if (event.type == SDL_TEXTINPUT)
            {
                playerName += event.text.text;
                showDefaultText = false; // Once user starts typing, hide the default text
            }
        }
        // Clear the screen
        SDL_SetRenderDrawColor(Game::renderer, 20, 20, 20, 255);
        SDL_RenderClear(Game::renderer);

        // Render the input box
        SDL_Rect inputBoxRect = {screen_width / 2 - 150, screen_height / 2 - 50, 300, 100}; // Adjust size and position
        SDL_SetRenderDrawColor(Game::renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(Game::renderer, &inputBoxRect);

        // Render the "INPUT NAME"
		TTF_Font *font = TTF_OpenFont("build/Pixel Sans Serif.ttf", 30);
		if (font == nullptr)
		{
			printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
			SDL_Delay(10000);
		}
		string INPUTNAME = "INPUT YOUR NAME";
		SDL_Color color = {255, 255, 0};
		SDL_Surface *surface = TTF_RenderText_Solid(font, INPUTNAME.c_str(), color);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		SDL_Rect textRect = {screen_width / 2 - 208, screen_height / 2 - 112, surface->w, surface->h};
		SDL_FreeSurface(surface);
		SDL_RenderCopy(Game::renderer, texture, NULL, &textRect);
        // Render the entered text or default text based on the flag
		
        SDL_Color White = {255, 255, 255};
        if (showDefaultText)
        {
            textBox defaultText(screen_width / 2, screen_height / 2, "ANONYMOUS", White, 15);
            defaultText.renderText(Game::renderer, "build/Pixel Sans Serif.ttf");
        }
        else
        {
            textBox inputText(screen_width / 2, screen_height / 2, playerName, White, 15);
            inputText.renderText(Game::renderer, "build/Pixel Sans Serif.ttf");
        }

        SDL_RenderPresent(Game::renderer);
    }
    SDL_StopTextInput();

    // playerName contains the inputted name or is empty if none was given
	string finalName = (playerName.empty() ? "ANONYMOUS" : playerName);
    cout << finalName << endl;
    ofstream recordFile("Record.txt", ios::app);
    if (recordFile.is_open())
    {
        recordFile << finalName;
        recordFile.close();
    }
    else
    {
        cerr << "Unable to open Record.txt for writing." << endl;
    }
}

