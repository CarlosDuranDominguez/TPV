#include "ScoreMarker.h"
#include "Game.h"

ScoreMarker::ScoreMarker(float x, float y, int width, int height, SDL_Color color, Font *font)
	: Text(font, x, y, width, height, color, "h")
{
	_score = Game::gameManager()->getScore();
	setText(to_string(_score));
}

void ScoreMarker::update()
{
	if (_score != Game::gameManager()->getScore())
	{
		_score = Game::gameManager()->getScore();
		setText(to_string(_score));
	}
}

std::istream &ScoreMarker::deserialize(std::istream &out)
{
	return out;
}

std::ostream &ScoreMarker::serialize(std::ostream &is) const
{
	return is;
}
