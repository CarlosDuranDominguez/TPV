#include "Ball.h"
#include "Game.h"
#include "Block.h"
#include "GameState.h"

/// Public
// Constructor
Ball::Ball(float32 x, float32 y, float32 radius, float32 speed, Texture *texture)
    : ArkanoidBody(x, y, radius * 2, radius * 2, texture), _speed(speed)
{
  setBody(x, y, radius, *Game::getWorld());
}

/// Public Virtual
// Updates the update behaviour
void Ball::update() {}

/// Public Virtual
// Defines behaviour after every update cycle
void Ball::afterUpdate()
{
  // Check if the speed is not the maximum speed
  if (getVelocity().LengthSquared() != _speed)
  {
    // Set the normalized speed to the maximum one
    b2Vec2 v = getVelocity();
    v.Normalize();
    v *= _speed;
    setVelocity(v);
  }
}

/// Public Virtual
// Defines the render behaviour
void Ball::render() const
{
  // Gets the position, size, and diameter, and renders
  auto pos = _body->GetPosition();
  auto size = getSize();
  auto diameter = (int)_fixture->GetShape()->m_radius * 2;
  _texture->renderFrame({(int)pos.x - (int)size.x / 2,
                         (int)pos.y - (int)size.y / 2,
                         diameter, diameter},
                        0, 0);
}

/// Public Virtual
// Defines the end contact behaviour
void Ball::onEndContact(RigidBody *rigidBody)
{
  // Casts the rigidBody to a block, since balls can only collide with blocks,
  // walls, and other balls
  Block *block = dynamic_cast<Block *>(rigidBody);
  // If it's a block, invoke the contact call
  if (block)
    block->contact();
}

/// Public Virtual
// Defines the deserialize method behaviour to patch the instance when loading a file save
std::istream &Ball::deserialize(std::istream &out)
{
  _texture = readTexture(out);
  float32 posx, posy, radius, velx, vely, speed;
  out >> posx >> posy >> radius >> velx >> vely >> speed;
  setBody(posx, posy, radius, *Game::getWorld());
  setSpeed(speed);
  setPosition(posx, posy);
  setVelocity(b2Vec2{velx, vely});
  _size.Set(radius * 2, radius * 2);
  return out;
}

/// Public Virtual
// Defines the serialize method behaviour to save the data into a file save
std::ostream &Ball::serialize(std::ostream &is) const
{
  return is << "Ball " << textureIndex() << " " << getPosition().x << " " << getPosition().y << " "
            << _fixture->GetShape()->m_radius << " " << getVelocity().x << " " << getVelocity().y << " " << getSpeed();
}

/// Public Virtual
// Defines behaviour when the instance is to be destroyed
void Ball::destroy()
{
  // Call inherited destroy method from GameObject
  GameObject::destroy();
  Game::getGameManager()->deleteBall();
}

/// Private
// setBody method, creates a dynamic circle shape with Box2D's API
void Ball::setBody(float32 x, float32 y, float32 radius, b2World &world)
{
  // Create the body definition
  b2BodyDef bodyDef;
  bodyDef.allowSleep = false;
  bodyDef.type = b2_dynamicBody;
  bodyDef.bullet = true;
  bodyDef.fixedRotation = true;
  bodyDef.position.x = x;
  bodyDef.position.y = y;
  bodyDef.linearDamping = 0.0f;
  bodyDef.userData = static_cast<RigidBody *>(this);

  // Create the circle shape
  b2CircleShape shape;
  shape.m_p.Set(0.0f, 0.0f);
  shape.m_radius = radius;

  // Create the fixture definition
  b2FixtureDef fixtureDef;
  fixtureDef.density = 0.0f;
  fixtureDef.filter.categoryBits = 0b0000'0000'0000'0000'0010;
  fixtureDef.filter.maskBits = 0b0000'0000'0000'0010'1111;
  fixtureDef.friction = 0.0f;
  fixtureDef.restitution = 1.0f;
  fixtureDef.shape = &shape;

  // Add the body definition to the world
  _body = world.CreateBody(&bodyDef);

  // Set up the shape
  setUp(shape, fixtureDef);
}
