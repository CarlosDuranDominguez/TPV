#pragma once

#include "checkML.h"
#include "RigidBody.h"
#include "ArkanoidObject.h"

class Wall : public ArkanoidObject, public RigidBody
{
  private:
	void setBody(float32 x, float32 y, float32 width, float32 height, b2World &world);

  public:
	Wall(){};
	Wall(float32 x, float32 y, float32 width, float32 height, Texture *texture);
	~Wall(){};
	virtual void update();
	virtual void render() const;
	virtual b2Vec2 getPosition() const { return RigidBody::getPosition(); };
	virtual void setPosition(float32 x, float32 y)
	{
		RigidBody::setPosition(b2Vec2{x, y});
		GameObject::setPosition(x, y);
	};
	virtual std::istream &deserialize(std::istream &out);
	virtual std::ostream &serialize(std::ostream &is) const;
};
