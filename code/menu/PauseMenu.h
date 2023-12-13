#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "../game.h"
#include "TextBox.h"

class PauseMenu
{
private:
	int pos = 0;
	int n = 3;
	textBox textBoxes[3];
public:
	static bool on;
	PauseMenu();
	~PauseMenu();
	void Update();
	void Render();
	void HandleEvent();
};