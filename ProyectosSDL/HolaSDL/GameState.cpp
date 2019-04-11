#include "GameState.h"
#include <fstream>
#include "ArkanoidSettings.h"
#include "Ball.h"
#include "Block.h"
#include "Bullet.h"
#include "Button.h"
#include "DeadZone.h"
#include "Enemy.h"
#include "EnlargenAward.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"
#include "Game.h"
#include "LaserAward.h"
#include "LiveMarker.h"
#include "MultiBallAward.h"
#include "NextLevelAward.h"
#include "Paddle.h"
#include "Scoremarker.h"
#include "ShortenAward.h"
#include "StickyAward.h"
#include "Timer.h"
#include "Wall.h"

/// Public Virtual
// Adds a pending event to reset this state in the next tick
void GameState::reset() {
  pendingEvents_.push([this]() { _reset(); });
}

/// Public Virtual
// Initializes this state
void GameState::init() {
  State::init();
  Game::setWorld(*world_);

  // Add the game's timer
  add(*new Timer(ArkanoidSettings::sceneUpperLeftCorner_.x,
                 ArkanoidSettings::sceneUpperLeftCorner_.y,
                 ArkanoidSettings::sceneWidth_ / 2.0f,
                 ArkanoidSettings::sceneHeight_ / 20.0f, kWhite,
                 game_->getFonts()[MEDIUM_FONT]));

  // Add the game's score marker
  add(*new ScoreMarker(ArkanoidSettings::sceneUpperLeftCorner_.x +
                           ArkanoidSettings::sceneWidth_ / 2.0f,
                       ArkanoidSettings::sceneUpperLeftCorner_.y,
                       ArkanoidSettings::sceneWidth_ / 2.0f,
                       ArkanoidSettings::sceneHeight_ / 20.0f, kWhite,
                       game_->getFonts()[MEDIUM_FONT]));

  // Add the game's live marker
  add(*new LiveMarker(ArkanoidSettings::sceneUpperLeftCorner_.x,
                      ArkanoidSettings::sceneUpperLeftCorner_.y +
                          ArkanoidSettings::sceneHeight_ * 19.0f / 20.0f,
                      ArkanoidSettings::sceneHeight_ / 20.0f,
                      ArkanoidSettings::sceneHeight_ / 20.0f,
                      game_->getTextures()[LIFE]));

  // Adds the save button
  add(*new Button(game_->getFonts()[MEDIUM_FONT], 400, 400, 100, 100, kWhite,
                  kGrey, "S", [this]() {
                    auto call = [this]() { saveLevel("../saves/level.save"); };
                    addEvent(call);
                  }));
  auto gameManager = Game::getGameManager();
  // If the game's level is above 0, try to load the level
  if (gameManager->getLevel() > 0) {
    // Get the amount of lives and load the level
    int lives = gameManager->getLives();
    int score = gameManager->getScore();
    int totalTime = gameManager->getTotalTime();
    loadLevel("../levels/level" +
              to_string(Game::getGameManager()->getLevel()) + ".ark");
    // If the current level is the first one, give three lives
    if (gameManager->getLevel() == 1) {
      gameManager->setLives(ArkanoidSettings::initialLives_);
    } else {
      gameManager->setLives(lives);
      gameManager->setScore(score);
      gameManager->setTotalTime(static_cast<float32>(totalTime));
    }
  } else {
    // Try to load the latest save, else load the first level
    try {
      loadLevel("../saves/level.save");
    } catch (exception e) {
      loadLevel("../levels/level1.ark");
      Game::getGameManager()->setLives(ArkanoidSettings::initialLives_);
    }
  }
}

