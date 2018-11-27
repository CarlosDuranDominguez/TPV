#pragma once
#include<Box2D/Box2D.h>

class RigidBody {
protected:
	b2Body *_body;
	b2Fixture* _fixture;
	virtual void SetUp(b2World& world) = 0;
public:
	~RigidBody() {};
	const b2Body* getBody() const { return _body; };
};