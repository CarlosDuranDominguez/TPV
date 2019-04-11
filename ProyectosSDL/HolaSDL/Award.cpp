#include "Award.h"
#include <iostream>
#include <string>
#include "Game.h"
#include "Paddle.h"

/// Public
// Constructor
Award::Award(float32 x, float32 y, float32 width, float32 height, float32 speed,
             Uint32 framerate, Texture *texture)
    : ArkanoidBody(x, y, width, height, texture),
      frameRate_(framerate),
      animationTimer_(new b2Timer()),
      frame_(0),
      contacted_(false),
      speed_(speed) {
  setBody(x, y, width, height, *Game::getWorld());
}

/// Public
// Destructor
Award::~Award() { delete animationTimer_; }

/// Public Virtual
// Updates the update behaviour
void Award::update() {
  // If the counter's milliseconds counted over 1000 milliseconds divided by
  // the framerate frequency, go to the next frame to continue the animation
  if (animationTimer_->GetMilliseconds() > 1000.0f / frameRate_) {
    // If the next frame is outside the animation range, go to to the first
    // frame
    if ((++frame_) > texture_->getNumCols() * texture_->getNumRows()) {
      frame_ = 0;
    }

    // Reset the timer
    animationTimer_->Reset();
  }
}

/// Public Virtual
// Defines the render behaviour
void Award::render() const {
  b2Vec2 pos = body_->GetPosition();

  texture_->renderFrame(
      {(int)pos.x - (int)getSize().x / 2, (int)pos.y - (int)getSize().y / 2,
       (int)getSize().x, (int)getSize().y},
      frame_ / (texture_->getNumCols() + 1), frame_ % texture_->getNumCols());
}

/// Public Virtual
// Defines behaviour when the instance gets in contact with the instance
void Award::contact() { destroy(); }

/// Public Virtual
// Defines behaviour when the instance is to be destroyed
void Award::destroy() {
  // Call inherited destroy method from GameObject
  GameObject::destroy();
}

/// Public Virtual
// Defines behaviour after every update cycle
void Award::afterUpdate() {
  if (getVelocity().y != speed_) {
    b2Vec2 v{0, speed_};
    setVelocity(v);
  }
}

/// Public Virtual
// Defines behaviour when the instance starts to have contact with an element
void Award::onBeginContact(RigidBody *rigidbody) {
  // If the contact was done with the paddle, set _contacted to true
  if (!contacted_ && dynamic_cast<Paddle *>(rigidbody)) {
    contacted_ = true;
    contact();
  }
}

/// Public Virtual
// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &Award::deserialize(std::istream &out) {
  texture_ = readTexture(out);
  float32 posx, posy, sizex, sizey;
  out >> posx >> posy >> sizex >> sizey;
  setBody(posx, posy, sizex, sizey, *Game::getWorld());
  setPosition(posx, posy);
  size_.Set(sizex, sizey);
  out >> speed_ >> frameRate_;
  return out;
}

/// Public Virtual
// Defines the serialize method behaviour to save the data into a file save
std::ostream &Award::serialize(std::ostream &is) const {
  string a = typeid(*this).name();
  a = a.substr(6);
  return is << a << " " << textureIndex() << " " << getPosition().x << " "
            << getPosition().y << " " << getSize().x << " " << getSize().y
            << " " << speed_ << " " << frameRate_;
}

/// Private
// setBody method, creates a dynamic polygon shape with Box2D's API
void Award::setBody(float32 x, float32 y, float32 width, float32 height,
                    b2World &world) {
  float32 radius = height / 2.0f;

  // Create the body definition
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.fixedRotation = true;
  bodyDef.position.x = x;
  bodyDef.position.y = y;
  bodyDef.linearDamping = 0.0f;
  bodyDef.userData = static_cast<RigidBody *>(this);

  // Create the poligon shape as a box
  b2PolygonShape shape;
  shape.SetAsBox((width - height) / 2.0f, height / 2.0f);

  // Create the fixture definition
  b2FixtureDef fixtureDef;
  fixtureDef.density = 1.0f;
  fixtureDef.filter.categoryBits = 0b0000'0000'0000'0001'0000;
  fixtureDef.filter.maskBits = 0b0000'0000'0000'0000'0001;
  fixtureDef.friction = 0.0f;
  fixtureDef.isSensor = true;
  fixtureDef.restitution = 0.0f;
  fixtureDef.shape = &shape;

  // Create the circle shape
  b2CircleShape leftshape;
  leftshape.m_p.x = radius - width;
  leftshape.m_p.y = 0;
  leftshape.m_radius = radius;

  // Create the fixture definition for the left side of the capsule
  b2FixtureDef leftfixtureDef;
  leftfixtureDef.density = 1.0f;
  leftfixtureDef.filter.categoryBits = 0b0000'0000'0000'0001'0000;
  leftfixtureDef.filter.maskBits = 0b0000'0000'0000'0000'0001;
  leftfixtureDef.friction = 0.0f;
  leftfixtureDef.isSensor = true;
  leftfixtureDef.restitution = 0.0f;
  leftfixtureDef.shape = &leftshape;

  // Create the circle shape
  b2CircleShape rightshape;
  leftshape.m_p.x = width - radius;
  leftshape.m_p.y = 0;
  leftshape.m_radius = radius;

  // Create the fixture definition for the right side of the capsule
  b2FixtureDef rightfixtureDef;
  rightfixtureDef.density = 1.0f;
  rightfixtureDef.filter.categoryBits = 0b0000'0000'0000'0001'0100;
  rightfixtureDef.filter.maskBits = 0b0000'0000'0000'0000'0001;
  rightfixtureDef.friction = 0.0f;
  rightfixtureDef.isSensor = true;
  rightfixtureDef.restitution = 0.0f;
  rightfixtureDef.shape = &leftshape;

  // Add the body definition to world
  body_ = world.CreateBody(&bodyDef);

  // Set up the shapes
  setUp(shape, fixtureDef);
  setUp(rightshape, rightfixtureDef);
  setUp(leftshape, leftfixtureDef);
}

Award::Award() { animationTimer_ = new b2Timer(); }

int Award::getFramerate() const { return frameRate_; }
