#include "Text.h"
#include "Vector2D.h"
class Counter {
private:
	int score;
	Text* text;
public:
	Counter(float x, float y, int width, int height, SDL_Color color, Font* font) :score(0) { text = new Text(font, x, y, width, height, color, to_string(score)); };
	Counter(Vector2D position, int width, int height, SDL_Color color, Font* font) :score(0){ text = new Text(font, position, width, height, color, to_string(score)); };
	~Counter() { delete text; }
	int setScore(const int num);
	int increaseScore(const int num);
	void render() const;
};