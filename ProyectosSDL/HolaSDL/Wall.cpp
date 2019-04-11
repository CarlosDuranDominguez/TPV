#include "Wall.h"
#include "Game.h"

/// Public
/// Constructor
Wall::Wall(float32 x, float32 y, float32 width, float32 height,
           Texture *texture)
    : ArkanoidBody(x, y, width, height, texture) {
  setBody(x, y, width, height, *Game::getWorld());
}

/// Public Virtual
/// Updates the update behaviour
void Wall::update() {}

/// Public Virtual
/// Defines the render behaviour
void Wall::render() const {
  b2Vec2 pos = body_->GetPosition();
  texture_->renderFrame(
      {(int)pos.x - (int)getSize().x / 2, (int)pos.y - (int)getSize().y / 2,
       (int)getSize().x, (int)getSize().y},
      0, 0);
}

/// Public Virtual
/// Defines the deserialize method behaviour to patch the instance when loading
/// a file save
std::istream &Wall::deserialize(std::istream &out) {
  texture_ = readTexture(out);
  float32 posx, posy, sizex, sizey;
  out >> posx >> posy >> sizex >> sizey;
  setBody(posx, posy, sizex, sizey, *Game::getWorld());
  setPosition(posx, posy);
  size_.Set(sizex, sizey);
  return out;
}

/// Public Virtual
/// Defines the serialize method behaviour to save the data into a file save
std::ostream &Wall::serialize(std::ostream &is) const {
  return is << "Wall " << textureIndex() << " " << getPosition().x << " "
            << getPosition().y << " " << getSize().x << " " << getSize().y;
}

/// Private
// setBody method, creates a static polygon shape with Box2D's API
void Wall::setBody(float32 x, float32 y, float32 width, float32 height,
                   b2World &world) {
  // Create the body definition
  b2BodyDef bodyDef;
  bodyDef.type = b2_staticBody;
  bodyDef.fixedRotation = true;
  bodyDef.position.x = x;
  bodyDef.position.y = y;
  bodyDef.linearDamping = 0.0f;
  bodyDef.userData = static_cast<RigidBody *>(this);

  // Create a polygon shape
  b2PolygonShape shape;
  shape.SetAsBox(width / 2.0f, height / 2.0f);

  // Create the fixture definition
  b2FixtureDef fixtureDef;
  fixtureDef.density = 1.0f;
  fixtureDef.filter.categoryBits = 0b0000'0000'0000'0000'0100;
  fixtureDef.filter.maskBits = 0b0000'0000'0000'0010'0010;
  fixtureDef.friction = 0.0f;
  fixtureDef.restitution = 1.0f;
  fixtureDef.shape = &shape;

  // Add the body definition to world
  body_ = world.CreateBody(&bodyDef);

  // Set up the shape
  setUp(shape, fixtureDef);
}

Wall::Wall() {
}

Wall::~Wall() {
}
