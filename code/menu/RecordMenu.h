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
	static textBox textBoxes[n];
	static bool isMuted;
	static Audio audioRecordMenu;
	static bool on;
	static vector<pair<string, int>> players;
	static vector<string> messages;
	
	RecordMenu();
	~RecordMenu();
	void Update();
	void Render();
	void HandleEvent();
};