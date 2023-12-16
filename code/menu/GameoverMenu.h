#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "../game.h"
#include "../Audio.h"
#include "TextBox.h"

using namespace std;

class GameoverMenu
{
private:
	int pos = 0;
	int n = 3;
	textBox textBoxes[3];
	SDL_Texture* backgoundGameOver;
public:
	static bool isMuted;
	static Audio audioGameoverMenu;
	static bool on;
	GameoverMenu();
	~GameoverMenu();
	void Update();
	void Render();
	void HandleEvent();
};