#include "DeadZone.h"
#include "Game.h"

/// Public
// Constructor
DeadZone::DeadZone(float32 x, float32 y, float32 width, float32 height)
    : ArkanoidBody(x, y, width, height, nullptr) {
  setBody(x, y, width, height, *Game::getWorld());
}

/// Public Virtual
// Defines behaviour when the instance starts to have contact with an element
void DeadZone::onBeginContact(RigidBody *rigidBody) {
  dynamic_cast<GameObject *>(rigidBody)->destroy();
}

/// Public Virtual
// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &DeadZone::deserialize(std::istream &out) {
  readTexture(out);
  float32 posx, posy, sizex, sizey;
  out >> posx >> posy >> sizex >> sizey;
  setBody(posx, posy, sizex, sizey, *Game::getWorld());
  setPosition(posx, posy);
  size_.Set(sizex, sizey);
  return out;
}

/// Public Virtual
// Defines the serialize method behaviour to save the data into a file save
std::ostream &DeadZone::serialize(std::ostream &is) const {
  return is << "DeadZone " << 0 << " " << position_.x << " " << position_.y
            << " " << size_.x << " " << size_.y;
}

/// Private
// setBody method, creates a static polygon shape with Box2D's API
void DeadZone::setBody(float32 x, float32 y, float32 width, float32 height,
                       b2World &world) {
  // Create the body definition
  b2BodyDef bodyDef;
  bodyDef.type = b2_staticBody;
  bodyDef.fixedRotation = true;
  bodyDef.position.x = x;
  bodyDef.position.y = y;
  bodyDef.linearDamping = 0.0f;
  bodyDef.userData = static_cast<RigidBody *>(this);

  // Create the polygon shape
  b2PolygonShape shape;
  shape.SetAsBox(width / 2.0f, height / 2.0f);

  // Create the fixture definition
  b2FixtureDef fixtureDef;
  fixtureDef.density = 1.0f;
  fixtureDef.filter.categoryBits = 0b0000'0000'0000'0000'0100;
  fixtureDef.filter.maskBits = 0b0000'0000'0000'0001'0010;
  fixtureDef.friction = 0.0f;
  fixtureDef.isSensor = false;
  fixtureDef.restitution = 0.0f;
  fixtureDef.shape = &shape;

  // Add the body definition to the world
  body_ = world.CreateBody(&bodyDef);

  // Set up the shape
  setUp(shape, fixtureDef);
}

DeadZone::DeadZone() {
}

DeadZone::~DeadZone() {
}

void DeadZone::update() {
}

void DeadZone::render() const {
}
