#pragma once
#include<Box2D/Box2D.h>

class RigidBody {
protected:
	b2Body *_body;
public:
	~RigidBody() {};
	const b2Body* getBody() const { return _body; };
};