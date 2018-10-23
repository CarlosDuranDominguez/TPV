#include "Wall.h"

Wall::Wall(float x, float y, int width, int height, Texture* texture)
	:position(x, y), width(width), height(height), texture(texture) {};
Wall::Wall(Vector2D position, int width, int height, Texture* texture)
	: position(position), width(width), height(height), texture(texture) {};
Wall::~Wall() {};
void Wall::render() {
	texture->render(SDL_Rect{ (int)position.getX(),(int)position.getY(),width,height });
};