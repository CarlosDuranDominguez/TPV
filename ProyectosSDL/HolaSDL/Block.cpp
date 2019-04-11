#include "Block.h"
#include "ArkanoidSettings.h"
#include "Award.h"
#include "EnlargenAward.h"
#include "Game.h"
#include "MultiBallAward.h"
#include "NextLevelAward.h"
#include "ShortenAward.h"
#include "StickyAward.h"

Block::Block() : color_(0) {}

Block::~Block() = default;

// Constructor
Block::Block(const float32 x, const float32 y, const float32 width,
             const float32 height, const int color, Texture *texture)
    : ArkanoidBody(x, y, width, height, texture), color_(color) {
  setBody(x, y, width, height, *Game::getWorld());
}

int Block::getColor() const { return color_; }

// Updates the update behaviour
void Block::update() {}

// Defines the render behaviour
void Block::render() const {
  const auto pos = body_->GetPosition();
  texture_->renderFrame(
      {int(pos.x) - int(getSize().x) / 2, int(pos.y) - int(getSize().y) / 2,
       int(getSize().x), int(getSize().y)},
      color_ / texture_->getNumCols(), color_ % texture_->getNumCols());
}

// Defines behaviour when the instance gets in contact with the instance
void Block::contact() {
  // Destroy the block on contact
  destroy();

  // Create a new randomized event that throws an award
  State::current_->addEvent([this]() {
    Award *award = nullptr;
    switch (rand() % 40) {
      case 0:
        award = new MultiBallAward(
            body_->GetPosition().x, body_->GetPosition().y,
            ArkanoidSettings::rewardWidth_, ArkanoidSettings::rewardHeight_,
            ArkanoidSettings::rewardSpeed_, ArkanoidSettings::rewardFramerate_,
            Game::current_->getTextures()[REWARD6]);
        break;
      case 1:
        award = new EnlargenAward(
            body_->GetPosition().x, body_->GetPosition().y,
            ArkanoidSettings::rewardWidth_, ArkanoidSettings::rewardHeight_,
            ArkanoidSettings::rewardSpeed_, ArkanoidSettings::rewardFramerate_,
            Game::current_->getTextures()[REWARD2]);
        break;
      case 2:
        award = new ShortenAward(
            body_->GetPosition().x, body_->GetPosition().y,
            ArkanoidSettings::rewardWidth_, ArkanoidSettings::rewardHeight_,
            ArkanoidSettings::rewardSpeed_, ArkanoidSettings::rewardFramerate_,
            Game::current_->getTextures()[REWARD4]);
        break;
      case 3:
        award = new NextLevelAward(
            body_->GetPosition().x, body_->GetPosition().y,
            ArkanoidSettings::rewardWidth_, ArkanoidSettings::rewardHeight_,
            ArkanoidSettings::rewardSpeed_, ArkanoidSettings::rewardFramerate_,
            Game::current_->getTextures()[REWARD1]);
        break;
      case 4:
        award = new StickyAward(
            body_->GetPosition().x, body_->GetPosition().y,
            ArkanoidSettings::rewardWidth_, ArkanoidSettings::rewardHeight_,
            ArkanoidSettings::rewardSpeed_, ArkanoidSettings::rewardFramerate_,
            Game::current_->getTextures()[REWARD1]);
        break;
      default:
        break;
    }

    // If award is not null, add it and set its velocity
    if (award != nullptr) {
      State::current_->add(*award);
      award->setVelocity(b2Vec2{0, 500.0f});
    }
  });
}

// Defines behaviour when the instance is to be destroyed
void Block::destroy() {
  // Call inherited destroy method from GameObject
  GameObject::destroy();
  Game::getGameManager()->deleteBlock();
}

// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &Block::deserialize(std::istream &out) {
  texture_ = readTexture(out);
  float32 posx, posy, sizex, sizey;
  out >> posx >> posy >> sizex >> sizey >> color_;
  setBody(posx, posy, sizex, sizey, *Game::getWorld());
  setPosition(posx, posy);
  size_.Set(sizex, sizey);
  return out;
}

// Defines the serialize method behaviour to save the data into a file save
std::ostream &Block::serialize(std::ostream &is) const {
  return is << "Block " << textureIndex() << " " << getPosition().x << " "
            << getPosition().y << " " << getSize().x << " " << getSize().y
            << " " << color_;
}

// setBody method, creates a static polygon shape with Box2D's API
void Block::setBody(const float32 x, const float32 y, const float32 width,
                    const float32 height, b2World &world) {
  // Create the body definition
  b2BodyDef bodyDef;
  bodyDef.type = b2_staticBody;
  bodyDef.fixedRotation = true;
  bodyDef.position.x = x;
  bodyDef.position.y = y;
  bodyDef.linearDamping = 0.0f;
  bodyDef.userData = static_cast<RigidBody *>(this);

  // Create the polygon shape
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

  // Add the body definition to the world
  body_ = world.CreateBody(&bodyDef);

  // Set up the shape
  setUp(shape, fixtureDef);
}
