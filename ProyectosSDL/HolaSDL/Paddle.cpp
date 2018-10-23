#include "Paddle.h"
#include "Game.h"
#include "SDL.h"

Paddle::Paddle(Vector2D position, int width, int heigth, double speed, Texture* texture) :
	position(position), width(width), heigth(heigth), velocity(), speed(), texture(texture) {};
Paddle::Paddle(double x, double y, int width, int heigth, double speed, Texture* texture) :
	position(x, y), width(width), heigth(heigth), velocity(), speed(speed), texture(texture) {};
void Paddle::render()
{
	texture->render(SDL_Rect{ (int)position.getX(),(int)position.getY(),width,heigth });
};
void Paddle::update() 
{
	position = position + velocity;
};
void Paddle::handleEvents(SDL_Event event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			velocity = Vector2D(1, 0)*speed;
		break;
		case SDLK_LEFT:
			velocity = -Vector2D(1, 0)*speed;
		break;
		}
		break;
	case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
		{
			velocity = Vector2D(0, 0);
		}
		break;
	}
}