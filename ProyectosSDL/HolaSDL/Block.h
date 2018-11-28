#pragma once

#include "checkML.h"
#include "ArkanoidObject.h"
#include "RigidBody.h"
#include "Texture.h"

class ArkanoidObject;

class Block: public ArkanoidObject, public RigidBody
{
protected:
	virtual void SetUp(b2World& world);
  private:
	int _color;
  public:
	Block() {};
	Block(float32 x, float32 y, float32 width, float32 height, int color, Texture *texture, b2World& world)
		:ArkanoidObject(x, y, width, height, texture), _color(color) {
		SetUp(world);
	};
	~Block();
	virtual void Init(b2World& world, Texture *texture);
	virtual void update();
	virtual std::istream& deserialize(std::istream& out);
	virtual std::ostream& serialize(std::ostream& is) const;
	int getColor() const { return _color; };
};
