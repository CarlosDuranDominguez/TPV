#include "DeadZone.h"
#include "Game.h"

DeadZone::DeadZone(float32 x, float32 y, float32 width, float32 height) 
	:ArkanoidObject(x,y,width,height,nullptr) {
	setBody(x, y, width, height, *Game::getWorld());
}

void DeadZone::setBody(float32 x, float32 y, float32 width, float32 height, b2World& world) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.x = x;
	bodyDef.position.y = y;
	bodyDef.linearDamping = 0.0f;
	bodyDef.userData = static_cast<RigidBody*>(this);
	b2PolygonShape shape;
	shape.SetAsBox(width / 2.0f, height / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.filter.categoryBits = 0b0000'0000'0000'0000'0100;
	fixtureDef.filter.maskBits = 0b0000'0000'0000'0000'0010;
	fixtureDef.friction = 0.0f;
	fixtureDef.isSensor = false;
	fixtureDef.restitution = 0.0f;
	fixtureDef.shape = &shape;
	setUp(bodyDef, shape, fixtureDef, world);
}

void DeadZone::onBeginContact(RigidBody* rigidBody) {
	dynamic_cast<GameObject*>(rigidBody)->destroy();
}

std::istream& DeadZone::deserialize(std::istream& out) {
	return out;
}

std::ostream& DeadZone::serialize(std::ostream& is) const {
	return is;
}
