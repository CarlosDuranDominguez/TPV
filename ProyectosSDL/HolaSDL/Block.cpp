#include "Block.h"

void Block::SetUp(b2World& world) {
	// Create the body
	b2BodyDef bodyDef;
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

void Block::Init(b2World& world, Texture *texture) {
	_texture = texture;
	SetUp(world);
}

Block::~Block() {
	_body->DestroyFixture(_fixture);
}

void Block::update() {

}


std::istream& Block::deserialize(std::istream&  is) {
	is >> _color >> _position.x >> _position.y >> _size.x >> _size.y;
	return is;
}

std::ostream& Block::serialize(std::ostream& out) const {
	return out << "Block " << _color << " " << _position.x << " " << _position.y << " " << _size.x << " " << _size.y;
	
}

