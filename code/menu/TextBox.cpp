#include "TextBox.h"

textBox::textBox() {
	x = 0;
	y = 0;
	c = { 255,255,255 };
	message = "INIT";
	size = 200;
};
textBox::textBox(int x, int y, const std::string &text, const SDL_Color &color, int size)
    : x(x), y(y), message(text.c_str()), c(color), size(size) {}
textBox::~textBox() {};


int textBox::getX() 
{ 
    return x; 
}
int textBox::getY() 
{ 
    return y; 
}
const char* textBox::getMessage() 
{ 
    return message; 
}

void textBox::setX(int x) 
{ 
    this->x = x; 
}
void textBox::setY(int y) 
{ 
    this->y = y; 
}
void textBox::setMessage(const char* message) 
{ 
    this->message = message; 
}
void textBox::setColor(unsigned char r, unsigned char g, unsigned char b) 
{ 
    this->c = {r, g, b}; 
}
void textBox::setSize(int size) 
{ 
    this->size = size; 
}

void textBox::renderText(SDL_Renderer* renderer, string path) {

	TTF_Init();
	TTF_Font* FONT = TTF_OpenFont(path.c_str(), size);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(FONT, message, c);
	TTF_CloseFont(FONT);
	TTF_Quit();

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect

	Message_rect.w = surfaceMessage->w; // controls the width of the rect
	Message_rect.h = surfaceMessage->h; // controls the height of the rect
	Message_rect.x = x - (Message_rect.w /2);  //controls the rect's x coordinate 
	Message_rect.y = y - (Message_rect.h / 2); // controls the rect's y coordinte

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}
void textBox::renderText(SDL_Renderer* renderer, int renderX, int renderY, string path) {
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);  
    if (font == nullptr) {
        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Blended(font, message, c);
    if (surface == nullptr) {
        TTF_CloseFont(font);
        std::cerr << "Failed to create text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        std::cerr << "Failed to create text texture! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Rect dstRect = {renderX, renderY, surface->w, surface->h}; // Use the specified rendering position
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

