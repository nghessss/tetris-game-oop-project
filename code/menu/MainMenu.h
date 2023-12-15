#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "../game.h"
#include "../Audio.h"
#include "../BackgroundManager.h"
#include "TextBox.h"
#include "AboutMenu.h"
#include <string>
#define VOLUME_BLKMOVE 60
#define VOLUME_BLKPICK 60
using namespace std;

class MainMenu
{
private:
	int pos = 0;
	static const int n = 5;
	textBox textBoxes[n];
    string musicPaths[n];
	SDL_Texture* mainMenuTexture;
public:
	static bool isMuted;
	static Audio audioMainMenu;
	static bool on;
	MainMenu();
	~MainMenu();
	void RenderTeamDetails();
	void Update();
	void Render();
	void HandleEvent();
};