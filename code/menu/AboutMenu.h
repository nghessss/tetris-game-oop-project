#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "../game.h"
#include "../Audio.h"
#include "TextBox.h"

class AboutMenu
{
private:
	int pos = 0;
	static const int n = 5;
	textBox textBoxes[n];
public:
	static bool on;
	AboutMenu();
	~AboutMenu();
	void Update();
	void Render();
	void HandleEvent();
};