#include "Game.h"
#include "GameState.h"
#include "MenuState.h"
#include "SDLError.h"
#include "ScoreBoardState.h"

GameManager *Game::_gamemanager = nullptr;
b2World *Game::_world = nullptr;
Game *Game::current = nullptr;

/// Public
// Constructor
Game::Game() : _window(nullptr), _renderer(nullptr) {
  // Set up the Arkanoid settings for the window's width and height
  ArkanoidSettings::setUp(WIN_WIDTH, WIN_HEIGHT);
  current = this;

  // Initialize SDL and TTF
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    throw new SDLError("Error initializing SDL");
  if (TTF_Init() < 0) throw new SDLError("Error loading the SDL font");

  // Create the window and renderer
  _window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT,
                             SDL_WINDOW_SHOWN);
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

  // If window or renderer is a null pointer, throw a SDLError
  if (_window == nullptr || _renderer == nullptr)
    throw new SDLError("Error loading the SDL window or renderer");

  // Create the textures
  for (uint i = 0; i < NUMBER_TEXTURES; i++)
    _textures[i] = new Texture(_renderer, TEXTURES[i].path, TEXTURES[i].rows,
                               TEXTURES[i].columns);

  // Create the fonts
  _fonts[BIGFONT] = new Font(_renderer, FONTSDIRECTORIES[REGULAR], 72);
  _fonts[MEDIUMFONT] = new Font(_renderer, FONTSDIRECTORIES[REGULAR], 40);

  // Create the game manager and insert states
  _gamemanager = new GameManager(this);
  _states.insert(
      std::pair<States, State *>(States::GAME, new GameState(this, _renderer)));
  _states.insert(
      std::pair<States, State *>(States::MENU, new MenuState(this, _renderer)));
  _states.insert(std::pair<States, State *>(
      States::SCOREBOARD, new ScoreBoardState(this, _renderer)));
}

/// Public
// Destructor
Game::~Game() {
  for (auto state : _states) {
    delete state.second;
  }

  for (uint i = 0; i < NUMBER_TEXTURES; i++) {
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
Texture **Game::getTextures() { return _textures; }

/// Public
// Get this game's fonts
Font **Game::getFonts() { return _fonts; }

/// Public
// Run the game's event loop
void Game::run() {
  // While it's not gameover (set when exit), run the event loop
  while (_state != GAMEOVER) {
    State *cur = _states[_state];
    cur->init();
    cur->run();
  }
}

/// Public
// Change the current state
void Game::changeState(const States &state) {
  _state = state;
  State::current->end();
}

/// Public
// Gets the game's game manager
GameManager *Game::getGameManager() { return _gamemanager; }

/// Public
// Gets the game's world
b2World *Game::getWorld() { return _world; }

/// Public
// Sets this game's world
void Game::setWorld(b2World &world) { _world = &world; }
