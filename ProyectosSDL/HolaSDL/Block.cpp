#include "Block.h"
#include "Game.h"

Block::Block(float32 x, float32 y, float32 width, float32 height, int color, Texture *texture) 
	:ArkanoidObject(x, y, width, height, texture), _color(color) {
	SetBody(x, y, width, height, *Game::getWorld());
}

Block::~Block() {
	_body->DestroyFixture(_fixture);
	_body=nullptr;
}

void Block::destroy() {
	GameObject::destroy();

}

void Block::update() { 
}

void Block::render() const{
	b2Vec2 pos = _body->GetPosition();
	_texture->renderFrame({ (int)pos.x - (int)getSize().x / 2, (int)pos.y - (int)getSize().y / 2, (int)getSize().x, (int)getSize().y }, _color/3, _color%3);
}

void Block::SetBody(float32 x, float32 y, float32 width, float32 height, b2World& world) {
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
	//fixtureDef.isSensor = false;
	fixtureDef.restitution = 1.0f;
	fixtureDef.shape = &shape;
	setUp(bodyDef, shape, fixtureDef, world);
}

std::istream& Block::deserialize(std::istream&  is) {
	is >> _color >> _position.x >> _position.y >> _size.x >> _size.y;
	SetBody(_position.x, _position.y, _size.x, _size.y, *Game::getWorld());
	return is;
}

std::ostream& Block::serialize(std::ostream& out) const {
	return out << "Block " << _color << " " << _position.x << " " << _position.y << " " << _size.x << " " << _size.y;
}

