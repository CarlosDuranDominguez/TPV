#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "checkML.h"
#include "Texture.h"

class Font {
private:
	TTF_Font* font = nullptr;
	SDL_Renderer* renderer;
	uint size = 8;
public:
	Font() {};
	Font(SDL_Renderer* renderer, string filename, int size): renderer(renderer), size(size) { load(filename); };
	~Font() { liberate(); };
	TTF_Font* getFont();
	SDL_Renderer* getRenderer();
	void liberate();
	void load(string filename);
};