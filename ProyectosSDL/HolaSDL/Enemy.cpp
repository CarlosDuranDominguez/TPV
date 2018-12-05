#include "Enemy.h"
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include <random>

/// Public
// Constructor
Enemy::Enemy(float32 x, float32 y, float32 width, float32 height, float32 maxSpeed, float32 halfLife,
             float32 changeProbability, float32 framerate, Texture *texture)
    : ArkanoidBody(x, y, width, height, texture), _speed(maxSpeed), _halfLife(halfLife),
      _changeProbability(changeProbability), _timer(new b2Timer()), _animationTimer(new b2Timer()), _framerate(framerate), _frame(0)
{
  setBody(x, y, width / 2.0f, *Game::getWorld());
  float32 ra = (float32)rand() / (RAND_MAX + 1.0f) * (float32)M_PI * 2.0f;
  setVelocity(b2Vec2{sin(ra) * _speed, cos(ra) * _speed});
  _timer->Reset();
  _animationTimer->Reset();
}

/// Public
// Destructor
Enemy::~Enemy()
{
  delete _timer;
  delete _animationTimer;
}

/// Public Victual
// Updates the update behaviour
void Enemy::update()
{
  if (_timer->GetMilliseconds() > _halfLife * 1000.0f)
  {
    if (rand() / (RAND_MAX + 1.) <= _changeProbability)
    {
      float32 ra = (float32)rand() / (RAND_MAX + 1.0f) * (float32)M_PI * 2.0f;
      setVelocity(b2Vec2{sin(ra) * _speed, cos(ra) * _speed});
    }
    _timer->Reset();
  }
  if (_animationTimer->GetMilliseconds() > 1000.0f / _framerate)
  {
    if ((++_frame) > _texture->getNumCols() * _texture->getNumRows())
    {
      _frame = 0;
    }
    _animationTimer->Reset();
  }
}

/// Public Virtual
// Defines the render behaviour
void Enemy::render() const
{
  b2Vec2 pos = _body->GetPosition();

  _texture->renderFrame({(int)pos.x - (int)getSize().x / 2, (int)pos.y - (int)getSize().y / 2,
                         (int)_fixture->GetShape()->m_radius * 2, (int)_fixture->GetShape()->m_radius * 2},
                        _frame / (_texture->getNumCols() + 1), _frame % _texture->getNumCols());
}

/// Public Virtual
// Defines behaviour when the instance starts to have contact with an element
void Enemy::onBeginContact(RigidBody *rigidBody)
{
  // If the contact was made with a ball or the paddle
  if (dynamic_cast<Ball *>(rigidBody) || dynamic_cast<Paddle *>(rigidBody))
  {
    // Destroy and add 50 points to the score
    destroy();
    Game::getGameManager()->addScore(50);
  }
}

/// Public Virtual
// Defines the deserialize method behaviour to patch the instance when loading a file save
std::istream &Enemy::deserialize(std::istream &out)
{
  _texture = readTexture(out);
  float32 posx, posy, radius, velx, vely;
  out >> posx >> posy >> radius >> velx >> vely >> _speed >> _halfLife >> _changeProbability >> _framerate >> _frame;
  setBody(posx, posy, radius, *Game::getWorld());
  setPosition(posx, posy);
  setVelocity(b2Vec2{velx, vely});
  _timer = new b2Timer();
  _animationTimer = new b2Timer();
  return out;
}

/// Public Virtual
// Defines the serialize method behaviour to save the data into a file save
std::ostream &Enemy::serialize(std::ostream &is) const
{
  return is << "Enemy " << textureIndex() << " " << _position.x << " " << _position.y << " "
            << _fixture->GetShape()->m_radius << " " << getVelocity().x << " " << getVelocity().y << " "
            << _speed << " " << _halfLife << " " << _changeProbability << " " << _framerate << " " << _frame;
}

/// Private
// setBody method, creates a dynamic circle shape with Box2D's API
void Enemy::setBody(float32 x, float32 y, float32 radius, b2World &world)
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
  _body = world.CreateBody(&bodyDef);

  // Set up the shape
  setUp(shape, fixtureDef);
}
