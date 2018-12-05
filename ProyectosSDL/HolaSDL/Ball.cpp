#include "Ball.h"
#include "Game.h"
#include "Block.h"
#include "GameState.h"

/*
* Constructor
*/
Ball::Ball(float32 x, float32 y, float32 radius, float32 speed, Texture *texture)
    : ArkanoidBody(x, y, radius * 2, radius * 2, texture), _speed(speed)
{
  setBody(x, y, radius, *Game::getWorld());
}

Ball::~Ball()
{
}

void Ball::setBody(float32 x, float32 y, float32 radius, b2World &world)
{
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
  fixtureDef.filter.maskBits = 0b0000'0000'0000'0010'1111;
  fixtureDef.friction = 0.0f;
  //fixtureDef.isSensor = false;
  fixtureDef.restitution = 1.0f;
  fixtureDef.shape = &shape;

  _body = world.CreateBody(&bodyDef);
  setUp(shape, fixtureDef);
}

/// Public Victual
/// Updates the update behaviour
void Ball::update() {}

void Ball::afterUpdate()
{
		if (getVelocity().LengthSquared() != _speed)
		{
			b2Vec2 v = getVelocity();
			v.Normalize();
			v *= _speed;
			setVelocity(v);
		}
}
/// Public Virtual
/// Defines the render behaviour
void Ball::render() const
{
  b2Vec2 pos = _body->GetPosition();
  _texture->renderFrame({(int)pos.x - (int)getSize().x / 2, (int)pos.y - (int)getSize().y / 2,
                         (int)_fixture->GetShape()->m_radius * 2, (int)_fixture->GetShape()->m_radius * 2},
                        0, 0);
}

void Ball::onEndContact(RigidBody *rigidBody)
{
  Block *block = dynamic_cast<Block *>(rigidBody);
  if (block)
  {
    block->contact();
  }
}

/// Public Virtual
/// Defines the deserialize method behaviour to patch the instance when loading a file save
std::istream &Ball::deserialize(std::istream &out)
{
  _texture = readTexture(out);
  float32 posx, posy, radius, velx, vely;
  out >> posx >> posy >> radius >> velx >> vely >> _speed;
  setBody(posx, posy, radius, *Game::getWorld());
  setPosition(posx, posy);
  setVelocity(b2Vec2{velx, vely});
  _size.Set(radius * 2, radius * 2);
  return out;
}

/// Public Virtual
/// Defines the serialize method behaviour to save the data into a file save
std::ostream &Ball::serialize(std::ostream &is) const
{
  return is << "Ball " << textureIndex() << " " << getPosition().x << " " << getPosition().y << " "
            << _fixture->GetShape()->m_radius << " " << getVelocity().x << " " << getVelocity().y << " " << _speed;
}

/// Public Virtual
/// Defines behaviour when the instance is to be destroyed
void Ball::destroy()
{
  GameObject::destroy();
  Game::gameManager()->deleteBall();
}
