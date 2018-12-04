#include "Block.h"
#include "Game.h"
#include "Award.h"
#include "MultiBallAward.h"
#include "EnlargenAward.h"
#include "ShortenAward.h"
#include "NextLevelAward.h"

Block::Block(float32 x, float32 y, float32 width, float32 height, int color, Texture *texture) 
	:ArkanoidObject(x, y, width, height, texture), _color(color) {
	SetBody(x, y, width, height, *Game::getWorld());
	Game::gameManager()->addBlock();
}

Block::~Block() {

}

void Block::update() { 
}

void Block::render() const{
	b2Vec2 pos = _body->GetPosition();
	_texture->renderFrame({ (int)pos.x - (int)getSize().x / 2, (int)pos.y - (int)getSize().y / 2, (int)getSize().x, (int)getSize().y }, _color/3, _color%3);
}

void Block::SetBody(float32 x, float32 y, float32 width, float32 height, b2World& world) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.x = x;
	bodyDef.position.y = y;
	bodyDef.linearDamping = 0.0f;
	bodyDef.userData = static_cast<RigidBody*>(this);
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

void Block::contact() {
	destroy();
	State::current->addEvent([this]() {
		Award *award = nullptr;
		switch (rand()%40)
		{
		case 0:
			award = new MultiBallAward(_body->GetPosition().x, _body->GetPosition().y,
				100, 40, 10, Game::current->getTextures()[REWARD6]);
			break;
		case 1:
			award = new EnlargenAward(_body->GetPosition().x, _body->GetPosition().y,
				100, 40, 10, Game::current->getTextures()[REWARD2]);
			break;
		case 2:
			award = new ShortenAward(_body->GetPosition().x, _body->GetPosition().y,
				100, 40, 10, Game::current->getTextures()[REWARD4]);
			break;
		case 3:
			award = new NextLevelAward(_body->GetPosition().x, _body->GetPosition().y,
				100, 40, 10, Game::current->getTextures()[REWARD1]);
			break;
		default:
			break;
		}
		if (award != nullptr) {
			State::current->add(*award);
			award->setVelocity(b2Vec2{ 0, 500.0f });
		}
	});
}

void Block::destroy() {
	GameObject::destroy();
	Game::gameManager()->deleteBlock();
}

std::istream& Block::deserialize(std::istream&  is) {
	is >> _color >> _position.x >> _position.y >> _size.x >> _size.y;
	SetBody(_position.x, _position.y, _size.x, _size.y, *Game::getWorld());
	return is;
}

std::ostream& Block::serialize(std::ostream& is) const {
  return is << "Block" << textureIndex() << _position.x << _position.y << _size.x << _size.y;
}
