#pragma once

#include "checkML.h"
#include "RigidBody.h"
#include "ArkanoidObject.h"

class Ball : public ArkanoidObject, public RigidBody
{
  private:
	void setBody(float32 x, float32 y, float32 radius, b2World &world);

  public:
	Ball(){};
	Ball(float32 x, float32 y, float32 radius, Texture *texture);
	~Ball();
	virtual void destroy();
	virtual void update();
	virtual void render() const;
	virtual void onEndContact(RigidBody *rigidBody);
	virtual b2Vec2 getPosition() const { return RigidBody::getPosition(); };
	virtual void setPosition(float32 x, float32 y)
	{
		RigidBody::setPosition(b2Vec2{x, y});
		GameObject::setPosition(x, y);
	};
	virtual std::istream &deserialize(std::istream &out);
	virtual std::ostream &serialize(std::ostream &is) const;
};
