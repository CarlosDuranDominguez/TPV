#include "LiveMarker.h"
#include "Game.h"

LiveMarker::LiveMarker(float32 x, float32 y, float32 width, float32 height, Texture *texture)
	: GameObject(x, y, width, height), Renderable(texture)
{
}

void LiveMarker::render() const
{
	SDL_Rect rect{
		(int)_position.x,
		(int)_position.y,
		_texture->getW(),
		_texture->getH()};
	int lives = Game::gameManager()->getLives();
	for (int i = 0; i < lives; i++)
	{
		rect.x = (int)_position.x + i * _texture->getW();
		_texture->render(rect);
	}
}

std::istream &LiveMarker::deserialize(std::istream &out)
{
	return out;
}

std::ostream &LiveMarker::serialize(std::ostream &is) const
{
	return is;
}
