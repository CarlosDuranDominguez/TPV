#include "Ball.h"
#include "Block.h"
#include "Game.h"

Ball::Ball() : speed_(0) {}

Ball::~Ball() = default;

// Constructor
Ball::Ball(const float32 x, const float32 y, const float32 radius,
           const float32 speed, Texture *texture)
    : ArkanoidBody(x, y, radius * 2, radius * 2, texture), speed_(speed) {
  setBody(x, y, radius, *Game::getWorld());
}

float32 Ball::getSpeed() const { return speed_; }
void Ball::setSpeed(const float32 speed) { speed_ = speed; }

// Updates the update behaviour
void Ball::update() {}

// Defines behaviour after every update cycle
void Ball::afterUpdate() {
  // Check if the speed is not the maximum speed
  const auto speed = getVelocity().LengthSquared();
  if (speed != speed_) {
    // Set the normalized speed to the maximum one
    auto v = getVelocity();
    v.Normalize();
    v *= speed_;
    setVelocity(v);
  } else if (speed < b2_epsilon) {
    setVelocity(b2Vec2{0.0f, speed});
  }
}

// Defines the render behaviour
void Ball::render() const {
  // Gets the position, size, and diameter, and renders
  const auto pos = body_->GetPosition();
  const auto size = getSize();
  const auto diameter = int(fixture_->GetShape()->m_radius) * 2;
  texture_->renderFrame({int(pos.x) - int(size.x) / 2,
                         int(pos.y) - int(size.y) / 2, diameter, diameter},
                        0, 0);
}

// Defines the end contact behaviour
void Ball::onEndContact(RigidBody *rigidBody) {
  // Casts the rigidBody to a block, since balls can only collide with blocks,
  // walls, and other balls
  auto block = dynamic_cast<Block *>(rigidBody);
  // If it's a block, invoke the contact call
  if (block) block->contact();
}

// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &Ball::deserialize(std::istream &out) {
  texture_ = readTexture(out);
  float32 posx, posy, radius, velx, vely, speed;
  out >> posx >> posy >> radius >> velx >> vely >> speed;
  setBody(posx, posy, radius, *Game::getWorld());
  setSpeed(speed);
  setPosition(posx, posy);
  setVelocity(b2Vec2{velx, vely});
  size_.Set(radius * 2, radius * 2);
  return out;
}

/// Public Virtual
// Defines the serialize method behaviour to save the data into a file save
std::ostream &Ball::serialize(std::ostream &is) const {
  return is << "Ball " << textureIndex() << " " << getPosition().x << " "
            << getPosition().y << " " << fixture_->GetShape()->m_radius << " "
            << getVelocity().x << " " << getVelocity().y << " " << getSpeed();
}

/// Public Virtual
// Defines behaviour when the instance is to be destroyed
void Ball::destroy() {
  // Call inherited destroy method from GameObject
  GameObject::destroy();
  Game::getGameManager()->deleteBall();
}

/// Private
// setBody method, creates a dynamic circle shape with Box2D's API
void Ball::setBody(const float32 x, const float32 y, const float32 radius,
                   b2World &world) {
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
  body_ = world.CreateBody(&bodyDef);

  // Set up the shape
  setUp(shape, fixtureDef);
}
