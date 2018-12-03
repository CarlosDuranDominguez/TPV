#pragma once

#include "checkML.h"
#include "ArkanoidObject.h"
#include "RigidBody.h"
#include "Texture.h"

class ArkanoidObject;

class StaticBody : public ArkanoidObject, public RigidBody
{
protected:
	virtual void (b2World& world);
public:
	//StaticBody() {};
	StaticBody(float32 x, float32 y, float32 width, float32 height, Texture *texture, b2World& world);
	~StaticBody();
	virtual void Init(b2World& world, Texture *texture);
	virtual b2Vec2 getPosition() const { return _body->GetPosition(); };
	virtual void update();
	virtual void render() const;
	virtual std::istream& deserialize(std::istream& out) = 0;
	virtual std::ostream& serialize(std::ostream& is) const = 0;
};