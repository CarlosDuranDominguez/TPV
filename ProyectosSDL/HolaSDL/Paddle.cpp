#include "Paddle.h"
#include "Game.h"

void Paddle::setBody(float32 x, float32 y, float32 width, float32 height, float32 anchorX, float32 anchorY, float32 limit, b2World& world) {
	b2BodyDef center;
	center.type = b2_staticBody;
	center.position.x = anchorX;
	center.position.y = anchorY;
	_anchor = world.CreateBody(&center);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
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
	fixtureDef.density = 1.0f;
	fixtureDef.filter.categoryBits = 0b0000'0000'0000'0000'0001;
	fixtureDef.filter.maskBits = 0b0000'0000'0000'0000'0010;
	fixtureDef.friction = 0.0f;
	//fixtureDef.isSensor = false;
	fixtureDef.restitution = 1.0f;
	fixtureDef.shape = &shape;
	setUp(bodyDef, shape, fixtureDef, world);

	b2PrismaticJointDef joint;
	joint.bodyA = _anchor;
	joint.bodyB = _body;
	joint.localAxisA.Set( 1,0 );
	joint.enableLimit = true;
	joint.lowerTranslation = -limit;
	joint.upperTranslation = limit;
	_joint = world.CreateJoint(&joint);
}

Paddle::Paddle() {};

Paddle::Paddle(float32 x, float32 y, float32 width, float32 height, float32 anchorX, float32 anchorY, float32 limit,float32 maxSpeed, Texture *texture)
	:ArkanoidObject(x,y,width,height,texture), _rightMovement(false), _leftMovement(false), _speed(maxSpeed){
	setBody(x, y, width, height,anchorX,anchorY,limit, *Game::getWorld());
}

Paddle::~Paddle() {
	Game::getWorld()->DestroyJoint(_joint);
	Game::getWorld()->DestroyBody(_anchor);
}

void Paddle::update() {
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
	if ((_leftMovement&&_rightMovement) || (!_leftMovement && !_rightMovement)) {
		_body->SetLinearDamping(1000.0f);
	}
	else {
		_body->SetLinearDamping(0.0f);
	}
	b2Vec2 v = {(_rightMovement ? _speed : 0) + (_leftMovement ? -_speed : 0), 0.0f};
	applyForceToCenter(v);
}

std::istream& Paddle::deserialize(std::istream& out) {
	return out;
}

std::ostream& Paddle::serialize(std::ostream& is) const {
	return is;
}