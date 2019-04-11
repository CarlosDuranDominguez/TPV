#include "Bullet.h"
#include "Game.h"

Bullet::Bullet() = default;

Bullet::Bullet(const float32 x, const float32 y, const float32 radius,
               const float32 speed, Texture *texture)
    : Ball(x, y, radius, speed, texture) {}

Bullet::~Bullet() = default;

// Defines behaviour when the instance starts to have contact with an element
void Bullet::onBeginContact(RigidBody *rigidBody) { destroy(); }

// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &Bullet::deserialize(std::istream &out) {
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

// Defines the serialize method behaviour to save the data into a file save
std::ostream &Bullet::serialize(std::ostream &is) const {
  return is << "Bullet " << textureIndex() << " " << getPosition().x << " "
            << getPosition().y << " " << fixture_->GetShape()->m_radius << " "
            << getVelocity().x << " " << getVelocity().y << " " << getSpeed();
}

// setBody method, creates a dynamic circle shape with Box2D's API
void Bullet::setBody(const float32 x, const float32 y, const float32 radius,
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
  fixtureDef.filter.maskBits = 0b0000'0000'0000'0000'0100;
  fixtureDef.friction = 0.0f;
  fixtureDef.restitution = 1.0f;
  fixtureDef.shape = &shape;

  // Add the body definition to the world
  body_ = world.CreateBody(&bodyDef);

  // Set up the shape
  setUp(shape, fixtureDef);
}
