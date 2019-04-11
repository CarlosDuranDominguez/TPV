#include "Wall.h"
#include "Game.h"

Wall::Wall() = default;

// Constructor
Wall::Wall(const float32 x, const float32 y, const float32 width,
           const float32 height, Texture *texture)
    : ArkanoidBody(x, y, width, height, texture) {
  setBody(x, y, width, height, *Game::getWorld());
}

Wall::~Wall() = default;

// Updates the update behaviour
void Wall::update() {}

// Defines the render behaviour
void Wall::render() const {
  const auto pos = body_->GetPosition();
  texture_->renderFrame(
      {int(pos.x) - int(getSize().x) / 2, int(pos.y) - int(getSize().y) / 2,
       int(getSize().x), int(getSize().y)},
      0, 0);
}

// Defines the deserialize method behaviour to patch the instance when loading
// a file save
std::istream &Wall::deserialize(std::istream &out) {
  texture_ = readTexture(out);
  float32 posx, posy, sizex, sizey;
  out >> posx >> posy >> sizex >> sizey;
  setBody(posx, posy, sizex, sizey, *Game::getWorld());
  setPosition(posx, posy);
  size_.Set(sizex, sizey);
  return out;
}

// Defines the serialize method behaviour to save the data into a file save
std::ostream &Wall::serialize(std::ostream &is) const {
  return is << "Wall " << textureIndex() << " " << getPosition().x << " "
            << getPosition().y << " " << getSize().x << " " << getSize().y;
}

// setBody method, creates a static polygon shape with Box2D's API
void Wall::setBody(const float32 x, const float32 y, const float32 width,
                   const float32 height, b2World &world) {
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
