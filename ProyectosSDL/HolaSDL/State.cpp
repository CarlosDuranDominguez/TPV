#include "State.h"
#include "ArkanoidSettings.h"
#include "Ball.h"
#include "Block.h"
#include "Button.h"
#include "CollisionLogic.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "MultiBallAward.h"
#include "Paddle.h"

State::State()
    : listenerLogic_(nullptr),
      world_(nullptr),
      stateTime_(nullptr),
      game_(nullptr) {}

// Constructor
State::State(Game *game, SDL_Renderer *renderer)
    : renderer_(renderer), stateTime_(new ArkanoidTimer()), game_(game) {
  world_ = new b2World(b2Vec2(0.0f, 0.0f));
  listenerLogic_ = new CollisionLogic();
  world_->SetContactListener(listenerLogic_);
}

// Destructor
State::~State() {
  destroy();
  for (auto gameObject : gameObjects_) {
    delete gameObject;
  }
  gameObjects_.clear();
  delete stateTime_;
  delete world_;
  delete listenerLogic_;
}

// The current state for the game
State *State::current_ = nullptr;

// Defines the destroy behaviour for this state
void State::destroy(GameObject *gameObject) {
  // For each element pending to destroy, check if it was already pending to be
  // destroyed
  for (auto &it : pendingOnDestroy_) {
    // If it was already pending to be destroyed, skip
    if (it == gameObject) return;
  }

  // Add the id to the pending on destroy list
  pendingOnDestroy_.push_back(gameObject);
}

// Pushes a new instance for creation for the task queue
void State::addCreation(GameObjects type, b2Vec2 &position) {
  pendingOnCreate_.push_back(new NewInstance(type, position));
}

// Creates a game object from the task queue
GameObject *State::create(const GameObjects type, b2Vec2 &position) {
  GameObject *gameObject = nullptr;
  switch (type) {
    case kAward:
      gameObject = new MultiBallAward(
          position.x, position.y, ArkanoidSettings::rewardWidth_,
          ArkanoidSettings::rewardHeight_, ArkanoidSettings::rewardSpeed_,
          ArkanoidSettings::rewardFramerate_,
          Game::current_->getTextures()[REWARD6]);
      dynamic_cast<RigidBody *>(gameObject)->setVelocity(b2Vec2{0, 500.0f});
      add(*gameObject);
      break;
    case kBall:
      gameObject =
          new Ball(position.x, position.y, ArkanoidSettings::ballRadius_,
                   ArkanoidSettings::ballSpeed_, game_->getTextures()[BALL]);
      add(*gameObject);
      dynamic_cast<RigidBody *>(gameObject)
          ->applyLinearImpulseToCenter(
              b2Vec2{0.0f, ArkanoidSettings::ballSpeed_});
      Game::getGameManager()->addBalls(1);
      break;
    case kBlock:
      gameObject =
          new Block(position.x, position.y, ArkanoidSettings::blockWidth_,
                    ArkanoidSettings::blockHeight_, rand() % 6,
                    game_->getTextures()[BRICKS]);
      add(*gameObject);
      Game::getGameManager()->addBlock();
      break;
    case kPaddle:
      gameObject = new Paddle(
          position.x, position.y, ArkanoidSettings::paddleWidth_,
          ArkanoidSettings::paddleHeight_,
          ArkanoidSettings::sceneUpperLeftCorner_.x +
              ArkanoidSettings::sceneWidth_ / 2.0f,
          ArkanoidSettings::sceneWidth_ / 2.0f, ArkanoidSettings::paddleSpeed_,
          NONE, game_->getTextures()[PADDLE]);
      add(*gameObject);
      break;
    default:
      break;
  }
  return gameObject;
}

// Adds a game object to the game objects list and sets its id
void State::add(GameObject &gameObject) {
  gameObjects_.push_front(&gameObject);
}

// Adds an event to the task queue
void State::addEvent(const function<void()> &callback) {
  pendingEvents_.push(callback);
}

// Gets the current time of game in seconds
float32 State::getTime() const { return float32(stateTime_->getSeconds()); }

State::NewInstance::NewInstance(const GameObjects type, b2Vec2 &position)
    : type_(type), position_(position) {}  /// Protected
void State::_end() {}  // Defines the behaviour for the creation

void State::end() { exit_ = true; }

void State::reset() {}

void State::init() {
  current_ = this;
  stateTime_->reset();
  exit_ = false;
}

void State::create() {
  for (auto instance : pendingOnCreate_) {
    create(instance->type_, instance->position_);
    delete instance;
  }
  pendingOnCreate_.clear();
}

// Defines the behaviour for the render
void State::render() const {
  // Clear the screen
  SDL_RenderClear(renderer_);

  // Render each game object
  for (auto gameObject : gameObjects_) gameObject->render();

  // Render the new frame
  SDL_RenderPresent(renderer_);
}

// Defines the behaviour for the updates
void State::update() {
  // Update each game object
  for (auto it = gameObjects_.begin(); !exit_ && it != gameObjects_.end();) {
    auto next = it;
    ++next;
    (*it)->update();
    it = next;
  }
}

// Defines the behaviour for the event handler
void State::handleEvents() {
  // Listen to SDL events
  SDL_Event event;
  while (!exit_ && SDL_PollEvent(&event)) {
    for (auto it = gameObjects_.begin(); !exit_ && it != gameObjects_.end();) {
      auto next = it;
      ++next;
      (*it)->handleEvents(event);
      it = next;
    }

    // If the event type is quit, change state to GAMEOVER for cleanup
    if (event.type == SDL_QUIT) {
      addEvent([this]() { game_->flushStates(); });
    }
  }
}

// Defines the behaviour for the fixed update
void State::fixUpdate(const float32 time) const {
  // Advance the world's physics by the time step, running
  // 8 velocity iterations and 3 position iterations
  world_->Step(time, 8, 3);
}

// Defines the behaviour for the after update
void State::afterUpdate() {
  // For each game object, run the after update handler
  for (auto gameObject : gameObjects_) gameObject->afterUpdate();
}

// Defines the behaviour for the events
void State::events() {
  // Call each event callback from the stack
  while (!exit_ && !pendingEvents_.empty()) {
    auto cb = pendingEvents_.top();
    pendingEvents_.pop();
    cb();
  }
}

// Defines the behaviour for the destroy
void State::destroy() {
  for (auto gameObject : pendingOnDestroy_) {
    // If the gameObject was already deleted from memory,
    // skip this search
    if (gameObject == nullptr) continue;

    auto it = gameObjects_.begin();
    while (it != gameObjects_.end()) {
      if (*it == gameObject) {
        gameObjects_.erase(it);
        delete gameObject;
        break;
      }
      ++it;
    }
  }

  pendingOnDestroy_.clear();
}

bool State::finished() const { return exit_; }
