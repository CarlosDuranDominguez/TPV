#include "GameState.h"
#include "Block.h"
#include "Wall.h"
#include "Ball.h"
#include "Game.h"
#include "Paddle.h"
#include "DeadZone.h"
#include "Enemy.h"
#include "Text.h"
#include "Timer.h"
#include "EnlargenAward.h"
#include "LaserAward.h"
#include "MultiBallAward.h"
#include "NextLevelAward.h"
#include "ShortenAward.h"
#include "StickyAward.h"
#include "Scoremarker.h"
#include "LiveMarker.h"
#include "Button.h"
#include <iostream>
#include <algorithm>
#include <fstream>  
#include "FileNotFoundError.h"
#include "FileFormatError.h"

GameState::GameState(Game *game, SDL_Renderer *renderer) 
	:State(game, renderer),_isNewGame(false) {
};

GameState::~GameState() {
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
	_stateTime->reset();
}

void GameState::init()
{
	State::init();
	Game::setWorld(*_world);
	Game::gameManager()->newGame();
	Game::gameManager()->addLives(3);

	GameObject *gameObject = new Timer(ArkanoidSettings::sceneUpperLeftCorner.x, ArkanoidSettings::sceneUpperLeftCorner.y,
		ArkanoidSettings::sceneWidth/2.0f, ArkanoidSettings::sceneHeight/20.0f, WHITE, _game->getFonts()[MEDIUMFONT]);
	add(*gameObject); 

	gameObject = new ScoreMarker(ArkanoidSettings::sceneUpperLeftCorner.x + ArkanoidSettings::sceneWidth / 2.0f, ArkanoidSettings::sceneUpperLeftCorner.y,
		ArkanoidSettings::sceneWidth / 2.0f, ArkanoidSettings::sceneHeight / 20.0f, WHITE, _game->getFonts()[MEDIUMFONT]);
	add(*gameObject);

	gameObject = new LiveMarker(ArkanoidSettings::sceneUpperLeftCorner.x, ArkanoidSettings::sceneUpperLeftCorner.y + ArkanoidSettings::sceneHeight*19.0f/20.0f,
		ArkanoidSettings::sceneHeight / 20.0f, ArkanoidSettings::sceneHeight / 20.0f, _game->getTextures()[LIFE]);
	add(*gameObject);

	gameObject = new Button(_game->getFonts()[MEDIUMFONT], 400, 400, 100, 100, WHITE, GREY, "S", [this]() {
	  auto call = [this]() { saveLevel("../saves/level.save"); };
		addEvent(call);
	});
	add(*gameObject);

	if (_isNewGame) {
		loadLevel("../levels/level01.ark");
	}
	else {
		try {
			loadLevel("../saves/level.save");
		}
		catch(exception e) {
			loadLevel("../levels/level01.ark");
		}
	}
	_isNewGame = false;
	/*
	gameObject = new Wall(ArkanoidSettings::sceneUpperLeftCorner.x +ArkanoidSettings::wallWidth/2.0f, 
		ArkanoidSettings::sceneUpperLeftCorner.y + ArkanoidSettings::wallWidth * 2.0f + ArkanoidSettings::wallHeight / 2.0f + ArkanoidSettings::sceneHeight / 20.0f,
		ArkanoidSettings::wallWidth, 
		ArkanoidSettings::wallHeight, 
		_game->getTextures()[SIDE]);
	add(*gameObject);

	gameObject = new Wall(ArkanoidSettings::sceneUpperLeftCorner.x + ArkanoidSettings::sceneWidth - ArkanoidSettings::wallWidth / 2.0f,
		ArkanoidSettings::sceneUpperLeftCorner.y + ArkanoidSettings::wallWidth * 2.0f + ArkanoidSettings::wallHeight / 2.0f + ArkanoidSettings::sceneHeight / 20.0f,
		ArkanoidSettings::wallWidth,
		ArkanoidSettings::wallHeight, 
		_game->getTextures()[SIDE]);
	add(*gameObject);
	gameObject = new Wall(ArkanoidSettings::sceneUpperLeftCorner.x+ArkanoidSettings::sceneWidth/2.0f,
		ArkanoidSettings::sceneUpperLeftCorner.y + ArkanoidSettings::wallWidth * 3.0f / 2.0f  + ArkanoidSettings::sceneHeight / 20.0f, 
		ArkanoidSettings::wallHeight,
		ArkanoidSettings::wallWidth, _game->getTextures()[TOPSIDE]);
	add(*gameObject);

	gameObject = new Block(ArkanoidSettings::sceneUpperLeftCorner.x + ArkanoidSettings::wallWidth+ArkanoidSettings::blockWidth/2.0f, 
		ArkanoidSettings::sceneUpperLeftCorner.y + ArkanoidSettings::wallWidth * 2.0f + ArkanoidSettings::sceneHeight / 20.0f +ArkanoidSettings::blockHeight/2.0f,
		ArkanoidSettings::blockWidth, 
		ArkanoidSettings::blockHeight,
		1,_game->getTextures()[BRICKS]);
	add(*gameObject);
	
	

	gameObject = new Ball(ArkanoidSettings::sceneUpperLeftCorner.x + ArkanoidSettings::sceneWidth / 2.0f + ArkanoidSettings::ballRadius*2.0f,
		ArkanoidSettings::sceneUpperLeftCorner.y + ArkanoidSettings::wallWidth * 3.0f / 2.0f + ArkanoidSettings::sceneHeight / 20.0f + ArkanoidSettings::wallHeight - ArkanoidSettings::ballRadius*2.0f,
		10, _game->getTextures()[BALL]);
	add(*gameObject);
	dynamic_cast<RigidBody*>(gameObject)->ApplyLinearImpulseToCenter(b2Vec2{ 0,10000 });
	_balls.push_back(gameObject->getId());

	gameObject = new Paddle(ArkanoidSettings::sceneUpperLeftCorner.x + ArkanoidSettings::sceneWidth / 2.0f,
		ArkanoidSettings::sceneUpperLeftCorner.y + ArkanoidSettings::wallWidth * 3.0f / 2.0f + ArkanoidSettings::sceneHeight / 20.0f +ArkanoidSettings::wallHeight,
		ArkanoidSettings::paddleWidth, 
		ArkanoidSettings::paddleHeight,
		ArkanoidSettings::sceneUpperLeftCorner.x + ArkanoidSettings::sceneWidth / 2.0f,
		(ArkanoidSettings::sceneWidth)/2 - ArkanoidSettings::wallWidth,
		ArkanoidSettings::paddleSpeed, _game->getTextures()[PADDLE]);
	add(*gameObject);
	_paddles.push_back(gameObject->getId());

	gameObject = new DeadZone(ArkanoidSettings::sceneUpperLeftCorner.x + ArkanoidSettings::sceneWidth / 2.0f, 
		ArkanoidSettings::sceneUpperLeftCorner.y + ArkanoidSettings::wallWidth * 3.0f / 2.0f + ArkanoidSettings::sceneHeight / 20.0f + ArkanoidSettings::wallHeight +ArkanoidSettings::paddleHeight,
		ArkanoidSettings::sceneWidth, 
		10.0f);
	add(*gameObject);

	gameObject = new Enemy(600, 50, 40, 40, 500, 1.0f, 0.2f, 10.0f,_game->getTextures()[ENEMY1]);
	add(*gameObject);
	*/

	
	_stateTime->reset();
	_isReseting = false;
}

