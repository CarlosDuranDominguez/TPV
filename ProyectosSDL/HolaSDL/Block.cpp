#include "Block.h"
#include "Game.h"
#include "Award.h"
#include "MultiBallAward.h"
#include "EnlargenAward.h"
#include "ShortenAward.h"
#include "NextLevelAward.h"

Block::Block(float32 x, float32 y, float32 width, float32 height, int color, Texture *texture)
    : ArkanoidBody(x, y, width, height, texture), _color(color)
{
  setBody(x, y, width, height, *Game::getWorld());
  Game::gameManager()->addBlock();
}

Block::~Block()
{
}

/// Public Victual
/// Updates the update behaviour
void Block::update()
{
}

/// Public Virtual
/// Defines the render behaviour
void Block::render() const
{
  b2Vec2 pos = _body->GetPosition();
  _texture->renderFrame({(int)pos.x - (int)getSize().x / 2, (int)pos.y - (int)getSize().y / 2, (int)getSize().x, (int)getSize().y}, _color / 3, _color % 3);
}

void Block::setBody(float32 x, float32 y, float32 width, float32 height, b2World &world)
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

  _body = world.CreateBody(&bodyDef);
  setUp(shape, fixtureDef);
}

/// Public Virtual
/// Defines behaviour when the instance gets in contact with the instance
void Block::contact()
{
  // Destroy the block on contact
  destroy();

  // Create a new randomized event that throws an award
  State::current->addEvent([this]() {
    Award *award = nullptr;
    switch (rand() % 40)
    {
    case 0:
      award = new MultiBallAward(_body->GetPosition().x, _body->GetPosition().y,
                                 ArkanoidSettings::rewardWidth,
                                 ArkanoidSettings::rewardHeigth,
                                 ArkanoidSettings::rewardSpeed,
                                 ArkanoidSettings::rewardFramerate,
                                 Game::current->getTextures()[REWARD6]);
      break;
    case 1:
      award = new EnlargenAward(_body->GetPosition().x, _body->GetPosition().y,
                                ArkanoidSettings::rewardWidth,
                                ArkanoidSettings::rewardHeigth,
                                ArkanoidSettings::rewardSpeed,
                                ArkanoidSettings::rewardFramerate,
                                Game::current->getTextures()[REWARD2]);
      break;
    case 2:
      award = new ShortenAward(_body->GetPosition().x, _body->GetPosition().y,
                               ArkanoidSettings::rewardWidth,
                               ArkanoidSettings::rewardHeigth,
                               ArkanoidSettings::rewardSpeed,
                               ArkanoidSettings::rewardFramerate,
                               Game::current->getTextures()[REWARD4]);
      break;
    case 3:
      award = new NextLevelAward(_body->GetPosition().x, _body->GetPosition().y,
                                 ArkanoidSettings::rewardWidth,
                                 ArkanoidSettings::rewardHeigth,
                                 ArkanoidSettings::rewardSpeed,
                                 ArkanoidSettings::rewardFramerate,
                                 Game::current->getTextures()[REWARD1]);
      break;
    default:
      break;
    }

    // If award is not null, add it and set its velocity
    if (award != nullptr)
    {
      State::current->add(*award);
      award->setVelocity(b2Vec2{0, 500.0f});
    }
  });
}

/// Public Virtual
/// Defines behaviour when the instance is to be destroyed
void Block::destroy()
{
  GameObject::destroy();
  Game::gameManager()->deleteBlock();
}

/// Public Virtual
/// Defines the deserialize method behaviour to patch the instance when loading a file save
std::istream &Block::deserialize(std::istream &out)
{
  _texture = readTexture(out);
  float32 posx, posy, sizex, sizey;
  out >> posx >> posy >> sizex >> sizey >> _color;
  setBody(posx, posy, sizex, sizey, *Game::getWorld());
  setPosition(posx, posy);
  _size.Set(sizex, sizey);
  return out;
}

/// Public Virtual
/// Defines the serialize method behaviour to save the data into a file save
std::ostream &Block::serialize(std::ostream &is) const
{
  return is << "Block " << textureIndex() << " " << getPosition().x << " " << getPosition().y << " " << getSize().x << " " << getSize().y
            << " " << _color;
}
