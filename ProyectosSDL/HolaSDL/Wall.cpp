#include "Wall.h"
#include "Game.h"

Wall::Wall(float32 x, float32 y, float32 width, float32 height, Texture *texture)
    : ArkanoidBody(x, y, width, height, texture)
{
  setBody(x, y, width, height, *Game::getWorld());
}

/// Public Victual
/// Updates the update behaviour
void Wall::update() {}

/// Public Virtual
/// Defines the render behaviour
void Wall::render() const
{
  b2Vec2 pos = _body->GetPosition();
  _texture->renderFrame({(int)pos.x - (int)getSize().x / 2, (int)pos.y - (int)getSize().y / 2, (int)getSize().x, (int)getSize().y}, 0, 0);
}

/// Public Virtual
/// Defines the deserialize method behaviour to patch the instance when loading a file save
std::istream &Wall::deserialize(std::istream &out)
{
  _texture = readTexture(out);
  float32 posx, posy, sizex, sizey;
  out >> posx >> posy >> sizex >> sizey;
  setBody(posx, posy, sizex, sizey, *Game::getWorld());
  setPosition(posx, posy);
  _size.Set(sizex, sizey);
  return out;
}

/// Public Virtual
/// Defines the serialize method behaviour to save the data into a file save
std::ostream &Wall::serialize(std::ostream &is) const
{
  return is << "Wall " << textureIndex() << " " << getPosition().x << " " << getPosition().y << " " << getSize().x << " " << getSize().y;
}

void Wall::setBody(float32 x, float32 y, float32 width, float32 height, b2World &world)
{
  b2BodyDef bodyDef;
  bodyDef.type = b2_staticBody;
  bodyDef.fixedRotation = true;
  bodyDef.position.x = x;
  bodyDef.position.y = y;
  bodyDef.linearDamping = 0.0f;
  bodyDef.userData = static_cast<RigidBody *>(this);
  b2PolygonShape shape;
  shape.SetAsBox(width / 2.0f, height / 2.0f);
  b2FixtureDef fixtureDef;
  fixtureDef.density = 1.0f;
  fixtureDef.filter.categoryBits = 0b0000'0000'0000'0000'0100;
  fixtureDef.filter.maskBits = 0b0000'0000'0000'0010'0010;
  fixtureDef.friction = 0.0f;
  //fixtureDef.isSensor = false;
  fixtureDef.restitution = 1.0f;
  fixtureDef.shape = &shape;
  // Add to world
  _body = world.CreateBody(&bodyDef);
  setUp(shape, fixtureDef);
}
