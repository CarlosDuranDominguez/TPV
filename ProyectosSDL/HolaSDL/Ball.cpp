#include "Ball.h"
#include "Game.h"
#include "Block.h"
#include "GameState.h"

/*
* Constructor
*/
Ball::Ball(float32 x, float32 y, float32 radius, Texture *texture)
	:ArkanoidObject(x, y, radius * 2, radius * 2, texture) {
	setBody(x, y, radius, *Game::getWorld());
	Game::gameManager()->addBalls(1);
}

Ball::~Ball() {
}

void Ball::setBody(float32 x, float32 y, float32 radius, b2World& world) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.bullet = true;
	bodyDef.fixedRotation = true;
	bodyDef.position.x = x;
	bodyDef.position.y = y;
	bodyDef.linearDamping = 0.0f;
	bodyDef.userData = static_cast<RigidBody*>(this);
	b2CircleShape shape;
	shape.m_p.Set(0.0f, 0.0f);
	shape.m_radius = radius;
	b2FixtureDef fixtureDef;
	fixtureDef.density = 0.1f;
	fixtureDef.filter.categoryBits = 0b0000'0000'0000'0000'0010;
	fixtureDef.filter.maskBits = 0b0000'0000'0000'0000'1111;
	fixtureDef.friction = 0.0f;
	//fixtureDef.isSensor = false;
	fixtureDef.restitution = 1.0f;
	fixtureDef.shape = &shape;
	setUp(bodyDef, shape, fixtureDef, world);
}

void Ball::update() {}

void Ball::render() const {
	b2Vec2 pos = _body->GetPosition();
	_texture->renderFrame({ (int)pos.x - (int)getSize().x / 2, (int)pos.y - (int)getSize().y / 2, 
		(int)_fixture->GetShape()->m_radius * 2, (int)_fixture->GetShape()->m_radius*2 }, 0, 0);
}

void Ball::onEndContact(RigidBody* rigidBody) {
	Block* block = dynamic_cast<Block*>(rigidBody);
	if (block) { block->destroy(); }
}

std::istream& Ball::deserialize(std::istream& is) {
	is >> _position.x >> _position.y >> _size.x >> _fixture->GetShape()->m_radius;
	setBody(_position.x, _position.y, _size.x/2, *Game::getWorld());
	return is;
}

std::ostream& Ball::serialize(std::ostream& out) const {
	return out << "Ball " << _body->GetPosition().x << " " << _body->GetPosition().y << " " << _fixture->GetShape()->m_radius;
}

void Ball::destroy() {
	GameObject::destroy();
	Game::gameManager()->deleteBall();
}