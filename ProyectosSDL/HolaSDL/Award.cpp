#include "Award.h"
#include <iostream>
#include <string>
#include "Game.h"
#include "Paddle.h"
#include "SDL.h"

// Constructor
Award::Award(const float32 x, const float32 y, const float32 width,
             const float32 height, const float32 speed, const Uint32 frameRate,
             Texture *texture)
    : ArkanoidBody(x, y, width, height, texture),
      frameRate_(frameRate),
      frame_(0),
      animationTimer_(SDL_GetTicks()),
      speed_(speed),
      contacted_(false) {
  setBody(x, y, width, height, *Game::getWorld());
}

Award::Award()
    : frameRate_(0),
      frame_(0),
      animationTimer_(SDL_GetTicks()),
      speed_(0),
      contacted_(false) {}

// Destructor
Award::~Award() = default;

// Updates the update behaviour
void Award::update() {
  // If the counter's milliseconds counted over 1000 milliseconds divided by
  // the framerate frequency, go to the next frame to continue the animation
  if (SDL_GetTicks() - animationTimer_ > 1000.0f / frameRate_) {
    // If the next frame is outside the animation range, go to to the first
    // frame
    if (++frame_ > texture_->getNumCols() * texture_->getNumRows()) {
      frame_ = 0;
    }

    // Reset the timer
    animationTimer_ = SDL_GetTicks();
  }
}

// Defines the render behaviour
void Award::render() const {
  const auto pos = body_->GetPosition();

  texture_->renderFrame(
      {int(pos.x) - int(getSize().x) / 2, int(pos.y) - int(getSize().y) / 2,
       int(getSize().x), int(getSize().y)},
      frame_ / (texture_->getNumCols() + 1), frame_ % texture_->getNumCols());
}

// Defines behaviour when the instance gets in contact with the instance
void Award::contact() { destroy(); }

// Defines behaviour when the instance is to be destroyed
void Award::destroy() {
  // Call inherited destroy method from GameObject
  GameObject::destroy();
}

// Defines behaviour after every update cycle
void Award::afterUpdate() {
  if (getVelocity().y != speed_) {
    b2Vec2 v{0, speed_};
    setVelocity(v);
  }
}

// Defines behaviour when the instance starts to have contact with an element
void Award::onBeginContact(RigidBody *rigidbody) {
  // If the contact was done with the paddle, set _contacted to true
  if (!contacted_ && dynamic_cast<Paddle *>(rigidbody)) {
    contacted_ = true;
    contact();
  }
}

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

// Defines the serialize method behaviour to save the data into a file save
std::ostream &Award::serialize(std::ostream &is) const {
  string a = typeid(*this).name();
  a = a.substr(6);
  return is << a << " " << textureIndex() << " " << getPosition().x << " "
            << getPosition().y << " " << getSize().x << " " << getSize().y
            << " " << speed_ << " " << frameRate_;
}

// setBody method, creates a dynamic polygon shape with Box2D's API
void Award::setBody(float32 x, float32 y, float32 width, float32 height,
                    b2World &world) {
  auto radius = height / 2.0f;

  // Create the body definition
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.fixedRotation = true;
  bodyDef.position.x = x;
  bodyDef.position.y = y;
  bodyDef.linearDamping = 0.0f;
  bodyDef.userData = static_cast<RigidBody *>(this);

  // Create the polygon shape as a box
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
  b2CircleShape leftShape;
  leftShape.m_p.x = radius - width;
  leftShape.m_p.y = 0;
  leftShape.m_radius = radius;

  // Create the fixture definition for the left side of the capsule
  b2FixtureDef leftFixtureDef;
  leftFixtureDef.density = 1.0f;
  leftFixtureDef.filter.categoryBits = 0b0000'0000'0000'0001'0000;
  leftFixtureDef.filter.maskBits = 0b0000'0000'0000'0000'0001;
  leftFixtureDef.friction = 0.0f;
  leftFixtureDef.isSensor = true;
  leftFixtureDef.restitution = 0.0f;
  leftFixtureDef.shape = &leftShape;

  // Create the circle shape
  b2CircleShape rightShape;
  leftShape.m_p.x = width - radius;
  leftShape.m_p.y = 0;
  leftShape.m_radius = radius;

  // Create the fixture definition for the right side of the capsule
  b2FixtureDef rightFixtureDef;
  rightFixtureDef.density = 1.0f;
  rightFixtureDef.filter.categoryBits = 0b0000'0000'0000'0001'0100;
  rightFixtureDef.filter.maskBits = 0b0000'0000'0000'0000'0001;
  rightFixtureDef.friction = 0.0f;
  rightFixtureDef.isSensor = true;
  rightFixtureDef.restitution = 0.0f;
  rightFixtureDef.shape = &leftShape;

  // Add the body definition to world
  body_ = world.CreateBody(&bodyDef);

  // Set up the shapes
  setUp(shape, fixtureDef);
  setUp(rightShape, rightFixtureDef);
  setUp(leftShape, leftFixtureDef);
}

int Award::getFramerate() const { return frameRate_; }
