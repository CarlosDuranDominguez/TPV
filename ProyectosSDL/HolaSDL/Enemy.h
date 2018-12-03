#pragma once

#include "checkML.h"
#include "ArkanoidObject.h"
#include "RigidBody.h"
#include "Controllable.h"

class Game;

class Enemy : public ArkanoidObject, public RigidBody
{
private:
	float32 _speed;
	float32 _halfLife;
	float32 _changeProbability;
	b2Timer* _timer;
	void setBody(float32 x, float32 y, float32 radius, b2World& world);
public:
	Enemy();
	Enemy(float32 x, float32 y, float32 width, float32 height, float32 maxSpeed, 
		float32 halfLife, float32 changeProbability, Texture *texture);
	~Enemy();
	virtual void update();
	virtual void render() const;
	virtual std::istream& deserialize(std::istream& out);
	virtual std::ostream& serialize(std::ostream& is) const;
};
