#include "State.h"
#include "ArkanoidSettings.h"
#include "Award.h"
#include "Ball.h"
#include "Block.h"
#include "Button.h"
#include "CollisionLogic.h"
#include "Game.h"
#include "MultiBallAward.h"
#include "Paddle.h"

/// Public
// Constructor
State::State(Game *game, SDL_Renderer *renderer)
    : game_(game), renderer_(renderer), stateTime_(new ArkanoidTimer()) {
  world_ = new b2World(b2Vec2(0.0f, 0.0f));
  listenerLogic_ = new CollisionLogic();
  world_->SetContactListener(listenerLogic_);
}

/// Public
// Destructor
State::~State() {
  for (auto gameObject : gameObjects_) {
    delete gameObject;
  }
  pendingOnDestroy_.clear();
  gameObjects_.clear();
  delete stateTime_;
  delete world_;
  delete listenerLogic_;
}

/// Public Static
// The current state for the game
State *State::current_ = nullptr;

/// Public
// Defines the destroy behaviour for this state
void State::destroy(list<GameObject *>::iterator &gameObjectId) {
  // For each element pending to destroy, check if it was already pending to be
  // destroyed
  for (auto it = pendingOnDestroy_.begin(); it != pendingOnDestroy_.end();
       ++it) {
    // If it was already pending to be destroyed, skip
    if (*it == gameObjectId) return;
  }

  // Add the id to the pending on destroy list
  pendingOnDestroy_.push_back(gameObjectId);
}

/// Public
// Defines the run behaviour for this state
void State::run() {
  // Set the start time, run state's event loop
  b2Timer startTime;

  // The event loop follows this scheme:
  // → Create all pending-to-create game objects
  // → Handle SDL events (provided by SDL's event poll)
  // → Handle updates (updates all game objects of the game)
  // → Handle fixed updates (called every second)
  // → Handle after updates (called after the physics engine has run)
  // → Render all the game objects from the scene
  // → Run all the pending events of this tick from the stack
  // → Destroy all the elements that are pending to destroy
  // Once all tasks are done, exit loop, perform cleanup, and finish
  while (!exit_) {
    create();
    handleEvents();
    update();
    if (startTime.GetMilliseconds() / 1000.0f >=
        1.0f / (ArkanoidSettings::framerate_)) {
      fixUpdate(startTime.GetMilliseconds() / 1000.0f);
      startTime.Reset();
    }
    afterUpdate();
    render();
    events();
    destroy();
  }
  _end();
}

/// Public
// Pushes a new instance for creation for the task queue
void State::addCreation(GameObjects type, b2Vec2 &position) {
  pendingOnCreate_.push_back(new NewInstance(type, position));
}

/// Public
// Creates a game object from the task queue
GameObject *State::create(GameObjects type, b2Vec2 &position) {
  GameObject *gameObject = nullptr;
  switch (type) {
    case GameObjects::kAward:
      gameObject = new MultiBallAward(
          position.x, position.y, ArkanoidSettings::rewardWidth_,
          ArkanoidSettings::rewardHeight_, ArkanoidSettings::rewardSpeed_,
          ArkanoidSettings::rewardFramerate_,
          Game::current_->getTextures()[REWARD6]);
      dynamic_cast<RigidBody *>(gameObject)->setVelocity(b2Vec2{0, 500.0f});
      add(*gameObject);
      break;
    case GameObjects::kBall:
      gameObject =
          new Ball(position.x, position.y, ArkanoidSettings::ballRadius_,
                   ArkanoidSettings::ballSpeed_, game_->getTextures()[BALL]);
      add(*gameObject);
      dynamic_cast<RigidBody *>(gameObject)
          ->applyLinearImpulseToCenter(
              b2Vec2{0.0f, ArkanoidSettings::ballSpeed_});
      Game::getGameManager()->addBalls(1);
      break;
    case GameObjects::kBlock:
      gameObject =
          new Block(position.x, position.y, ArkanoidSettings::blockWidth_,
                    ArkanoidSettings::blockHeight_, rand() % 6,
                    game_->getTextures()[BRICKS]);
      add(*gameObject);
      Game::getGameManager()->addBlock();
      break;
    case GameObjects::kPaddle:
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

/// Public
// Adds a game object to the game objects list and sets its id
void State::add(GameObject &gameObject) {
  gameObjects_.push_front(&gameObject);
  gameObject.setId(gameObjects_.begin());
}

/// Public
// Adds an event to the task queue
void State::addEvent(function<void()> callback) {
  pendingEvents_.push(callback);
}

/// Public
// Gets the current time of game in seconds
float32 State::getTime() const { return (float32)stateTime_->getSeconds(); }

State::NewInstance::NewInstance(GameObjects type, b2Vec2 &position)
    : type_(type), position_(position) {}  /// Protected
void State::_end() {}  // Defines the behaviour for the creation
State::State() {}

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

/// Protected
// Defines the behaviour for the render
void State::render() const {
  // Clear the screen
  SDL_RenderClear(renderer_);

  // Render each game object
  for (auto gameObject : gameObjects_) gameObject->render();

  // Render the new frame
  SDL_RenderPresent(renderer_);
}

/// Protected
// Defines the behaviour for the updates
void State::update() {
  // Update each game object
  for (auto gameObject : gameObjects_) gameObject->update();
}

/// Protected
// Defines the behaviour for the event handler
void State::handleEvents() {
  // Listen to SDL events
  SDL_Event event;
  while (!exit_ && SDL_PollEvent(&event)) {
    // If the event type is quit, change state to GAMEOVER for cleanup
    if (event.type == SDL_QUIT) {
      exit_ = true;
      game_->changeState(States::GAMEOVER);
    }

    // For each game object, run the event handler
    for (auto gameObject : gameObjects_) gameObject->handleEvents(event);
  }
}

/// Protected
// Defines the behaviour for the fixed update
void State::fixUpdate(float32 timeStep) {
  // Advance the world's physics by the time step, running
  // 8 velocity iterations and 3 position iterations
  world_->Step(timeStep, 8, 3);
}

/// Protected
// Defines the behaviour for the after update
void State::afterUpdate() {
  // For each game object, run the after update handler
  for (auto gameObject : gameObjects_) gameObject->afterUpdate();
}

/// Protected
// Defines the behaviour for the events
void State::events() {
  // Call each event callback from the stack
  while (!pendingEvents_.empty()) {
    pendingEvents_.top()();
    pendingEvents_.pop();
  }
}

/// Protected Virtual
// Defines the behaviour for the destroy
void State::destroy() {
  // For each object pending to be destroyed, destroy and erase from the game
  // objects
  for (list<GameObject *>::iterator object : pendingOnDestroy_) {
    if (*object != nullptr) {
      delete *object;
      gameObjects_.erase(object);
    }
  }

  // Clear the queue
  pendingOnDestroy_.clear();
}
