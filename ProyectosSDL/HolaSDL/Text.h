#pragma once

#include "checkML.h"
#include "Font.h"
#include "Vector2D.h"

class Text
{
private:
	Font *_font;
	SDL_Texture *_textTexture;
	SDL_Renderer *_renderer;
	string _text;
	Vector2D _position;
	int _width, _height;
	SDL_Color _color;

public:
	Text(Font *font, float x, float y, int width, int height, const SDL_Color &color, const string &text);
	Text(Font *font, const Vector2D &position, int width, int height, const SDL_Color &color, const string &text);
	~Text();
	void setText(const string newText);
	SDL_Rect getRect() const;
	Vector2D setPosition(const Vector2D &newPosition);
	Vector2D setPosition(double x, double y);
	SDL_Color setColor(const SDL_Color &color);
	void render() const;
};
