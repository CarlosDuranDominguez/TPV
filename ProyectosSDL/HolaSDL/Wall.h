#pragma once

#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include "Ball.h"

class Wall
{
  private:
	Vector2D _position;
	int _width, _height;
	Texture *_texture;

  public:
	Wall(float x, float y, int width, int height, Texture *texture);
	Wall(Vector2D position, int width, int height, Texture *texture);
	~Wall();
	void render() const;
	bool collide(const Ball *, Vector2D &, Vector2D &);
};
