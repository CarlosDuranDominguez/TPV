#include "Paddle.h"
#include <algorithm>
#include "ArkanoidSettings.h"
#include "Bullet.h"
#include "Game.h"

Paddle::Paddle()
    : rightMovement_(false),
      leftMovement_(false),
      speed_(0),
      leftAnchor_(0),
      rightAnchor_(0),
      sticky_(false),
      actionType_() {}

Paddle::Paddle(const float32 x, const float32 y, const float32 width,
               const float32 height, const float32 anchorX, const float32 limit,
               const float32 maxSpeed, const Actions action, Texture *texture)
    : ArkanoidBody(x, y, width, height, texture),
      rightMovement_(false),
      leftMovement_(false),
      speed_(maxSpeed),
      leftAnchor_(anchorX - limit),
      rightAnchor_(anchorX + limit),
      sticky_(true),
      actionType_(action) {
  setAction(action);
  setBody(x, y, width, height, anchorX, limit, *Game::getWorld());
}

void Paddle::setSticky(const bool sticky) { sticky_ = sticky; }

// Destructor
Paddle::~Paddle() {
  for (auto joint : joints_) {
    delete joint;
  }
  joints_.clear();
}

// Defines the update behaviour for this instance
void Paddle::update() {
  for (auto joint : joints_) {
    const auto pos = getPosition() + joint->distance_;
    joint->ball_->setPosition(pos.x, pos.y);
  }
}

// Defines the after update behaviour for this instance
void Paddle::afterUpdate() {
  // Get position
  const auto pos = body_->GetPosition();

  // If the paddle is in the walls, move it inside the area
  if (pos.x - size_.x / 2.0f < leftAnchor_) {
    setPosition(leftAnchor_ + size_.x / 2.0f, pos.y);
  } else if (pos.x + size_.x / 2.0f > rightAnchor_) {
    setPosition(rightAnchor_ - size_.x / 2.0f, pos.y);
  }
}

/// Public Virtual
// Defines the render behaviour
void Paddle::render() const {
  const auto pos = body_->GetPosition();
  texture_->render({int(pos.x) - int(size_.x) / 2,
                    int(pos.y) - int(size_.y) / 2, int(size_.x), int(size_.y)});
}

// Defines the event handler behaviour
void Paddle::handleEvents(const SDL_Event event) {
  switch (event.type) {
    // If it's a key press
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        // If right arrow was pressed, set rightMovement to true
        case SDLK_RIGHT:
          rightMovement_ = true;
          break;
        // If left arrow was pressed, set leftMovement to true
        case SDLK_LEFT:
          leftMovement_ = true;
          break;
        // If space bar was pressed, call _action()
        case SDLK_SPACE:
          State::current_->addEvent(action_);
          break;
        default:
          break;
      }
      break;
    // If it's a key leave
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
        // If the right arrow was unpressed, set rightMovement to false
        case SDLK_RIGHT:
          rightMovement_ = false;
          break;
        // If the left arrow was unpressed, set leftMovement to false
        case SDLK_LEFT:
          leftMovement_ = false;
          break;
        default:
          break;
      }
    default:
      break;
  }

  // Set the velocity
  setVelocity(b2Vec2{
      (rightMovement_ ? speed_ : 0) + (leftMovement_ ? -speed_ : 0), 0.0f});
}

// Defines behaviour when the instance starts to have contact with an element
void Paddle::onBeginContact(RigidBody *rigidBody) {
  Ball *ball;
  if (sticky_ && (ball = dynamic_cast<Ball *>(rigidBody))) {
    State::current_->addEvent([this, ball]() { jointTo(ball); });
  }
}

// Defines the setWidth behaviour
void Paddle::setWidth(const float32 width) {
  // Gets the position and linear velocity, then destroy the fixture and the
  // body
  const auto pos = body_->GetPosition();
  auto vel = body_->GetLinearVelocity();
  body_->DestroyFixture(fixture_);
  Game::getWorld()->DestroyBody(body_);

  // Sets the new width and creates a new body and velocity
  size_.x = width;
  setBody(pos.x, pos.y, width, size_.y, leftAnchor_ - rightAnchor_,
          (rightAnchor_ - leftAnchor_) / 2.0f, *Game::getWorld());
  setVelocity(vel);
}

/// Public
// Creates a joint to a ball (for the sticky paddle)
void Paddle::jointTo(Ball *ball) {
  if (!any_of(joints_.begin(), joints_.end(),
              [ball](ArkanoidJoint *joint) { return joint->ball_ == ball; })) {
    auto a = ball->getPosition() - getPosition();

    joints_.push_back(new ArkanoidJoint(ball, a));
    ball->getBody()->SetActive(false);
  }
}

