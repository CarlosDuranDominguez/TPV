 #pragma once

#include "checkML.h"
#include "ArkanoidObject.h"
#include "RigidBody.h"

class Block: public ArkanoidObject, public RigidBody
{
  private:
	int _color;
	void SetBody(float32 x, float32 y, float32 width, float32 height, b2World& world);
  public:
	Block() {};
	Block(float32 x, float32 y, float32 width, float32 height, int color, Texture *texture);
	~Block();
	virtual void destroy();
	virtual void update();
	virtual void render() const;
	virtual std::istream& deserialize(std::istream& out);
	virtual std::ostream& serialize(std::ostream& is) const;
	int getColor() const { return _color; };
};
