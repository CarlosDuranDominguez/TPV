#include "Award.h"
#include "Game.h"
#include "Paddle.h"

void Award::setBody(float32 x, float32 y, float32 width, float32 height, b2World& world) {

	float32 radius = height / 2.0f;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.x = x;
	bodyDef.position.y = y;
	bodyDef.linearDamping = 0.0f;
	bodyDef.userData = static_cast<RigidBody*>(this);
	b2PolygonShape shape;
	shape.SetAsBox((width - height) / 2.0f, height / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.filter.categoryBits = 0b0000'0000'0000'0001'0000;
	fixtureDef.filter.maskBits = 0b0000'0000'0000'0000'0001;
	fixtureDef.friction = 0.0f;
	fixtureDef.isSensor = true;
	fixtureDef.restitution = 0.0f;
	fixtureDef.shape = &shape;
	b2CircleShape leftshape;
	leftshape.m_p.x = radius - width;
	leftshape.m_p.y = 0;
	leftshape.m_radius = radius;
	b2FixtureDef leftfixtureDef;
	leftfixtureDef.density = 1.0f;
	leftfixtureDef.filter.categoryBits = 0b0000'0000'0000'0001'0000;
	leftfixtureDef.filter.maskBits = 0b0000'0000'0000'0000'0001;
	leftfixtureDef.friction = 0.0f;
	leftfixtureDef.isSensor = true;
	leftfixtureDef.restitution = 0.0f;
	leftfixtureDef.shape = &leftshape;
	b2CircleShape rightshape;
	leftshape.m_p.x = width - radius;
	leftshape.m_p.y = 0;
	leftshape.m_radius = radius;
	b2FixtureDef rightfixtureDef;
	rightfixtureDef.density = 1.0f;
	rightfixtureDef.filter.categoryBits = 0b0000'0000'0000'0001'0000;
	rightfixtureDef.filter.maskBits = 0b0000'0000'0000'0000'0001;
	rightfixtureDef.friction = 0.0f;
	rightfixtureDef.isSensor = true;
	rightfixtureDef.restitution = 0.0f;
	rightfixtureDef.shape = &leftshape;
	// Add to world
	_body = world.CreateBody(&bodyDef);
	setUp(shape, fixtureDef);
	setUp(rightshape, rightfixtureDef);
	setUp(leftshape, leftfixtureDef);
}

Award::Award(float32 x, float32 y, float32 width, float32 height, float32 framerate, Texture *texture)
	:ArkanoidObject(x,y,width,height,texture), _framerate(framerate), _animationTimer(new b2Timer()), _frame(0), _contacted(false) {
	setBody(x, y, width, height, *Game::getWorld());
}

Award::~Award(){
	delete _animationTimer;
}

void Award::update(){
	if (_animationTimer->GetMilliseconds() > 1000.0f / _framerate) {
		if ((++_frame) > _texture->getNumCols()*_texture->getNumRows()) {
			_frame = 0;
		}
		_animationTimer->Reset();
	}
}

void Award::render() const{
	b2Vec2 pos = _body->GetPosition();

	_texture->renderFrame({ (int)pos.x - (int)getSize().x / 2, (int)pos.y - (int)getSize().y / 2,
		(int)getSize().x, (int)getSize().y },
		_frame / (_texture->getNumCols() + 1), _frame%_texture->getNumCols());
}

void Award::contact(){
	destroy();
}

void Award::destroy(){
	GameObject::destroy();
}

void Award::onBeginContact(RigidBody* rigidbody) {
	if (!_contacted && dynamic_cast<Paddle*>(rigidbody)) {
		_contacted = true;
		contact();
	}
}

std::istream& Award::deserialize(std::istream& out){
  _texture = readTexture(out);
  float32 posx, posy, sizex, sizey;
  out >> posx >> posy >> sizex >> sizey;
  _position.Set(posx, posy);
  setBody(posx, posy, sizex, sizey, *Game::getWorld());
  _size.Set(sizex, sizey);
  out >> _framerate;
  return out;
}

std::ostream& Award::serialize(std::ostream& is) const {
  return is << typeid(*this).name() << " " << textureIndex() << " " << _position.x << " " << _position.y << " " << _size.x << " " << _size.y << " "
    << _framerate;
}
