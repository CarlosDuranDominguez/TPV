#pragma once

#include "checkML.h"
#include "ArkanoidObject.h"
#include "RigidBody.h"

class Ball;

class Block: public ArkanoidObject, public RigidBody
{
protected:
	virtual void SetUp(b2World world);
  private:
	int _column, _row;
	int _color;
  public:
	Block(float x, float y, int width, int height, int column, int row, int color, Texture *texture, b2World& world)
		:ArkanoidObject(x, y, width, height, texture), _column(column), _row(row), _color(color) {
		SetUp(world);
	};
	~Block();
	virtual void update();
	virtual std::ostream& toOutStream(std::ostream& out);
	virtual std::istream& fromInStream(std::istream& is);
	int getColor() const { return _color; };
};