void GameState::loadLevel(const string& path) {
	ifstream file;
	file.open(path, std::ifstream::out);
	if (file.fail()) {
		throw (FileNotFoundError)(path);
	}

	if (!file.eof())
	{
		int level;
		file >> level;
		Game::gameManager()->setLevel(level);
	}

	if (!file.eof() && !file.fail())
	{
		int score;
		file >> score;
		Game::gameManager()->setScore(score);
	}

	if (!file.eof() && !file.fail())
	{
		double time;
		file >> time;
		_stateTime->delay(time);
	}

	GameObject* gameObject;
	while (!file.eof() && !file.fail()) {
		string name;
		file >> name;
		GameObject* gameObject = nullptr;
		if (name == "Wall") { gameObject = new Wall(); }
		else if (name == "Paddle") { gameObject = new Paddle(); }
		else if (name == "Enemy") { gameObject = new Enemy(); }
		else if (name == "DeadZone") { gameObject = new DeadZone(); }
		else if (name == "Block") { gameObject = new Block(); Game::gameManager()->addBlock(); }
		else if (name == "Ball") { gameObject = new Ball(); Game::gameManager()->addBalls(1); }
		else if (name == "Award") { gameObject = new Award(); }
		else if (name == "EnlargenAward") { gameObject = new EnlargenAward(); }
		else if (name == "LaserAward") { gameObject = new LaserAward(); }
		else if (name == "MultiBallAward") { gameObject = new MultiBallAward();	}
		else if (name == "NextLevelAward") { gameObject = new NextLevelAward();	}
		else if (name == "ShortenAward") { gameObject = new ShortenAward();	}
		else if (name == "StickyAward") { gameObject = new StickyAward(); }
		else { 
			throw (FileFormatError)(path); 
		}
		file >> *gameObject;
		add(*gameObject);
	}
}

void GameState::saveLevel(const string& path) {
	ofstream file;
	file.open(path, std::ofstream::in);
	if (file.fail()) {
		throw new FileNotFoundError(path);
	}
	file << Game::gameManager()->level()<<' '<<Game::gameManager()->getScore() << ' ' << _stateTime->getSeconds() << '\n';
	for (auto gameObject : _gameObjects) {
		if(dynamic_cast<ArkanoidObject*>(gameObject))
			file << *gameObject << "\n";
	}
}

void GameState::_end(){
	if (_isReseting) {
		_reset();
		_exit = false;
		run();
	}
	
}

void GameState::_destroy() {
	State::_destroy();
}