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

/// Public
/// Constructor
GameState::GameState(Game *game, SDL_Renderer *renderer)
    : State(game, renderer){};

void GameState::reset()
{
  _pendingEvents.push([this]() { _reset(); });
}

void GameState::_reset()
{

  for (auto gameObject : _gameObjects)
  {
    if (dynamic_cast<Ball *>(gameObject) || dynamic_cast<Paddle *>(gameObject))
      gameObject->destroy();
  }
  _paddle = new Paddle(ArkanoidSettings::sceneUpperLeftCorner.x + ArkanoidSettings::sceneWidth / 2.0f,
                       ArkanoidSettings::sceneUpperLeftCorner.y + ArkanoidSettings::wallWidth * 3.0f / 2.0f + ArkanoidSettings::sceneHeight / 20.0f + ArkanoidSettings::wallHeight,
                       ArkanoidSettings::paddleWidth,
                       ArkanoidSettings::paddleHeight,
                       ArkanoidSettings::sceneUpperLeftCorner.x + ArkanoidSettings::sceneWidth / 2.0f,
                       ArkanoidSettings::sceneWidth / 2.0f,
                       ArkanoidSettings::paddleSpeed,
                       _game->getTextures()[PADDLE]);
  add(*_paddle);

  Ball *ball = new Ball(ArkanoidSettings::sceneUpperLeftCorner.x + ArkanoidSettings::sceneWidth / 2.0f,
                        ArkanoidSettings::sceneUpperLeftCorner.y + ArkanoidSettings::wallWidth * 3.0f / 2.0f + ArkanoidSettings::sceneHeight / 20.0f + ArkanoidSettings::wallHeight - ArkanoidSettings::ballRadius * 2.0f,
                        ArkanoidSettings::ballRadius, ArkanoidSettings::ballSpeed, _game->getTextures()[BALL]);
  add(*ball);
  Game::gameManager()->setBalls(1);
  _stateTime->reset();
}

void GameState::init()
{
  State::init();
  Game::setWorld(*_world);

  GameObject *gameObject = new Timer(ArkanoidSettings::sceneUpperLeftCorner.x, ArkanoidSettings::sceneUpperLeftCorner.y,
                                     ArkanoidSettings::sceneWidth / 2.0f, ArkanoidSettings::sceneHeight / 20.0f, WHITE, _game->getFonts()[MEDIUMFONT]);
  add(*gameObject);

  gameObject = new ScoreMarker(ArkanoidSettings::sceneUpperLeftCorner.x + ArkanoidSettings::sceneWidth / 2.0f, ArkanoidSettings::sceneUpperLeftCorner.y,
                               ArkanoidSettings::sceneWidth / 2.0f, ArkanoidSettings::sceneHeight / 20.0f, WHITE, _game->getFonts()[MEDIUMFONT]);
  add(*gameObject);

  gameObject = new LiveMarker(ArkanoidSettings::sceneUpperLeftCorner.x, ArkanoidSettings::sceneUpperLeftCorner.y + ArkanoidSettings::sceneHeight * 19.0f / 20.0f,
                              ArkanoidSettings::sceneHeight / 20.0f, ArkanoidSettings::sceneHeight / 20.0f, _game->getTextures()[LIFE]);
  add(*gameObject);

  gameObject = new Button(_game->getFonts()[MEDIUMFONT], 400, 400, 100, 100, WHITE, GREY, "S", [this]() {
    auto call = [this]() { saveLevel("../saves/level.save"); };
    addEvent(call);
  });
  add(*gameObject);
  if (Game::gameManager()->level() > 0)
  {
    int lives = Game::gameManager()->getLives();
    loadLevel("../levels/level" + to_string(Game::gameManager()->level()) + ".ark");
    if (Game::gameManager()->level() == 1)
    {
      Game::gameManager()->setLives(ArkanoidSettings::initialLives);
    }
    else
    {
      Game::gameManager()->setLives(lives);
    }
  }
  else
  {
    try
    {
      loadLevel("../saves/level.save");
    }
    catch (exception e)
    {
      loadLevel("../levels/level01.ark");
      Game::gameManager()->setLives(ArkanoidSettings::initialLives);
    }
  }
}

void GameState::loadLevel(const string &path)
{
  ifstream file;
  file.open(path, std::ifstream::out);
  if (file.fail())
  {
    throw(FileNotFoundError)(path);
  }

  if (!file.eof())
  {
    uint level;
    file >> level;
    if (level == 1)
      Game::gameManager()->newGame();
    else
      Game::gameManager()->reset();
    Game::gameManager()->setLevel(level);
  }

  if (!file.eof() && !file.fail())
  {
    int lives;
    file >> lives;
    Game::gameManager()->setLives(lives);
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

  while (!file.eof() && !file.fail())
  {
    string name;
    file >> name;
    if (name == "")
      continue;
    GameObject *gameObject = nullptr;
    if (name == "Wall")
    {
      gameObject = new Wall();
    }
    else if (name == "Paddle")
    {
      _paddle = new Paddle();
      gameObject = _paddle;
    }
    else if (name == "Enemy")
    {
      gameObject = new Enemy();
    }
    else if (name == "DeadZone")
    {
      gameObject = new DeadZone();
    }
    else if (name == "Block")
    {
      gameObject = new Block();
      Game::gameManager()->addBlock();
    }
    else if (name == "Ball")
    {
      gameObject = new Ball();
      Game::gameManager()->addBalls(1);
    }
    else if (name == "Award")
    {
      gameObject = new Award();
    }
    else if (name == "EnlargenAward")
    {
      gameObject = new EnlargenAward();
    }
    else if (name == "LaserAward")
    {
      gameObject = new LaserAward();
    }
    else if (name == "MultiBallAward")
    {
      gameObject = new MultiBallAward();
    }
    else if (name == "NextLevelAward")
    {
      gameObject = new NextLevelAward();
    }
    else if (name == "ShortenAward")
    {
      gameObject = new ShortenAward();
    }
    else if (name == "StickyAward")
    {
      gameObject = new StickyAward();
    }
    else
    {
      throw(FileFormatError)(path);
    }
    file >> *gameObject;
    add(*gameObject);
  }
  file.close();
}

void GameState::saveLevel(const string &path)
{
  ofstream file;
  file.open(path, std::ofstream::out);
  if (file.fail())
  {
    throw new FileNotFoundError(path);
  }
  file << Game::gameManager()->level() << ' ' << Game::gameManager()->getLives() << ' ' << Game::gameManager()->getScore() << ' ' << _stateTime->getSeconds() << '\n';
  for (auto gameObject : _gameObjects)
  {
    if (dynamic_cast<ArkanoidObject *>(gameObject))
      file << *gameObject << "\n";
  }
  file.close();
}

void GameState::_destroyAll()
{
  for (auto gameobject : _gameObjects)
  {
    delete gameobject;
  }
  _gameObjects.clear();
}

void GameState::_end()
{
  _destroyAll();
}
