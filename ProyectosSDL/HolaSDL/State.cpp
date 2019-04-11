#include "State.h"
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
    : _game(game), _renderer(renderer), _stateTime(new ArkanoidTimer()) {
  _world = new b2World(b2Vec2(0.0f, 0.0f));
  _listenerLogic = new CollisionLogic();
  _world->SetContactListener(_listenerLogic);
}

/// Public
// Destructor
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

/// Public Static
// The current state for the game
State *State::current = nullptr;

/// Public
// Defines the destroy behaviour for this state
void State::destroy(list<GameObject *>::iterator &gameObjectId) {
  // For each element pending to destroy, check if it was already pending to be
  // destroyed
  for (auto it = _pendingOnDestroy.begin(); it != _pendingOnDestroy.end();
       ++it) {
    // If it was already pending to be destroyed, skip
    if (*it == gameObjectId) return;
  }

  // Add the id to the pending on destroy list
  _pendingOnDestroy.push_back(gameObjectId);
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
  while (!_exit) {
    _create();
    _handleEvents();
    _update();
    if (startTime.GetMilliseconds() / 1000.0f >=
        1.0f / (ArkanoidSettings::framerate)) {
      _fixUpdate(startTime.GetMilliseconds() / 1000.0f);
      startTime.Reset();
    }
    _afterUpdate();
    _render();
    _events();
    _destroy();
  }
  _end();
}

/// Public
// Pushes a new instance for creation for the task queue
void State::addCreation(GAME_OBJECTS type, b2Vec2 &position) {
  _pendingOnCreate.push_back(new newInstance(type, position));
}

/// Public
// Creates a game object from the task queue
GameObject *State::create(GAME_OBJECTS type, b2Vec2 &position) {
  GameObject *gameObject = nullptr;
  switch (type) {
    case GAME_OBJECTS::award:
      gameObject = new MultiBallAward(
          position.x, position.y, ArkanoidSettings::rewardWidth,
          ArkanoidSettings::rewardHeigth, ArkanoidSettings::rewardSpeed,
          ArkanoidSettings::rewardFramerate,
          Game::current->getTextures()[REWARD6]);
      dynamic_cast<RigidBody *>(gameObject)->setVelocity(b2Vec2{0, 500.0f});
      add(*gameObject);
      break;
    case GAME_OBJECTS::ball:
      gameObject =
          new Ball(position.x, position.y, ArkanoidSettings::ballRadius,
                   ArkanoidSettings::ballSpeed, _game->getTextures()[BALL]);
      add(*gameObject);
      dynamic_cast<RigidBody *>(gameObject)
          ->ApplyLinearImpulseToCenter(
              b2Vec2{0.0f, ArkanoidSettings::ballSpeed});
      Game::getGameManager()->addBalls(1);
      break;
    case GAME_OBJECTS::block:
      gameObject =
          new Block(position.x, position.y, ArkanoidSettings::blockWidth,
                    ArkanoidSettings::blockHeight, rand() % 6,
                    _game->getTextures()[BRICKS]);
      add(*gameObject);
      Game::getGameManager()->addBlock();
      break;
    case GAME_OBJECTS::paddle:
      gameObject = new Paddle(
          position.x, position.y, ArkanoidSettings::paddleWidth,
          ArkanoidSettings::paddleHeight,
          ArkanoidSettings::sceneUpperLeftCorner.x +
              ArkanoidSettings::sceneWidth / 2.0f,
          ArkanoidSettings::sceneWidth / 2.0f, ArkanoidSettings::paddleSpeed,
          NONE, _game->getTextures()[PADDLE]);
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
  _gameObjects.push_front(&gameObject);
  gameObject.setId(_gameObjects.begin());
}

/// Public
// Adds an event to the task queue
void State::addEvent(function<void()> callback) {
  _pendingEvents.push(callback);
}

/// Public
// Gets the current time of game in seconds
float32 State::getTime() const { return (float32)_stateTime->getSeconds(); }

/// Protected
// Defines the behaviour for the creation
void State::_create() {
  for (auto instance : _pendingOnCreate) {
    create(instance->type, instance->position);
    delete instance;
  }
  _pendingOnCreate.clear();
}

/// Protected
// Defines the behaviour for the render
void State::_render() const {
  // Clear the screen
  SDL_RenderClear(_renderer);

  // Render each game object
  for (auto gameObject : _gameObjects) gameObject->render();

  // Render the new frame
  SDL_RenderPresent(_renderer);
}

/// Protected
// Defines the behaviour for the updates
void State::_update() {
  // Update each game object
  for (auto gameObject : _gameObjects) gameObject->update();
}

/// Protected
// Defines the behaviour for the event handler
void State::_handleEvents() {
  // Listen to SDL events
  SDL_Event event;
  while (!_exit && SDL_PollEvent(&event)) {
    // If the event type is quit, change state to GAMEOVER for cleanup
    if (event.type == SDL_QUIT) {
      _exit = true;
      _game->changeState(States::GAMEOVER);
    }

    // For each game object, run the event handler
    for (auto gameObject : _gameObjects) gameObject->handleEvents(event);
  }
}

/// Protected
// Defines the behaviour for the fixed update
void State::_fixUpdate(float32 timeStep) {
  // Advance the world's physics by the time step, running
  // 8 velocity iterations and 3 position iterations
  _world->Step(timeStep, 8, 3);
}

/// Protected
// Defines the behaviour for the after update
void State::_afterUpdate() {
  // For each game object, run the after update handler
  for (auto gameObject : _gameObjects) gameObject->afterUpdate();
}

/// Protected
// Defines the behaviour for the events
void State::_events() {
  // Call each event callback from the stack
  while (!_pendingEvents.empty()) {
    _pendingEvents.top()();
    _pendingEvents.pop();
  }
}

/// Protected Virtual
// Defines the behaviour for the destroy
void State::_destroy() {
  // For each object pending to be destroyed, destroy and erase from the game
  // objects
  for (list<GameObject *>::iterator object : _pendingOnDestroy) {
    if (*object != nullptr) {
      delete *object;
      _gameObjects.erase(object);
    }
  }

  // Clear the queue
  _pendingOnDestroy.clear();
}
