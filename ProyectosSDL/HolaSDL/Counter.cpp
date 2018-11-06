#include"Counter.h"
#include<math.h>

Counter::Counter(float x, float y, int width, int height, SDL_Color color, Font* font) :score(0) { 
	text = new Text(font, x, y, width, height, color, to_string(score)); 
};

Counter::Counter(Vector2D position, int width, int height, SDL_Color color, Font* font) :score(0) { 
	text = new Text(font, position, width, height, color, to_string(score)); 
};

int Counter::setScore(const int num) { 
	text->setText(to_string(num));
	return score = num; 
}

int Counter::increaseScore(const int num) { 
	text->setText(to_string(score += num));
	return score; 
}

void Counter::render() const{
	text->render();
}