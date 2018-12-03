#pragma once

#include "checkML.h"
#include "Text.h"

class ScoreMarker : public Text
{
private:
	int _score;
public:
	ScoreMarker(float x, float y, int width, int height, SDL_Color color, Font *font);
	~ScoreMarker() {};
	void update();
	virtual std::istream& deserialize(std::istream& out);
	virtual std::ostream& serialize(std::ostream& is) const;
};