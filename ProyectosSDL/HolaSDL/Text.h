#pragma once

#include "Font.h"
#include "Vector2D.h"

class Text
{
private:
	Font *font;
	SDL_Texture *textTexture;
	SDL_Renderer *renderer;
	string text;
	Vector2D position;
	int width, height;
	SDL_Color color;

public:
	Text(Font *font, float x, float y, int width, int height, const SDL_Color &color, const string &text);
	Text(Font *font, const Vector2D &position, int width, int height, const SDL_Color &color, const string &text);
	~Text();
	void setText(const string newText);
	SDL_Rect getRect();
	Vector2D setPosition(const Vector2D &newPosition);
	Vector2D setPosition(double x, double y);
	SDL_Color setColor(const SDL_Color &color);
	void render() const;
};
