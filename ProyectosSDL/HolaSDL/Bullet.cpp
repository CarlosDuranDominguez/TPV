#include "Bullet.h"
#include "Game.h"

Bullet::Bullet(float32 x, float32 y, float32 radius, float32 speed, Texture *texture)
	:Ball(x,y,radius,speed,texture) {
}

void Bullet::setBody(float32 x, float32 y, float32 radius, b2World &world) {
	b2BodyDef bodyDef;
	bodyDef.allowSleep = false;
	bodyDef.type = b2_dynamicBody;
	bodyDef.bullet = true;
	bodyDef.fixedRotation = true;
	bodyDef.position.x = x;
	bodyDef.position.y = y;
	bodyDef.linearDamping = 0.0f;
	bodyDef.userData = static_cast<RigidBody *>(this);
	b2CircleShape shape;
	shape.m_p.Set(0.0f, 0.0f);
	shape.m_radius = radius;
	b2FixtureDef fixtureDef;

	fixtureDef.density = 0.0f;
	fixtureDef.filter.categoryBits = 0b0000'0000'0000'0000'0010;
	fixtureDef.filter.maskBits = 0b0000'0000'0000'0000'0100;
	fixtureDef.friction = 0.0f;
	//fixtureDef.isSensor = false;
	fixtureDef.restitution = 1.0f;
	fixtureDef.shape = &shape;

	_body = world.CreateBody(&bodyDef);
	setUp(shape, fixtureDef);
}

Bullet::~Bullet(){}
void Bullet::onBeginContact(RigidBody *rigidBody) { destroy(); }

std::istream &Bullet::deserialize(std::istream &out) {
  _texture = readTexture(out);
  float32 posx, posy, radius, velx, vely, speed;
  out >> posx >> posy >> radius >> velx >> vely >> speed;
  setBody(posx, posy, radius, *Game::getWorld());
  setSpeed(speed);
  setPosition(posx, posy);
  setVelocity(b2Vec2{ velx, vely });
  _size.Set(radius * 2, radius * 2);
  return out;
}

std::ostream &Bullet::serialize(std::ostream &is) const {
  return is << "Bullet " << textureIndex() << " " << getPosition().x << " " << getPosition().y << " "
    << _fixture->GetShape()->m_radius << " " << getVelocity().x << " " << getVelocity().y << " " << getSpeed();
}
