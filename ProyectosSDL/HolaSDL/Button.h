#include "Text.h"

class Button {
private:
	Text *text;
	SDL_Color inColor;
	SDL_Color outColor;
public:
	Button();
	void render();
	void handleEvents(SDL_Event event);
};