#include "GameState.h"
#include "Block.h"
#include "Wall.h"
#include "Ball.h"
#include "Game.h"
#include "Paddle.h"
#include "DeadZone.h"
#include "Enemy.h"
#include <algorithm>

GameState::GameState(Game *game, SDL_Renderer *renderer) 
	:State(game, renderer), timer(new b2Timer()) {
};

GameState::~GameState() {
	delete timer; 
}

void GameState::reset() {
	_isReseting = true;
	_exit = true;
}

void GameState::_reset() {

	for (auto paddle : _paddles) {
		destroy(paddle);
	}

	_paddles.clear();
	addCreation(GAME_OBJECTS::ball, b2Vec2{ 100, 100 });
	addCreation(GAME_OBJECTS::paddle, b2Vec2{ 200,400 });
	_isReseting = false;
	timer->Reset();
}

void GameState::init()
{
	State::init();
	Game::setWorld(*_world);
	Game::gameManager()->newGame();
	Game::gameManager()->addLives(3);

	GameObject *gameObject = new Block(50,50, 40, 30,1,_game->getTextures()[BRICKS]);
	add(*gameObject);
	
	gameObject = new Wall(10, 600, 20, 1200, _game->getTextures()[SIDE]);
	add(*gameObject);
	gameObject = new Wall(600, 10, 1200, 20, _game->getTextures()[TOPSIDE]);
	add(*gameObject);

	gameObject = new Ball(100,100,5, _game->getTextures()[BALL]);
	add(*gameObject);
	dynamic_cast<RigidBody*>(gameObject)->ApplyLinearImpulseToCenter(b2Vec2{ 0,500 });
	_balls.push_back(gameObject->getId());

	gameObject = new Paddle(200, 400, 100, 5, 400,400,2000.f, _game->getTextures()[PADDLE]);
	add(*gameObject);
	_paddles.push_back(gameObject->getId());

	gameObject = new DeadZone(200, 600, 1000, 5);
	add(*gameObject);

	gameObject = new Enemy(600, 50, 40, 40, 500, 1.0f, 0.2f, _game->getTextures()[BALL]);
	add(*gameObject);

	timer->Reset();
	_isReseting = false;
}
void GameState::_end(){
	if (_isReseting) {
		_reset();
		_exit = false;
		run();
	}
	
}

float32 GameState::getTime() {
	return timer->GetMilliseconds();
}

void GameState::_destroy() {
	State::_destroy();
}