#include "Game.h"
#include "MenuState.h"
#include "SDLError.h"

GameManager *Game::_gamemanager = nullptr;
b2World *Game::_world = nullptr;
Game *Game::current = nullptr;

/// Public
// Constructor
Game::Game()
    : _window(nullptr), _renderer(nullptr)
{
  // Set up the Arkanoid settings for the window's width and height
  ArkanoidSettings::setUp(WIN_WIDTH, WIN_HEIGHT);
  current = this;

  // Initialize SDL and TTF
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    throw new SDLError("Error initializing SDL");
  if (TTF_Init() < 0)
    throw new SDLError("Error loading the SDL font");

  // Create the window and renderer
  _window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

  // If window or renderer is a null pointer, throw a SDLError
  if (_window == nullptr || _renderer == nullptr)
    throw new SDLError("Error loading the SDL window or renderer");

  // Create the textures
  for (uint i = 0; i < NUMBER_TEXTURES; i++)
    _textures[i] = new Texture(_renderer, TEXTURES[i].path, TEXTURES[i].rows, TEXTURES[i].columns);

  // Create the fonts
  _fonts[BIGFONT] = new Font(_renderer, FONTSDIRECTORIES[REGULAR], 72);
  _fonts[MEDIUMFONT] = new Font(_renderer, FONTSDIRECTORIES[REGULAR], 40);

  // Create the game manager and insert states
  _gamemanager = new GameManager(this);
  _states.push( new MenuState(this, _renderer));
  _currentState = _states.top();
}

/// Public
// Destructor
Game::~Game()
{
	while (!_states.empty()) {
		delete _states.top();
		_states.pop();
	}

  for (uint i = 0; i < NUMBER_TEXTURES; i++)
  {
    delete _textures[i];
  }
  delete _fonts[BIGFONT];
  delete _fonts[MEDIUMFONT];
  delete _gamemanager;
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  TTF_Quit();
  SDL_Quit();
}

/// Public
// Get this game's textures
Texture **Game::getTextures()
{
  return _textures;
}

/// Public
// Get this game's fonts
Font **Game::getFonts()
{
  return _fonts;
}

/// Public
// Run the game's event loop
void Game::run()
{
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
  while (!_states.empty())
  {
	  if (_currentState != nullptr)_currentState->create();
	  if (_currentState != nullptr) _currentState->handleEvents();
	  if (_currentState != nullptr) _currentState->update();
	  if (startTime.GetMilliseconds() / 1000.0f >= 1.0f / (ArkanoidSettings::framerate))
	  {
		  if (_currentState != nullptr) _currentState->fixUpdate(startTime.GetMilliseconds() / 1000.0f);
		  startTime.Reset();
	  }
	  if (_currentState != nullptr) _currentState->afterUpdate();
	  if (_currentState != nullptr) _currentState->render();
	  if (_currentState != nullptr) _currentState->events();
	  if (_currentState != nullptr) _currentState->destroy();
  }
}

void Game::popState() {
	if (!_states.empty()) {
		delete _states.top();
		_states.pop();
		if (!_states.empty()) {
			_currentState = _states.top();
			_currentState->init();
		}
		else {
			_currentState = nullptr;
		}
	}

}
void Game::pushState(State& state) {
	_states.push(&state);
	_currentState = &state;
}

/// Public
// Gets the game's game manager
GameManager *Game::getGameManager()
{
  return _gamemanager;
}

/// Public
// Gets the game's world
b2World *Game::getWorld()
{
  return _world;
}

/// Public
// Sets this game's world
void Game::setWorld(b2World &world)
{
  _world = &world;
}
