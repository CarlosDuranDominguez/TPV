#include "Award.h"
#include "Game.h"


void Award::SetBody(float32 x, float32 y, float32 width, float32 height, b2World& world) {

	float32 radius = height / 2.0f;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.x = x;
	bodyDef.position.y = y;
	bodyDef.linearDamping = 0.0f;
	bodyDef.userData = static_cast<RigidBody*>(this);
	b2PolygonShape shape;
	shape.SetAsBox((width - height) / 2.0f, height / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.filter.categoryBits = 0b0000'0000'0000'0001'0000;
	fixtureDef.filter.maskBits = 0b0000'0000'0000'0000'0001;
	fixtureDef.friction = 0.0f;
	fixtureDef.isSensor = true;
	fixtureDef.restitution = 0.0f;
	fixtureDef.shape = &shape;
	b2CircleShape leftshape;
	leftshape.m_p.x = radius - width;
	leftshape.m_p.y = 0;
	leftshape.m_radius = radius;
	b2FixtureDef leftfixtureDef;
	leftfixtureDef.density = 1.0f;
	leftfixtureDef.filter.categoryBits = 0b0000'0000'0000'0001'0000;
	leftfixtureDef.filter.maskBits = 0b0000'0000'0000'0000'0001;
	leftfixtureDef.friction = 0.0f;
	leftfixtureDef.isSensor = true;
	leftfixtureDef.restitution = 0.0f;
	leftfixtureDef.shape = &leftshape;
	b2CircleShape rightshape;
	leftshape.m_p.x = width - radius;
	leftshape.m_p.y = 0;
	leftshape.m_radius = radius;
	b2FixtureDef rightfixtureDef;
	rightfixtureDef.density = 1.0f;
	rightfixtureDef.filter.categoryBits = 0b0000'0000'0000'0001'0000;
	rightfixtureDef.filter.maskBits = 0b0000'0000'0000'0000'0001;
	rightfixtureDef.friction = 0.0f;
	rightfixtureDef.isSensor = true;
	rightfixtureDef.restitution = 0.0f;
	rightfixtureDef.shape = &leftshape;
	// Add to world
	_body = world.CreateBody(&bodyDef);
	setUp(shape, fixtureDef);
	setUp(rightshape, rightfixtureDef);
	setUp(leftshape, leftfixtureDef);
}

Award::Award(float32 x, float32 y, float32 width, float32 height, float32 framerate, Texture *texture)
	:ArkanoidObject(x,y,width,height,texture), _framerate(framerate) {
	SetBody(x, y, width, height, *Game::getWorld());
}

Award::~Award(){
}

void Award::update(){
}

void Award::render() const{
	_texture->render({ (int)(_body->GetPosition().x - _size.x / 2.0f),
					  (int)(_body->GetPosition().y - _size.y / 2.0f),
					  (int)(_size.x), (int)(_size.y) });
}

void Award::contact(){
	destroy();
}

void Award::destroy(){
	GameObject::destroy();
}

void Award::onBeginContact(RigidBody* rigidbody) {
	contact();
}
std::istream& Award::deserialize(std::istream& out){
	return out;
}

std::ostream& Award::serialize(std::ostream& is) const{
	return is;
}
