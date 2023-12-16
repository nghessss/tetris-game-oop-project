#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "../game.h"
#include "../Audio.h"
#include "TextBox.h"

class RecordMenu
{
private:
	int pos = 0;
	static const int n = 6;
	SDL_Texture* gameoverMenuTexture;
	SDL_Texture* gameoverMenuTextureLayout;
public:
	static Audio audioRecordMenu;
	static bool isMuted;
	static textBox textBoxes[n];
	static vector<pair<string, int>> players;
	static vector<string> messages;
	static bool on;
	RecordMenu();
	~RecordMenu();
	void Update();
	void Render();
	void HandleEvent();
};