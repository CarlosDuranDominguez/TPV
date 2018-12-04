#include "Award.h"
#include "Game.h"
#include "Paddle.h"

/// Public
/// Constructor
Award::Award(float32 x, float32 y, float32 width, float32 height, float32 speed, float32 framerate, Texture *texture)
    : ArkanoidBody(x, y, width, height, texture), _framerate(framerate), _animationTimer(new b2Timer()), _frame(0), _contacted(false), _speed(speed)
{
  setBody(x, y, width, height, *Game::getWorld());
}

/// Public
/// Destructor
Award::~Award()
{
  delete _animationTimer;
}

/// Public Victual
/// Updates the update behaviour
void Award::update()
{
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
/// Defines the render behaviour
void Award::render() const
{
  b2Vec2 pos = _body->GetPosition();

  _texture->renderFrame({(int)pos.x - (int)getSize().x / 2, (int)pos.y - (int)getSize().y / 2,
                         (int)getSize().x, (int)getSize().y},
                        _frame / (_texture->getNumCols() + 1), _frame % _texture->getNumCols());
}

/// Public Virtual
/// Defines behaviour when the instance gets in contact with the instance
void Award::contact()
{
  destroy();
}

/// Public Virtual
/// Defines behaviour when the instance is to be destroyed
void Award::destroy()
{
  // Calls GameObject's destroy method
  GameObject::destroy();
}

/// Public Virtual
/// Defines behaviour when the instance starts to have contact with an element
void Award::onBeginContact(RigidBody *rigidbody)
{
  // If the contact was done with the paddle, set _contacted to true
  if (!_contacted && dynamic_cast<Paddle *>(rigidbody))
  {
    _contacted = true;
    contact();
  }
}

/// Public Virtual
/// Defines the deserialize method behaviour to patch the instance when loading a file save
std::istream &Award::deserialize(std::istream &out)
{
  _texture = readTexture(out);
  float32 posx, posy, sizex, sizey;
  out >> posx >> posy >> sizex >> sizey;
  setBody(posx, posy, sizex, sizey, *Game::getWorld());
  setPosition(posx, posy);
  _size.Set(sizex, sizey);
  out >> _framerate;
  return out;
}

/// Public Virtual
/// Defines the serialize method behaviour to save the data into a file save
std::ostream &Award::serialize(std::ostream &is) const
{
  return is << typeid(*this).name() << " " << textureIndex() << " " << getPosition().x << " " << getPosition().y << " " << getSize().x << " " << getSize().y << " "
            << _framerate;
}

/// Private
/// setBody method, creates a dynamic polygon shape with Box2D's API
void Award::setBody(float32 x, float32 y, float32 width, float32 height, b2World &world)
{
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
  rightfixtureDef.filter.categoryBits = 0b0000'0000'0000'0001'0000;
  rightfixtureDef.filter.maskBits = 0b0000'0000'0000'0000'0001;
  rightfixtureDef.friction = 0.0f;
  rightfixtureDef.isSensor = true;
  rightfixtureDef.restitution = 0.0f;
  rightfixtureDef.shape = &leftshape;

  // Add the body definition to world
  _body = world.CreateBody(&bodyDef);

  // Set up the shapes
  setUp(shape, fixtureDef);
  setUp(rightshape, rightfixtureDef);
  setUp(leftshape, leftfixtureDef);
}
