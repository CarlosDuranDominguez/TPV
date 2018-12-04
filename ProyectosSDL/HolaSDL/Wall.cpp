#include "Wall.h"
#include "Game.h"

Wall::Wall(float32 x, float32 y, float32 width, float32 height, Texture *texture)
	: ArkanoidObject(x, y, width, height, texture)
{
	setBody(x, y, width, height, *Game::getWorld());
}

void Wall::update() {}

void Wall::render() const
{
	b2Vec2 pos = _body->GetPosition();
	_texture->renderFrame({(int)pos.x - (int)getSize().x / 2, (int)pos.y - (int)getSize().y / 2, (int)getSize().x, (int)getSize().y}, 0, 0);
}

std::istream &Wall::deserialize(std::istream &is)
{
	is >> _position.x >> _position.y >> _size.x >> _size.y;
	setBody(_position.x, _position.y, _size.x, _size.y, *Game::getWorld());
	return is;
}

std::ostream &Wall::serialize(std::ostream &is) const
{
	return is << "Wall " << textureIndex() << " " << _position.x << " " << _position.y << " " << _size.x << " " << _size.y;
}

void Wall::setBody(float32 x, float32 y, float32 width, float32 height, b2World &world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.x = x;
	bodyDef.position.y = y;
	bodyDef.linearDamping = 0.0f;
	bodyDef.userData = static_cast<RigidBody *>(this);
	b2PolygonShape shape;
	shape.SetAsBox(width / 2.0f, height / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.filter.categoryBits = 0b0000'0000'0000'0000'0100;
	fixtureDef.filter.maskBits = 0b0000'0000'0000'0010'0010;
	fixtureDef.friction = 0.0f;
	//fixtureDef.isSensor = false;
	fixtureDef.restitution = 1.0f;
	fixtureDef.shape = &shape;
	// Add to world
	_body = world.CreateBody(&bodyDef);
	setUp(shape, fixtureDef);
}
