#include "State.h"
#include "Game.h"
#include "Block.h"
#include "Wall.h"
#include "Ball.h"
#include "Paddle.h"
#include "Button.h"
#include "Award.h"
#include "EnlargenAward.h"
#include "LaserAward.h"
#include "MultiBallAward.h"
#include "NextLevelAward.h"
#include "ShortenAward.h"
#include "StickyAward.h"
#include <fstream>
#include "CollisionLogic.h"


/**
 * Constructor.
 */

void State::_create() {
	for (auto instance : _pendingOnCreate) {
		create(instance->type, instance->position);
		delete instance;
	}
	_pendingOnCreate.clear();
}
void State::_render() const {
	SDL_RenderClear(_renderer);
	for (auto gameObject : _gameObjects) {
		gameObject->render();
	}
	SDL_RenderPresent(_renderer);
}

void State::_update() {
	for (auto gameObject : _gameObjects) {
		gameObject->update();
	}
}

void State::_handleEvents() {
  SDL_Event event;
  while (!_exit && SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      _exit = true;
      _game->changeState(States::GAMEOVER);
    }
    for (auto gameObject : _gameObjects) {
	    gameObject->handleEvents(event);
    }
  }
}

void State::_fixUpdate(float32 time) {
	_world->Step(time, 8, 3);
}

void State::_afterUpdate() {
	for (auto gameObject : _gameObjects) {
		gameObject->afterUpdate();
	}
}

void State::_destroy() {
	for (list<GameObject*>::iterator object : _pendingOnDestroy) {
		if (*object != nullptr) {
			delete *object;
			_gameObjects.erase(object);
		}
	}
	_pendingOnDestroy.clear();
}

void State::_events() {
	while (!_pendingEvents.empty()) {
		_pendingEvents.top()();
		_pendingEvents.pop();
	}
}

State* State::current = nullptr;

void State::destroy(list<GameObject*>::iterator& gameObjectId) {
	for (auto it = _pendingOnDestroy.begin(); it != _pendingOnDestroy.end(); ++it) {
		if (*it == gameObjectId) {
			return;
		}
	}
	_pendingOnDestroy.push_back(gameObjectId);
}

State::State(Game *game, SDL_Renderer *renderer)
	: _game(game), _renderer(renderer), _stateTime(new ArkanoidTimer()){
	_world = new b2World(b2Vec2(0.0f, 0.0f));
	_listenerLogic = new CollisionLogic();
	_world->SetContactListener(_listenerLogic);
}

State::~State() {
	for (auto gameObject : _gameObjects) {
		delete gameObject;
	}
	_pendingOnDestroy.clear();
	_gameObjects.clear();
	delete _stateTime;
	delete _world;
	delete _listenerLogic;
}

void State::run() {

	b2Timer startTime;
	while (!_exit)
	{
		_create();
		_handleEvents();
		_update();
		if (startTime.GetMilliseconds()/1000.0f >= 1.0f/(FRAMERATE))
		{
			_fixUpdate(startTime.GetMilliseconds()/1000.0f);
			startTime.Reset();
		}
		_afterUpdate();
		_render();
		_events();
		_destroy();
	}
	_end();
}
void State::addCreation(GAME_OBJECTS type, b2Vec2& position) {
	_pendingOnCreate.push_back(new newInstance(type, position));
}

GameObject* State::create(GAME_OBJECTS type, b2Vec2& position) {
	GameObject* gameObject = nullptr;
	switch (type)
	{
	case GAME_OBJECTS::award:
		gameObject = new MultiBallAward(position.x, position.y, 40, 10, 10, _game->getTextures()[REWARD1]);
		dynamic_cast<RigidBody*>(gameObject)->setVelocity(b2Vec2{ 0,500.0f });
		add(*gameObject);
		break;
	case GAME_OBJECTS::ball:
		gameObject = new Ball(position.x, position.y, 5, _game->getTextures()[BALL]);
		add(*gameObject);
		dynamic_cast<RigidBody*>(gameObject)->ApplyLinearImpulseToCenter(b2Vec2{ 0.0f, 500.0f });
		break;
	case GAME_OBJECTS::block:
		gameObject = new Block(position.x, position.y, 40, 30, 1, _game->getTextures()[BRICKS]);
		add(*gameObject);
		break;
	case GAME_OBJECTS::paddle:
		gameObject = new Paddle(position.x, position.y, 100, 5, 400, 400, 2000.f, _game->getTextures()[PADDLE]);
		add(*gameObject);
		break;
	default:
		break;
	}
	return gameObject;
}

void State::add(GameObject& gameObject) {
	_gameObjects.push_front(&gameObject);
	gameObject.setId(_gameObjects.begin());
}

void State::addEvent(function<void()> callback) {
	_pendingEvents.push(callback);
}

float32 State::getTime() const {
	return _stateTime->getSeconds();
}
