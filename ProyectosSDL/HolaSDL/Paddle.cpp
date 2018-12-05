#include "Paddle.h"
#include "Game.h"
#include "Bullet.h"
#include <algorithm>

/// Public
/// Constructor
Paddle::Paddle(float32 x, float32 y, float32 width, float32 height, float32 anchorX, float32 limit, float32 maxSpeed, ACTIONS action, Texture *texture)
    : ArkanoidBody(x, y, width, height, texture), _rightMovement(false), _leftMovement(false),
      _leftAnchor(anchorX - limit), _rightAnchor(anchorX + limit), _speed(maxSpeed), _sticky(true), _actionType(action)
{
  setAction(action);
  setBody(x, y, width, height, anchorX, limit, *Game::getWorld());
}

/// Public
// Destructor
Paddle::~Paddle()
{
  for (auto joint : _joints)
  {
    delete joint;
  }
  _joints.clear();
}

/// Public Virtual
// Defines the update behaviour for this instance
void Paddle::update()
{
  for (auto joint : _joints)
  {
    b2Vec2 pos = getPosition() + joint->_distance;
    joint->_ball->setPosition(pos.x, pos.y);
  }
}

/// Public Virtual
// Defines the after update behaviour for this instance
void Paddle::afterUpdate()
{
  // Get position
  b2Vec2 pos = _body->GetPosition();

  // If the paddle is in the walls, move it inside the area
  if (pos.x - _size.x / 2.0f < _leftAnchor)
  {
    setPosition(_leftAnchor + _size.x / 2.0f, pos.y);
  }
  else if (pos.x + _size.x / 2.0f > _rightAnchor)
  {
    setPosition(_rightAnchor - _size.x / 2.0f, pos.y);
  }
}

/// Public Virtual
// Defines the render behaviour
void Paddle::render() const
{
  b2Vec2 pos = _body->GetPosition();
  _texture->render({(int)pos.x - (int)_size.x / 2, (int)pos.y - (int)_size.y / 2, (int)_size.x, (int)_size.y});
}

/// Publc Virtual
// Defines the event handler behaviour
void Paddle::handleEvents(SDL_Event event)
{
  switch (event.type)
  {
  // If it's a key press
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym)
    {
    // If right arrow was pressed, set rightMovement to true
    case SDLK_RIGHT:
      _rightMovement = true;
      break;
    // If left arrow was pressed, set leftMovement to true
    case SDLK_LEFT:
      _leftMovement = true;
      break;
    // If space bar was pressed, call _action()
    case SDLK_SPACE:
      State::current->addEvent(_action);
      break;
    }
    break;
  // If it's a key leave
  case SDL_KEYUP:
    switch (event.key.keysym.sym)
    {
    // If the right arrow was unpressed, set rightMovement to false
    case SDLK_RIGHT:
      _rightMovement = false;
      break;
    // If the left arrow was unpressed, set leftMovement to false
    case SDLK_LEFT:
      _leftMovement = false;
      break;
    }
  }

  // Set the velocity
  setVelocity(b2Vec2{
      (_rightMovement ? _speed : 0) + (_leftMovement ? -_speed : 0),
      0.0f});
}

/// Public Virtual
// Defines behaviour when the instance starts to have contact with an element
void Paddle::onBeginContact(RigidBody *rigigbody)
{
  Ball *ball;
  if (_sticky && (ball = dynamic_cast<Ball *>(rigigbody)))
  {
    State::current->addEvent([this, ball]() { jointTo(ball); });
  }
}

/// Public Virtual
// Defines the setWidth behaviour
void Paddle::setWidth(float32 width)
{
  // Gets the position and linear velocity, then destroy the fixture and the body
  b2Vec2 pos = _body->GetPosition();
  b2Vec2 vel = _body->GetLinearVelocity();
  _body->DestroyFixture(_fixture);
  Game::getWorld()->DestroyBody(_body);

  // Sets the new width and creates a new body and velocity
  _size.x = width;
  setBody(pos.x, pos.y, width, _size.y, _leftAnchor - _rightAnchor,
          (_rightAnchor - _leftAnchor) / 2.0f, *Game::getWorld());
  setVelocity(vel);
}

