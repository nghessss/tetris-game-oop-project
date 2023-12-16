#pragma once
#ifndef TEXTBOX_H
#define TEXTBOX_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <string>
using namespace std;

class textBox {
private:
	int x;
	int y;
	SDL_Color c;
	int size;
	const char* message;
public:
	textBox();
	textBox(int x, int y, const string &text, const SDL_Color &color, int size);
	~textBox();

	//get
	int getX();
	int getY();
	const char* getMessage();

	//set
	void setX(int x);
	void setY(int y);
	void setMessage(const char* message);
	void setColor(unsigned char r, unsigned char g, unsigned char b);
	void setSize(int size);

	//render
	void renderText(SDL_Renderer* renderer, int renderX, int renderY, string path);
	void renderText(SDL_Renderer* renderer, string path);
};
#endif