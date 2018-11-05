#include"Font.h"
void Font::liberate() {
	TTF_CloseFont(font);
}
void Font::load(string filename) {
	TTF_OpenFont(filename.c_str(), size);
}
TTF_Font* Font::getFont() {
	return font;
}
SDL_Renderer* Font::getRenderer() {
	return renderer;
}