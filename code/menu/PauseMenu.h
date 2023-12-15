#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "../game.h"
#include "../Audio.h"
#include "TextBox.h"
#define VOLUME_BLKMOVE 50
#define VOLUME_BLKPICK 70

class PauseMenu
{
private:
	int pos = 0;
	int n = 3;
	textBox textBoxes[3];
	SDL_Texture* pauseMenuTexture;

public:
	static Audio audioPauseMenu;
	static bool on;
	PauseMenu();
	~PauseMenu();
	void Update();
	void Render();
	void HandleEvent();
};