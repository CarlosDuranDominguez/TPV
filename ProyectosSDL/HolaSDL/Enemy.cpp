#include "Enemy.h"
#include <random>
#include "Ball.h"
#include "Game.h"
#include "Paddle.h"

/// Public
// Constructor
Enemy::Enemy(const float32 x, const float32 y, const float32 width,
             const float32 height, const float32 maxSpeed,
             const float32 halfLife, const float32 changeProbability,
             const float32 framerate, Texture *texture)
    : ArkanoidBody(x, y, width, height, texture),
      speed_(maxSpeed),
      halfLife_(halfLife),
      changeProbability_(changeProbability),
      framerate_(framerate),
      timer_(new b2Timer()),
      animationTimer_(new b2Timer()),
      frame_(0) {
  setBody(x, y, width / 2.0f, *Game::getWorld());
  const auto ra = float32(rand()) / (RAND_MAX + 1.0f) * float32(M_PI) * 2.0f;
  setVelocity(b2Vec2{sin(ra) * speed_, cos(ra) * speed_});
  timer_->Reset();
  animationTimer_->Reset();
}

Enemy::Enemy()
    : speed_(0),
      halfLife_(0),
      changeProbability_(0),
      framerate_(0),
      timer_(nullptr),
      animationTimer_(nullptr),
      frame_(0) {}

// Destructor
Enemy::~Enemy() {
  delete timer_;
  delete animationTimer_;
}

void Enemy::setPosition(const float32 x, const float32 y) {
  RigidBody::setPosition(b2Vec2{x, y});
  GameObject::setPosition(x, y);
}

// Updates the update behaviour
void Enemy::update() {
  if (timer_->GetMilliseconds() > halfLife_ * 1000.0f) {
    if (rand() / (RAND_MAX + 1.) <= changeProbability_) {
      const auto ra =
          float32(rand()) / (RAND_MAX + 1.0f) * float32(M_PI) * 2.0f;
      setVelocity(b2Vec2{sin(ra) * speed_, cos(ra) * speed_});
    }
    timer_->Reset();
  }
  if (animationTimer_->GetMilliseconds() > 1000.0f / framerate_) {
    if ((++frame_) > texture_->getNumCols() * texture_->getNumRows()) {
      frame_ = 0;
    }
    animationTimer_->Reset();
  }
}

// Defines the render behaviour
void Enemy::render() const {
  const auto pos = body_->GetPosition();

  texture_->renderFrame(
      {int(pos.x) - int(getSize().x) / 2, int(pos.y) - int(getSize().y) / 2,
       int(fixture_->GetShape()->m_radius) * 2,
       int(fixture_->GetShape()->m_radius) * 2},
      frame_ / (texture_->getNumCols() + 1), frame_ % texture_->getNumCols());
}

// Defines behaviour when the instance starts to have contact with an element
void Enemy::onBeginContact(RigidBody *rigidBody) {
  // If the contact was made with a ball or the paddle
  if (dynamic_cast<Ball *>(rigidBody) || dynamic_cast<Paddle *>(rigidBody)) {
    // Destroy and add 50 points to the score
    destroy();
    Game::getGameManager()->addScore(50);
  }
}

// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &Enemy::deserialize(std::istream &out) {
  texture_ = readTexture(out);
  float32 posx, posy, radius, velx, vely;
  out >> posx >> posy >> radius >> velx >> vely >> speed_ >> halfLife_ >>
      changeProbability_ >> framerate_ >> frame_;
  setBody(posx, posy, radius, *Game::getWorld());
  setPosition(posx, posy);
  setVelocity(b2Vec2{velx, vely});
  timer_ = new b2Timer();
  animationTimer_ = new b2Timer();
  return out;
}

/// Public Virtual
// Defines the serialize method behaviour to save the data into a file save
std::ostream &Enemy::serialize(std::ostream &is) const {
  return is << "Enemy " << textureIndex() << " " << position_.x << " "
            << position_.y << " " << fixture_->GetShape()->m_radius << " "
            << getVelocity().x << " " << getVelocity().y << " " << speed_ << " "
            << halfLife_ << " " << changeProbability_ << " " << framerate_
            << " " << frame_;
}

/// Private
// setBody method, creates a dynamic circle shape with Box2D's API
void Enemy::setBody(float32 x, const float32 y, const float32 radius,
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

  // Create a circle shape
  b2CircleShape shape;
  shape.m_p.Set(0.0f, 0.0f);
  shape.m_radius = radius;

  // Create the fixture definition
  b2FixtureDef fixtureDef;
  fixtureDef.density = 0.1f;
  fixtureDef.filter.categoryBits = 0b0000'0000'0000'0010'0000;
  fixtureDef.filter.maskBits = 0b0000'0000'0000'0000'1111;
  fixtureDef.friction = 0.0f;
  fixtureDef.restitution = 1.0f;
  fixtureDef.shape = &shape;

  // Add the body definition to world
  body_ = world.CreateBody(&bodyDef);

  // Set up the shape
  setUp(shape, fixtureDef);
}
