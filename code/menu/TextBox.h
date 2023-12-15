#pragma once
#ifndef TEXTBOX_H
#define TEXTBOX_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <string>
using namespace std;
// #include "game.h"

class textBox {
private:
	int x;
	int y;
	SDL_Color c;
	const char* message;
	int size;
public:
	textBox();
	~textBox();
	void setX(int x) { this->x = x; };
	void setY(int y) { this->y = y; };
	int getX() { return x; };
	int getY() { return y; };
	void setMessage(const char* message) { this->message = message; };
	void setColor(unsigned char r, unsigned char g, unsigned char b) { this->c = {r, g, b}; };
	void setSize(int size) { this->size = size; };
	void renderText(SDL_Renderer* renderer, int renderX, int renderY, string path);
	void renderText(SDL_Renderer* renderer, string path);
};
#endif