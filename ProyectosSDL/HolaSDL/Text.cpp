#include "Text.h"

Text::Text(Font* font, float x, float y, int width, int height, const SDL_Color& color, const string& text):
	font(font),position(x,y),width(width),height(height), color(color), text(text)
{
	SDL_Surface *textSurface = TTF_RenderText_Solid(font->getFont(), text.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(font->getRenderer(), textSurface);
	SDL_FreeSurface(textSurface);
}
Text::Text(Font* font, const Vector2D& position, int width, int height, const SDL_Color& color, const string& text) :
	font(font), position(position), width(width), height(height), color(color), text(text)
{
	SDL_Surface *textSurface = TTF_RenderText_Solid(font->getFont(), text.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(font->getRenderer(), textSurface);
	SDL_FreeSurface(textSurface);
}
Text::~Text() {
	SDL_DestroyTexture(textTexture);
}
void Text::setText(const string newText) {
	SDL_DestroyTexture(textTexture);
	SDL_Surface *textSurface = TTF_RenderText_Solid(font->getFont(), newText.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(font->getRenderer(), textSurface);
	SDL_FreeSurface(textSurface);
}

SDL_Rect Text::getRect() {
	return{ (int)position.getX(),(int)position.getY(),width,height };
}

Vector2D Text::setPosition(const Vector2D& newPosition) { 
	return position = newPosition; 
}

Vector2D Text::setPosition(double x, double y) { 
	return position = Vector2D(x, y); 
}

SDL_Color Text::setColor(const SDL_Color& color) { 
	SDL_DestroyTexture(textTexture);
	SDL_Surface *textSurface = TTF_RenderText_Solid(font->getFont(), text.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(font->getRenderer(), textSurface);
	SDL_FreeSurface(textSurface);
	return this->color = color; 
}

void Text::render() const {
	SDL_Rect rect{ (int)position.getX(),(int)position.getY(),width,height };
	SDL_RenderCopy(font->getRenderer(), textTexture, nullptr, &rect);
}