/// Public
// Creates a joint to a ball (for the sticky paddle)
void Paddle::jointTo(Ball *ball)
{
  if (!any_of(_joints.begin(), _joints.end(), [ball](ArkanoidJoint *joint) { return joint->_ball == ball; }))
  {

    b2Vec2 a = ball->getPosition() - getPosition();

    _joints.push_back(new ArkanoidJoint(ball, a));
    ball->getBody()->SetActive(false);
  }
}

/// Public
// Splits from a ball, releasing it to a direction away from the paddle's center
void Paddle::splitFromBalls()
{
  for (auto joint : _joints)
  {
    joint->_ball->getBody()->SetActive(true);
    joint->_distance *= (1.0f / (joint->_distance.LengthSquared() * joint->_ball->getSpeed()));
    joint->_ball->setVelocity(joint->_distance);
    delete joint;
  }
  _joints.clear();
}

/// Public Virtual
// Defines the deserialize method behaviour to patch the instance when loading a file save
std::istream &Paddle::deserialize(std::istream &out)
{
  _texture = readTexture(out);
  float32 posx, posy, sizex, sizey;
  int action;
  out >> posx >> posy >> sizex >> sizey >> _speed >> action;
  setBody(posx, posy, sizex, sizey, ArkanoidSettings::sceneUpperLeftCorner.x + ArkanoidSettings::sceneWidth / 2.0f,
          (ArkanoidSettings::sceneWidth) / 2 - ArkanoidSettings::wallWidth, *Game::getWorld());
  setPosition(posx, posy);
  _size.Set(sizex, sizey);
  _leftAnchor = ArkanoidSettings::sceneUpperLeftCorner.x + ArkanoidSettings::wallWidth;
  _rightAnchor = ArkanoidSettings::sceneUpperLeftCorner.x + ArkanoidSettings::sceneWidth - ArkanoidSettings::wallWidth;
  _leftMovement = false;
  _rightMovement = false;
  _actionType = (ACTIONS)action;
  setAction(_actionType);
  return out;
}

/// Public Virtual
// Defines the serialize method behaviour to save the data into a file save
std::ostream &Paddle::serialize(std::ostream &is) const
{
  return is << "Paddle " << textureIndex() << " " << getPosition().x << " " << getPosition().y << " " << getSize().x << " " << getSize().y << " "
            << _speed << _actionType;
}

/// Private
// setBody method, creates a kinematic chain shape with Box2D's API
void Paddle::setBody(float32 x, float32 y, float32 width, float32 height, float32 anchorX, float32 limit, b2World &world)
{
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
  _body = world.CreateBody(&bodyDef);

  // Set up the shape
  setUp(shape, fixtureDef);
}

/// Public
// Defines the setWidth behaviour
void Paddle::setAction(ACTIONS action)
{
  _actionType = action;
  // Set the proper action.
  switch (action)
  {
  case NONE:
    splitFromBalls();
    setSticky(false);
    _action = []() {};
    break;
  case BEGIN:
    splitFromBalls();
    setSticky(true);
    _action = [this]() {splitFromBalls(); setSticky(false); };
    break;
  case STICKY:
    setSticky(true);
    _action = [this]() { splitFromBalls(); };
    break;
  case LASER:
    splitFromBalls();
    setSticky(false);
    _action = [this]() {
      /*Create Bullet*/
      Bullet *bullet = new Bullet(getPosition().x, getPosition().y, 10.0f, 1000.0f, Game::current->getTextures()[BALLBLACK]);
      State::current->add(*bullet);
      bullet->setVelocity(b2Vec2{0, -1000.0f});
    };
    break;
  default:
    break;
  }
}

Paddle::ArkanoidJoint::ArkanoidJoint(Ball *ball, b2Vec2 &distance)
    : _ball(ball), _distance(distance) {}

Paddle::ArkanoidJoint::~ArkanoidJoint(){};
