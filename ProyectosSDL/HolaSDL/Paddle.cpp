#include "Paddle.h"
#include "Game.h"

void Paddle::setBody(float32 x, float32 y, float32 width, float32 height, float32 anchorX, float32 limit, b2World& world) {	

	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.x = x;
	bodyDef.position.y = y;
	bodyDef.linearDamping = 0.0f;
	bodyDef.userData = static_cast<RigidBody*>(this);
	b2Vec2 vs[6];
	vs[0].Set(-width/2.0f, height/2.0f);
	vs[1].Set(-width*3.0/8.0f, -height / 4.0f);
	vs[2].Set(-width / 8.0f, -height / 2.0f);
	vs[3].Set(width / 8.0f, -height / 2.0f);
	vs[4].Set(width*3.0 / 8.0f, -height / 4.0f);
	vs[5].Set(width / 2.0f, height / 2.0f);
	b2ChainShape shape;
	shape.CreateChain(vs, 6);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1000000.0f;
	fixtureDef.filter.categoryBits = 0b0000'0000'0000'0000'0001;
	fixtureDef.filter.maskBits = 0b0000'0000'0000'0011'0010;
	fixtureDef.friction = 0.0f;
	//fixtureDef.isSensor = false;
	fixtureDef.restitution = 1.0f;
	fixtureDef.shape = &shape;

	// Add to world
	_body = world.CreateBody(&bodyDef);
	setUp(shape, fixtureDef);
	
}

Paddle::Paddle() {};

Paddle::Paddle(float32 x, float32 y, float32 width, float32 height, float32 anchorX, float32 limit,float32 maxSpeed, Texture *texture)
	:ArkanoidObject(x,y,width,height,texture), _rightMovement(false), _leftMovement(false), 
	_leftAnchor(anchorX-limit),_rightAnchor(anchorX+limit), _speed(maxSpeed) {
	setBody(x, y, width, height,anchorX,limit, *Game::getWorld());
}

Paddle::~Paddle() {
}

void Paddle::update() {
}
void Paddle::afterUpdate() {
	b2Vec2 pos = _body->GetPosition();
	if (pos.x - _size.x / 2.0f < _leftAnchor) {
		setPosition(b2Vec2{ _leftAnchor + _size.x / 2.0f,pos.y });
	}
	else if (pos.x + _size.x / 2.0f > _rightAnchor){
		setPosition(b2Vec2{ _rightAnchor - _size.x / 2.0f,pos.y });
	}
}

void Paddle::render() const {
	b2Vec2 pos = _body->GetPosition();
	_texture->render({ (int)pos.x - (int)_size.x / 2, (int)pos.y - (int)_size.y / 2, (int)_size.x, (int)_size.y });
}

void Paddle::handleEvents(SDL_Event event) {
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			_rightMovement = true;
			break;
		case SDLK_LEFT:
			_leftMovement = true;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			_rightMovement = false;
			break;
		case SDLK_LEFT:
			_leftMovement = false;
			break;
		}
	}
	b2Vec2 v = {(_rightMovement ? _speed : 0) + (_leftMovement ? -_speed : 0), 0.0f};
	setVelocity(v);
}

void Paddle::setWidth(float32 width) {
	b2Vec2 pos = _body->GetPosition();
	b2Vec2 vel = _body->GetLinearVelocity();
	_body->DestroyFixture(_fixture);
	Game::getWorld()->DestroyBody(_body);
	_size.x = width;
	setBody(pos.x, pos.y, width, _size.y, _leftAnchor - _rightAnchor, 
		(_rightAnchor - _leftAnchor) / 2.0f, *Game::getWorld());
	setVelocity(vel);
}

std::istream& Paddle::deserialize(std::istream& out) {
	return out;
}

std::ostream& Paddle::serialize(std::ostream& is) const {
  return is << "Paddle" << textureIndex() << _position.x << _position.y << _size.x << _size.y
    << _speed;
}