#include "StaticBody.h"

void StaticBody::(b2World& world) {
	// Create the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	// Position must be in the center of the block
	bodyDef.position.Set(_position.x + _size.x / 2, _position.y + _size.y / 2);
	// Add to world
	_body = world.CreateBody(&bodyDef);
	// Set the polygon shape
	b2PolygonShape box;
	box.SetAsBox(_size.x / 2, _size.y / 2);
	// Set the fixture definition
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	// Create the fixture
	_fixture = _body->CreateFixture(&fixtureDef);

}

void StaticBody::Init(b2World& world, Texture *texture) {
	_texture = texture;
	(world);
}

StaticBody::~StaticBody() {
	_body->DestroyFixture(_fixture);
	_body = nullptr;
}

void StaticBody::update() {
}

void StaticBody::render() const {
	_texture->renderFrame({ (int)getPosition().x - (int)getSize().x / 2, (int)getPosition().y - (int)getSize().y / 2, (int)getSize().x, (int)getSize().y }, 0, 0);
}

