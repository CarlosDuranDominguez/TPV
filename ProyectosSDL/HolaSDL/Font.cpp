#include"Font.h"
void Font::liberate() {
	TTF_CloseFont(font);
	font = nullptr;
}
void Font::load(string filename) {
	font = TTF_OpenFont(filename.c_str(), size);
	if (font == nullptr) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		throw "Error loading font";
	}
}
TTF_Font* Font::getFont() {
	return font;
}
SDL_Renderer* Font::getRenderer() {
	return renderer;
}