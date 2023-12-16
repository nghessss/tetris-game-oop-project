#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "../game.h"
#include "../Audio.h"
#include "TextBox.h"

class TutorialMenu
{
private:
	int pos = 0;
	static const int n = 1;
	textBox textBoxes[n];
	SDL_Texture* tutorialMenuTexture;
	SDL_Texture* tutorialMenuTextureLayout;
public:
	static bool isMuted;
	static Audio audioTutorialMenu;
	static bool on;
	TutorialMenu();
	~TutorialMenu();
	void Update();
	void Render();
	void HandleEvent();
};