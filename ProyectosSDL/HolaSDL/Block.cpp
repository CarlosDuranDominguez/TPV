#include "Block.h"
#include "Texture.h"
#include "Game.h"
Block::Block() :
	position(), width(), height(), column(), row(), color(), texture() {};
Block::Block(float x, float y, int width, int height, int column, int row, int color, Texture* texture)
	:position(x, y), width(width), height(height), column(column), row(row), color(color), texture(texture) {};
Block::Block(Vector2D position, int width, int height, int column, int row, int color, Texture* texture)
	:position(position), width(width), height(height), column(column), row(row), color(color), texture(texture) {};
Block::~Block() {};
void Block::render() {
	texture->renderFrame(SDL_Rect{ (int)position.getX(),(int)position.getY(),width, height }, color/texture->getNumCols(), color%texture->getNumCols());
}