// Splits from a ball, releasing it to a direction away from the paddle's center
void Paddle::splitFromBalls() {
  for (auto joint : joints_) {
    joint->ball_->getBody()->SetActive(true);
    joint->distance_ *=
        (1.0f / (joint->distance_.LengthSquared() * joint->ball_->getSpeed()));
    joint->ball_->setVelocity(joint->distance_);
    delete joint;
  }
  joints_.clear();
}

// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &Paddle::deserialize(std::istream &out) {
  texture_ = readTexture(out);
  float32 posx, posy, sizex, sizey;
  int action;
  out >> posx >> posy >> sizex >> sizey >> speed_ >> action;
  setBody(posx, posy, sizex, sizey,
          ArkanoidSettings::sceneUpperLeftCorner_.x +
              ArkanoidSettings::sceneWidth_ / 2.0f,
          (ArkanoidSettings::sceneWidth_) / 2 - ArkanoidSettings::wallWidth_,
          *Game::getWorld());
  setPosition(posx, posy);
  size_.Set(sizex, sizey);
  leftAnchor_ =
      ArkanoidSettings::sceneUpperLeftCorner_.x + ArkanoidSettings::wallWidth_;
  rightAnchor_ = ArkanoidSettings::sceneUpperLeftCorner_.x +
                 ArkanoidSettings::sceneWidth_ - ArkanoidSettings::wallWidth_;
  leftMovement_ = false;
  rightMovement_ = false;
  actionType_ = Actions(action);
  setAction(actionType_);
  return out;
}

// Defines the serialize method behaviour to save the data into a file save
std::ostream &Paddle::serialize(std::ostream &is) const {
  return is << "Paddle " << textureIndex() << " " << getPosition().x << " "
            << getPosition().y << " " << getSize().x << " " << getSize().y
            << " " << speed_ << actionType_;
}

// setBody method, creates a kinematic chain shape with Box2D's API
void Paddle::setBody(float32 x, float32 y, float32 width, float32 height,
                     float32 anchorX, float32 limit, b2World &world) {
  // Create the body definition
  b2BodyDef bodyDef;
  bodyDef.type = b2_kinematicBody;
  bodyDef.fixedRotation = true;
  bodyDef.position.x = x;
  bodyDef.position.y = y;
  bodyDef.linearDamping = 0.0f;
  bodyDef.userData = static_cast<RigidBody *>(this);

  // Create an array of 2D vectors
  b2Vec2 vs[6];
  vs[0].Set(-width / 2.0f, height / 2.0f);
  vs[1].Set(-width * 3.0f / 8.0f, -height / 4.0f);
  vs[2].Set(-width / 8.0f, -height / 2.0f);
  vs[3].Set(width / 8.0f, -height / 2.0f);
  vs[4].Set(width * 3.0f / 8.0f, -height / 4.0f);
  vs[5].Set(width / 2.0f, height / 2.0f);

  // Create a chain shape and set the array of vectors
  b2ChainShape shape;
  shape.CreateChain(vs, 6);

  // Create the fixture definition
  b2FixtureDef fixtureDef;
  fixtureDef.density = 1000000.0f;
  fixtureDef.filter.categoryBits = 0b0000'0000'0000'0000'0001;
  fixtureDef.filter.maskBits = 0b0000'0000'0000'0011'0010;
  fixtureDef.friction = 0.0f;
  fixtureDef.restitution = 1.0f;
  fixtureDef.shape = &shape;

  // Add the body definition to world
  body_ = world.CreateBody(&bodyDef);

  // Set up the shape
  setUp(shape, fixtureDef);
}

// Defines the setWidth behaviour
void Paddle::setAction(const Actions action) {
  actionType_ = action;
  // Set the proper action.
  switch (action) {
    case NONE:
      splitFromBalls();
      setSticky(false);
      action_ = []() {};
      break;
    case BEGIN:
      splitFromBalls();
      setSticky(true);
      action_ = [this]() {
        splitFromBalls();
        setSticky(false);
      };
      break;
    case STICKY:
      setSticky(true);
      action_ = [this]() { splitFromBalls(); };
      break;
    case LASER:
      splitFromBalls();
      setSticky(false);
      action_ = [this]() {
        /*Create Bullet*/
        auto bullet =
            new Bullet(getPosition().x, getPosition().y, 10.0f, 1000.0f,
                       Game::current_->getTextures()[BALLBLACK]);
        State::current_->add(*bullet);
        bullet->setVelocity(b2Vec2{0, -1000.0f});
      };
      break;
    default:
      break;
  }
}

Paddle::ArkanoidJoint::ArkanoidJoint(Ball *ball, b2Vec2 &distance)
    : distance_(distance), ball_(ball) {}

Paddle::ArkanoidJoint::~ArkanoidJoint() = default;