/// Public
// Load a level into this game state
void GameState::loadLevel(const string &path) {
  // Create an input file stream to the path and open it
  ifstream file;
  file.open(path, std::ifstream::out);

  // If the file failed to load, throw FileNotFoundError
  if (!file)
    // If the name could not be recognized, throw an error
    throw(FileFormatError)(path);

  Uint32 level, timer;
  int lives, score;

  // Read and set the level
  file >> level;
  if (level == 1)
    Game::getGameManager()->newGame();
  else
    Game::getGameManager()->reset();
  Game::getGameManager()->setLevel(level);

  // If not good (!eof && !fail && !bad), stop loading
  if (!file.good())
    // If the name could not be recognized, throw an error
    throw(FileFormatError)(path);

  // Read and set the amount of lives
  file >> lives;
  Game::getGameManager()->setLives(lives);

  // If not good (!eof && !fail && !bad), stop loading
  if (!file.good())
    // If the name could not be recognized, throw an error
    throw(FileFormatError)(path);

  // Read and set the amount of points
  file >> score;
  Game::getGameManager()->setScore(score);

  // If not good (!eof && !fail && !bad), stop loading
  if (!file.good())
    // If the name could not be recognized, throw an error
    throw(FileFormatError)(path);

  // Read and set the timer second delay
  file >> timer;
  stateTime_->delay(timer);

  // If not good (!eof && !fail && !bad), stop loading
  if (!file.good())
    // If the name could not be recognized, throw an error
    throw(FileFormatError)(path);

  // Read and set the timer second delay
  file >> timer;
  Game::getGameManager()->setTotalTime(static_cast<float32>(timer));

  // While good (!eof && !fail && !bad), load lines
  while (file.good()) {
    // Read the name
    string name;
    file >> name;

    // If the name is an empty string (empty line), skip to the next loop
    if (name == "") continue;

    // Create a GameObject pointer and identify the kind of object
    GameObject *gameObject;
    if (name == "Wall") {
      gameObject = new Wall();
    } else if (name == "Paddle") {
      paddle_ = new Paddle();
      gameObject = paddle_;
    } else if (name == "Enemy") {
      gameObject = new Enemy();
    } else if (name == "DeadZone") {
      gameObject = new DeadZone();
    } else if (name == "Block") {
      gameObject = new Block();
      Game::getGameManager()->addBlock();
    } else if (name == "Ball") {
      gameObject = new Ball();
      Game::getGameManager()->addBalls(1);
    } else if (name == "Award") {
      gameObject = new Award();
    } else if (name == "EnlargenAward") {
      gameObject = new EnlargenAward();
    } else if (name == "LaserAward") {
      gameObject = new LaserAward();
    } else if (name == "MultiBallAward") {
      gameObject = new MultiBallAward();
    } else if (name == "NextLevelAward") {
      gameObject = new NextLevelAward();
    } else if (name == "ShortenAward") {
      gameObject = new ShortenAward();
    } else if (name == "StickyAward") {
      gameObject = new StickyAward();
    } else if (name == "Bullet") {
      gameObject = new Bullet();
    } else {
      // If the name could not be recognized, throw an error
      throw(FileFormatError)(path);
    }

    // Serialize the game object and add it to the state
    file >> *gameObject;
    add(*gameObject);
  }

  // Close the input file stream
  file.close();
}

/// Public
// Save the level to a save file
void GameState::saveLevel(const string &path) {
  // Create and open a output file stream to a path
  ofstream file;
  file.open(path, std::ofstream::out);

  // If the file failed to load, throw FileNotFoundError
  if (!file) throw new FileNotFoundError(path);

  // Save the level, lives, score, and seconds
  file << Game::getGameManager()->getLevel() << " "
       << Game::getGameManager()->getLives() << " "
       << Game::getGameManager()->getScore() << " " << stateTime_->getSeconds()
       << "\n";

  // Save each one of the objects from this state
  for (auto gameObject : gameObjects_) {
    if (dynamic_cast<ArkanoidObject *>(gameObject)) file << *gameObject << "\n";
  }

  // Close the output file stream
  file.close();
}

/// Protected
// Sets the behaviour for the _end method
void GameState::_end() { _destroyAll(); }

/// Protected
// Sets the reset behaviour for this state
void GameState::_reset() {
  // Destroy all the balls
  for (auto gameObject : gameObjects_) {
    if (dynamic_cast<Ball *>(gameObject)) gameObject->destroy();
  }

  // Destroy the paddle
  paddle_->destroy();

  // Creates the paddle in the middle of the scene
  paddle_ = new Paddle(
      ArkanoidSettings::sceneUpperLeftCorner_.x +
          ArkanoidSettings::sceneWidth_ / 2.0f,
      ArkanoidSettings::sceneUpperLeftCorner_.y +
          ArkanoidSettings::wallWidth_ * 3.0f / 2.0f +
          ArkanoidSettings::sceneHeight_ / 20.0f +
          ArkanoidSettings::wallHeight_,
      ArkanoidSettings::paddleWidth_, ArkanoidSettings::paddleHeight_,
      ArkanoidSettings::sceneUpperLeftCorner_.x +
          ArkanoidSettings::sceneWidth_ / 2.0f,
      ArkanoidSettings::sceneWidth_ / 2.0f - ArkanoidSettings::wallWidth_,
      ArkanoidSettings::paddleSpeed_, BEGIN, game_->getTextures()[PADDLE]);
  add(*paddle_);

  // Creates the ball on top of the paddle
  Ball *ball = new Ball(
      ArkanoidSettings::sceneUpperLeftCorner_.x +
          ArkanoidSettings::sceneWidth_ / 2.0f +
          ArkanoidSettings::paddleWidth_ / 4.0f,
      ArkanoidSettings::sceneUpperLeftCorner_.y +
          ArkanoidSettings::wallWidth_ * 3.0f / 2.0f +
          ArkanoidSettings::sceneHeight_ / 20.0f +
          ArkanoidSettings::wallHeight_ - ArkanoidSettings::ballRadius_ * 2.0f -
          ArkanoidSettings::paddleHeight_ / 2.0f,
      ArkanoidSettings::ballRadius_, ArkanoidSettings::ballSpeed_,
      game_->getTextures()[BALL]);
  ball->setVelocity(b2Vec2(0.0f, 1.0f));
  add(*ball);

  // Sets the initial ball for the game manager
  Game::getGameManager()->setBalls(1);

  // Reset the timer
  stateTime_->reset();
}

/// Private
// Sets the behaviour to destroy all objects
void GameState::_destroyAll() {
  // Delete all game objects
  for (auto gameobject : gameObjects_) delete gameobject;

  // Clear the state
  gameObjects_.clear();
}

GameState::GameState(Game *game, SDL_Renderer *renderer)
    : State(game, renderer) {}

GameState::~GameState() {}

Paddle *GameState::paddle() const { return paddle_; }
